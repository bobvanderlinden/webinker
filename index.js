const HeadlessChrome = require("simple-headless-chrome");
const fs = require("fs");
const im = require('imagemagick-stream');
const Readable = require('stream').Readable;
const express = require('express');

const app = express()
app.set('port', (process.env.PORT || 5000));
app.get('/', (req, res) => {
  res.setHeader('Content-Type', 'image/png');
  const converted = convert(getScreenshotStream(req.params.url))
  converted.pipe(res)
})

function convert(stream) {
  const converter = im()
    .set('colorspace', 'gray')
    .set('depth', '2')
    .set('alpha', 'off');
  return stream.pipe(converter);
}

function getScreenshotStream(url) {
  const stream = new Readable();
  stream._read = () => {};
  getScreenshot(url)
    .then(data => {
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
    captureOptions: {
      format: 'png'
    },
    returnBinary: true
  });
  await browser.close();
  return result;
}

app.listen(app.get('port'))
