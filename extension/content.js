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
window.addEventListener('load', async () => {
  window.dispatchEvent(new MessageEvent('xrchromeloaded'));
  const _keydown = e => {
    if (e.ctrlKey && e.which === 17) {
      window.removeEventListener('keydown', _keydown);
      navigator.xr.dispatchEvent(new MessageEvent('activate'));
    }
  };
  window.addEventListener('keydown', _keydown);
  await window.xrchrome.request('activate', []);
});

/* window.xrchrome.request('test', [])
  .then(res => {
    console.log(res);
  }); */