const puppeteer = require('puppeteer');

let page = null;
(async () => {
  const browser = await puppeteer.launch({
    executablePath: '', // XXX
    args: [
      // XXX
    ],
  });
  page = await browser.newPage();
  await page.goto('https://www.google.com'); // XXX
  await browser.close();
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
    case 'mousedown' {
      if (page) {
        await page.mouse.down();
      }
      break;
    }
    case 'mouseup' {
      if (page) {
        await page.mouse.up();
      }
      break;
    }
    case 'mousemove' {
      if (page) {
        const {x, y} = j;
        await page.mouse.move(x, y);
      }
      break;
    }
  }
};