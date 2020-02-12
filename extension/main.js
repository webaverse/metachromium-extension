/* chrome.runtime.sendMessage({greeting: "hello"}, function(response) {
  console.log(response.farewell);
}); */

// console.log('injecting');

window.addEventListener('message', m => {
  // console.log('main script got message', m.data);
  if (m.data && m.data._xrcreq) {
    const {method, args, id} = m.data;
    // console.log('send runtime msg');
    chrome.runtime.sendMessage({method, args}, function(res) {
      // console.log('got runtime response', chrome.runtime.lastError, res, Array.from(arguments));
      const {error, result} = res;
      window.postMessage({
        _xrcres: true,
        id,
        error,
        result,
      }, '*', []);
    });
  }
});
chrome.runtime.sendMessage({}, function(res) {
  console.log('got ping response', res);
});

function injectScript(file_path, tag) {
  const node = document.getElementsByTagName(tag)[0];
  const script = document.createElement('script');
  script.setAttribute('type', 'text/javascript');
  script.setAttribute('src', file_path);
  node.appendChild(script);
}
injectScript(chrome.extension.getURL('content.js'), 'body');

// chrome.runtime.sendMessage({ping: true}, () => {});
// console.log('content script', chrome.runtime.connectNative);