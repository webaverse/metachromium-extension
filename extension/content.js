let s = null;
const cbs = [];
window.xrchrome = {
  async request(method, args) {
    if (!s) {
      s = new WebSocket('ws://localhost:9002');
      s.onmessage = e => {
        console.log('got response', e.data);
        const j = JSON.parse(e.data);
        cbs.shift()(j.error, j.result);
      };
      s.onclose = () => {
        s = null;
        console.warn('native host websocket closed');
      };
      s.onerror = err => {
        console.warn(err.stack);
      };
    }
    
    const _send = () => {
      console.log('send req', {method, args});
      s.send(JSON.stringify({
        method,
        args,
      }));
    };
    if (s.readyState === s.CONNECTED) {
      _send();
    } else {
      s.addEventListener('open', _send, {once: true});
    }

    let accept, reject;
    const p = new Promise((a, r) => {
      accept = a;
      reject = r;
    });
    cbs.push((error, result) => {
      if (!error) {
        accept(result);
      } else {
        reject(error);
      }
    });
    return await p;
  }
};
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