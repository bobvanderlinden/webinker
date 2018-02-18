const HeadlessChrome = require("simple-headless-chrome");
const im = require('imagemagick-stream');
const fs = require('fs')
const net = require('net')
const toArray = require('stream-to-array')
const unique = require('array-unique')
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
  // const screenshot = fs.createReadStream('test.png');
  const grayScreenshot = convertToGrayscale(screenshot)
  // const grayScreenshot = fs.createReadStream('gray.raw')
  // grayScreenshot.pipe(fs.createWriteStream('gray.raw'))
  // let counter = 0
  // grayScreenshot.on('data', data => {
  //   counter += data.length
  // })
  // grayScreenshot.on('end', () => {
  //   console.log('SENT', counter, 'bytes')
  // })
  // const ding = net.createConnection(12345, '192.168.1.25', () => {
  //   ding.write('@')
  //   grayScreenshot.pipe(ding)
  // })
  // ding.on('finish', () => {
  //   console.log('ding end')
  //   res.end()
  // })
  // const TwoBppScreenshot = convertTo2bpp(grayScreenshot)
  // TwoBppScreenshot.pipe(fs.createWriteStream('test.raw'));
  const output = grayScreenshot.pipe(res)
  output.on('end', () => {
    console.log(`Finished streaming ${url}`)
  })
})

function convertTo2bpp(input) {
  console.log('convertTo2bpp')
  const output = new Readable();
  output._read = () => {};
  toArray(input, (err, buffers) => {
    const arr = []
    for(let buffer of buffers) {
      arr.push(...buffer)
    }
    const uniqueBytes = {};
    for(let byte of arr) {
      uniqueBytes[byte] = true;
    }
    console.log(Object.keys(uniqueBytes))
    const uniqueColors = unique(arr)
    console.log('uniqueColors', uniqueColors.length)
    console.assert(uniqueColors.length <= 4, 'Too many colors')
    const sortedColors = uniqueColors.sort()
    while (sortedColors.length < 4) {
      sortedColors.push(0xff);
    }
    const outputArr = [];
    for (let i = 0; i < arr.length; i += 4) {
      const color1 = sortedColors.indexOf(arr[i]);
      const color2 = sortedColors.indexOf(arr[i+1]);
      const color3 = sortedColors.indexOf(arr[i+2]);
      const color4 = sortedColors.indexOf(arr[i+3]);
      const outputByte =
        (color1 << 6) &
        (color2 << 4) & 
        (color3 << 2) &
        (color4 << 0);
      outputArr.push(outputByte);
    }
    const outputStr = String.fromCharCode.apply(null, outputArr);
    console.log('outputArr', outputArr);
    console.log('outputStr', outputStr);
    output.push(outputStr);
    output.push(null);
  })
  return output
}

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
