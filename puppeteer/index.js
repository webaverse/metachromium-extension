const path = require('path');
const fs = require('fs');

const logStream = fs.createWriteStream(__dirname + '/log_puppeteer.txt', {
  flags: 'a',
});
Object.defineProperty(process, 'stdout', {
  get() {
    return logStream;
  },
});
Object.defineProperty(process, 'stderr', {
  get() {
    return logStream;
  },
});

const puppeteer = require('../node/node_modules/puppeteer');

let page = null;
(async () => {
  const browser = await puppeteer.launch({
    executablePath: path.join(__dirname, '..', 'Chrome-bin', 'chrome.exe'),
    args: [
      `--enable-features="WebXR,OpenVR"`,
      `--disable-features="WindowsMixedReality"`,
      `--no-sandbox`,
      `--test-type`,
      `--disable-xr-device-consent-prompt-for-testing`,
      // `--app=${path.join(__dirname, '..', 'extension', 'index.html')}`,
    ],
    ignoreDefaultArgs: ['--enable-automation'],
    headless: false,
  });
  browser.on('disconnected', () => {
    process.exit();
  });
  const pages = await browser.pages();
  // page = await browser.newPage();
  page = pages[0];
  await page.goto(path.join(__dirname, '..', 'extension', 'index.html'));
  // await browser.close();
})();

let bs = [];
let size = 0;
const _flatten = () => {
  if (bs.length > 0) {
    bs = [Buffer.concat.apply(Buffer, bs)];
  }
  return bs[0];
};
process.stdin.on('data', d => {
  bs.push(d);
  size += d.length;
  let flattened = false;

  for (;;) {
    if (size >= Uint32Array.BYTES_PER_ELEMENT) {
      const b = _flatten();
      const jsonSize = new Uint32Array(b)[0];
      if (size >= Uint32Array.BYTES_PER_ELEMENT + jsonSize) {
        const s = new TextDecoder().decode(b.slice(Uint32Array.BYTES_PER_ELEMENT, Uint32Array.BYTES_PER_ELEMENT + jsonSize));
        const j = JSON.parse(s);
        _handleMessage(j);
        bs[0] = bs[0].slice(Uint32Array.BYTES_PER_ELEMENT + jsonSize);
      } else {
        break;
      }
    } else {
      break;
    }
  }
});
process.stdin.on('end', () => {
  process.exit();
});

const _handleMessage = async j => {
  const {method} = j;
  switch (method) {
    case 'mousedown': {
      if (page) {
        await page.mouse.down();
      }
      break;
    }
    case 'mouseup': {
      if (page) {
        await page.mouse.up();
      }
      break;
    }
    case 'mousemove': {
      if (page) {
        const {x, y} = j;
        await page.mouse.move(x, y);
      }
      break;
    }
  }
};