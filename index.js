const HeadlessChrome = require("simple-headless-chrome");
const im = require('imagemagick-stream');
const Readable = require('stream').Readable;
const express = require('express');
const debug = require('debug')('webinker')

function tryParseInt(s) {
  return s && parseInt(s, 10);
}

const formats = {
  png: (stream) => stream,
  gray: convertToGrayscale
}

const app = express()
app.set('port', (process.env.PORT || 5000));
app.get('/', (req, res) => {
  const url = req.query.url;
  if (!url) {
    res.statusCode = 400;
    res.statusMessage = 'No url specified'
    return res.end()
  }
  const format = req.query.format || 'png'
  const formatter = formats[format]
  if (!formatter) {
    res.statusCode = 400;
    res.statusMessage = 'No valid format specified'
    return res.end()
  }
  debug(`Request received for ${url}`)
  res.status = 200;
  res.setHeader('Content-Type', 'image/png');
  const screenshot = getScreenshotStream(url, {
    width: tryParseInt(req.query.width),
    height: tryParseInt(req.query.height)
  });
  const formattedScreenshot = formatter(screenshot)
  const output = formattedScreenshot.pipe(res)
  output.on('end', () => {
    debug(`Finished streaming ${url}`)
  })
})

function convertToGrayscale(stream) {
  const converter = im()
    .set('colorspace', 'gray')
    .set('colors', '4')
    .set('depth', '2')
    .set('alpha', 'off')
    .outputFormat('gray');
  return stream.pipe(converter);
}

function getScreenshotStream(url, options = {}) {
  debug(`Creating screenshot ${url}`);
  const stream = new Readable();
  stream._read = () => {};
  getScreenshot(url, options)
    .then(data => {
      debug(`Screenshot created ${url} (${data.length})`);
      stream.push(data);
      stream.push(null);
    });
  return stream;
}

async function getScreenshot(url, options = { }) {
  const browser = new HeadlessChrome({
    headless: true,
    deviceMetrics: {
      width: options.width || 800,
      height: options.height || 600
    }
  });
  await browser.init();
  const mainTab = await browser.newTab({ privateTab: false });
  await mainTab.goTo(url);
  await mainTab.wait(1000);
  const result = await mainTab.getScreenshot({
    format: 'png'
  }, true);
  await browser.close();
  return result;
}

app.listen(app.get('port'))
