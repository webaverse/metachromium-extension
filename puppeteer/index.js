const path = require('path');
const fs = require('fs');

/* const logStream = fs.createWriteStream(__dirname + '/../node/log_puppeteer.txt', {
  flags: 'a',
});
const con = new console.Console(logStream, logStream);
Object.defineProperty(process, 'stdout', {
  get() {
    return logStream;
  },
});
Object.defineProperty(process, 'stderr', {
  get() {
    return logStream;
  },
}); */

const puppeteer = require('../node/node_modules/puppeteer');

(async () => {
const browser = await puppeteer.launch({
  executablePath: path.join(__dirname, '..', 'device', 'vr', 'build', 'mock_vr_clients', 'bin', 'chrome.exe'),
  args: [
    `--enable-features="WebXR,OpenVR"`,
    `--disable-features="WindowsMixedReality"`,
    `--no-sandbox`,
    `--test-type`,
    `--disable-xr-device-consent-prompt-for-testing`,
    // `--app=${path.join(__dirname, '..', 'extension', 'index.html')}`,
    // `--no-startup-window`,
    `--load-extension=${path.join(__dirname, '..', 'extension')}`,
    `--window-position=-10000,-10000`,
  ],
  ignoreDefaultArgs: ['--enable-automation'],
  headless: false,
});
// const pages = await browser.pages();
// const page = pages[0];
const page = await browser.newPage();
await page.goto(path.join(__dirname, '..', 'extension', 'index.html'));
// await browser.close();

process.stdin.on('end', () => {
  process.exit();
});
/* process.on('exit', () => {
  browser.close();
});
browser.on('disconnected', () => {
  console.log('browser disconnect');
}); */

const _jsonParse = s => {
  try {
    return JSON.parse(s);
  } catch(err) {
    return null;
  }
};

let bs = [];
let size = 0;
const _flatten = () => {
  if (bs.length > 0) {
    bs = [Buffer.concat(bs)];
  }
  return bs[0];
};
process.stdin.on('data', d => {
  bs.push(d);
  size += d.length;

  for (;;) {
    if (size >= Uint32Array.BYTES_PER_ELEMENT) {
      // console.log('got size', size);
      const b = _flatten();
      const jsonSize = new Uint32Array(b)[0];
      // console.log('more size ok?', jsonSize, size >= Uint32Array.BYTES_PER_ELEMENT + jsonSize);
      if (size >= Uint32Array.BYTES_PER_ELEMENT + jsonSize) {
        const s = new TextDecoder().decode(b.slice(Uint32Array.BYTES_PER_ELEMENT, Uint32Array.BYTES_PER_ELEMENT + jsonSize));
        // console.log('browser got message', s);
        const j = _jsonParse(s);
        _handleMessage(j);
        const shiftSize = Uint32Array.BYTES_PER_ELEMENT + jsonSize;
        bs[0] = bs[0].slice(shiftSize);
        size -= shiftSize;
      } else {
        break;
      }
    } else {
      break;
    }
  }
});

const _handleMessage = async j => {
  if (j) {
    const {method, args} = j;
    switch (method) {
      case 'mousedown': {
        if (page) {
          // console.log('mouse down');
          await page.mouse.down();
        }
        break;
      }
      case 'mouseup': {
        if (page) {
          // console.log('mouse up');
          await page.mouse.up();
        }
        break;
      }
      case 'mousemove': {
        if (page) {
          const {x, y} = args;
          // console.log('mouse move', x, y);
          await page.mouse.move(x, y);
        }
        break;
      }
    }
  }
};

})();