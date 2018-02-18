const HeadlessChrome = require("simple-headless-chrome");
const im = require('imagemagick-stream');
const Readable = require('stream').Readable;
const express = require('express');

const app = express()
app.set('port', (process.env.PORT || 5000));
app.get('/', (req, res) => {
  const url = req.query.url;
  if (!url) {
    res.statusCode = 400;
    res.statusMessage = 'No url specified'
    return res.end()
  }
  console.log(`Request received for ${url}`)
  res.status = 200;
  res.setHeader('Content-Type', 'image/png');
  const screenshot = getScreenshotStream(url);
  const grayScreenshot = convertToGrayscale(screenshot)
  const output = grayScreenshot.pipe(res)
  output.on('end', () => {
    console.log(`Finished streaming ${url}`)
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

function getScreenshotStream(url) {
  console.log(`Creating screenshot ${url}`);
  const stream = new Readable();
  stream._read = () => {};
  getScreenshot(url)
    .then(data => {
      console.log(`Screenshot created ${url} (${data.length})`);
      stream.push(data);
      stream.push(null);
    });
  return stream;
}

async function getScreenshot(url) {
  const browser = new HeadlessChrome({
    headless: true,
    deviceMetrics: {
      width: 800,
      height: 600
    }
  });
  await browser.init();
  const mainTab = await browser.newTab({ privateTab: false });
  await mainTab.goTo(url);
  const result = await mainTab.getScreenshot({
    format: 'png'
  }, true);
  await browser.close();
  return result;
}

app.listen(app.get('port'))
