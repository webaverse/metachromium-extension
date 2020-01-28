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

chrome.runtime.onMessage.addListener(
  function(request, sender, sendResponse) {
    /* console.log(sender.tab ?
                "from a content script:" + sender.tab.url :
                "from the extension"); */
    console.log('got req', request, sender, sendResponse);
    if (request && request.method && request.args) {
      const {method, args} = request;
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
    } else {
      sendResponse({
        pong: true,
      });
    }
    
    return true; // async
});