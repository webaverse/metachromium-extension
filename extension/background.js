// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

// Declare extension default properties
/* let downloadsArray = [];
let initialState = {
  'savedImages': downloadsArray,
  'thumbnails': false,
  'saveImages': true
}; */

// Set extension setting on installation
/* chrome.runtime.onInstalled.addListener(function() {
}); */

/* console.log('listening 1', chrome.runtime.connectNative);

const inject = tab => {
  console.log('got tab', tab.id);
  chrome.tabs.executeScript(tab.id, {
    code: `
      window.lol = 'zol';
      window.document.lol = 'zol';
      // document.body.style.backgroundColor = "orange";
    `,  
  }, () => {
    console.log('ran script');
  })
};
chrome.tabs.onCreated.addListener(inject);
chrome.tabs.onUpdated.addListener(inject); */

const port = chrome.runtime.connectNative('com.exokit.xrchrome');
const cbs = [];
port.onMessage.addListener(msg => {
  console.log("received native", msg);
  if (cbs.length > 0) {
    const cb = cbs.shift();
    cb(msg);
  }
});
port.onDisconnect.addListener(() => {
  console.log("disconnected native");
});
// port.postMessage({ text: "Hello, my_application" });

function proxyRequest(method, args, sendResponse) {
  port.postMessage({method, args});
  cbs.push(msg => {
    console.log('got proxy res', msg);
    if (msg && msg.error !== undefined && msg.result !== undefined) {
      sendResponse({
        error: msg.error,
        result: msg.result,
      });
    } else {
      sendResponse({
        error: 'internal error: ' + JSON.stringify(msg),
        result: null,
      });
    }
  });
}

chrome.runtime.onMessage.addListener(
  function(request, sender, sendResponse) {
    /* console.log(sender.tab ?
                "from a content script:" + sender.tab.url :
                "from the extension"); */
    console.log('got req', request, sender, sendResponse);
    if (request && request.method && request.args) {
      const {method, args} = request;
      if (method === 'tabCapture') {
        // const [u] = args;
        // console.log('capture offscreen 1', u);
        chrome.tabs.query({}, tabs => {
          chrome.desktopCapture.chooseDesktopMedia(['window'], tabs[0], streamId => {
            // e = streamId;
            // console.log(e);
            sendResponse({
              error: null,
              result: streamId,
            });
          });
        });
      } else if (method === 'sendMouse') {
        // const [u] = args;
        // console.log('capture offscreen 1', u);
        chrome.tabs.query({}, tabs => {
          chrome.processes.getProcessIdForTab(tabs[0].id, processId => {
            chrome.processes.getProcessInfo(processId, false, pids => {
              const pid = pids[processId].osProcessId;
              args.push(pid);
              proxyRequest(method, args, sendResponse);
            });
          });
        });
        /* chrome.tabCapture.captureOffscreenTab(u, {
          video: true,
        }, mediaStream => {
          const u = URL.createObjectURL(mediaStream);
          console.log('capture offscreen 2', mediaStream, u);
          sendResponse({
            error: null,
            result: u,
          });
        }); */
      } else {
        proxyRequest(method, args, sendResponse);
      }
    } else {
      sendResponse({
        pong: true,
      });
    }
    
    return true; // async
});