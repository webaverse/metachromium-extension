let ids = 0;
const callbacks = {};
window.xrchrome = {
  async request(method, args) {
    const id = ++ids;

    postMessage({
      _xrcreq: true,
      method,
      args,
      id,
    }, '*', []);

    let accept, reject;
    const p = new Promise((a, r) => {
      accept = a;
      reject = r;
    });
    callbacks[id] = (error, result) => {
      if (!error) {
        accept(result);
      } else {
        reject(error);
      }
    };
    return await p;
  }
};
window.addEventListener('message', m => {
  // console.log('content script got message', m);
  if (m.data && m.data._xrcres) {
    const {id, error, result} = m.data;
    const cb = callbacks[id];
    if (cb) {
      cb(error, result);
      delete callbacks[id];
    }
  }
});
const getHWnd = async () => {
  const oldTitle = document.title;
  document.title = `Metachromium ${Math.random().toString(36).replace(/[^a-z]+/g, '').substr(0, 5)}`;
  const title = document.title + ' - Chromium';
  let hwnd = [0, 0];
  while (hwnd[0] === 0 && hwnd[1] === 0) {
    hwnd = await window.xrchrome.request('getHwndFromTitle', [title]);
    await new Promise(accept => {
      setTimeout(accept, 100);
    });
  }
  document.title = oldTitle;
  return hwnd;
};
window.addEventListener('load', async () => {
  const hwnd = await getHWnd();
  window.dispatchEvent(new MessageEvent('xrload', {
    data: {
      hwnd,
    },
  }));

  const _keydown = e => {
    if (e.ctrlKey && e.which === 17) {
      window.removeEventListener('keydown', _keydown);
      navigator.xr.dispatchEvent(new MessageEvent('activate'));
    }
  };
  window.addEventListener('keydown', _keydown);
  await window.xrchrome.request('activate', [hwnd]);
});

/* window.xrchrome.request('test', [])
  .then(res => {
    console.log(res);
  }); */