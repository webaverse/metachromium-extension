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
  console.log('load 1');
  const _keydown = e => {
    console.log('got keydown', e.ctrlKey, e.which);
    if (e.ctrlKey && e.which === 17) {
      console.log('emit 1');
      window.removeEventListener('keydown', _keydown);
      navigator.xr.dispatchEvent(new MessageEvent('activate'));
      console.log('emit 2');
    }
  };
  window.addEventListener('keydown', _keydown);
  console.log('load 2');
  await window.xrchrome.request('activate', []);
  console.log('load 3');
});

/* window.xrchrome.request('test', [])
  .then(res => {
    console.log(res);
  }); */