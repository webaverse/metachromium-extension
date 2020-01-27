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
port.onMessage.addListener(function(msg) {
  console.log("Received", msg);
});
port.onDisconnect.addListener(function() {
  console.log("Disconnected");
});
port.postMessage({ text: "Hello, my_application" });

chrome.runtime.onMessage.addListener(
  function(request, sender, sendResponse) {
    /* console.log(sender.tab ?
                "from a content script:" + sender.tab.url :
                "from the extension"); */
    // if (request.greeting == "hello")
    // console.log('got req', request);
    sendResponse({
      error: null,
      result: 'ok',
    });
});