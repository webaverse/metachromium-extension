// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

chrome.windows.onRemoved.addListener(windowId => {
  console.log('window removed', windowId);
  chrome.windows.getAll({}, windows => {
    console.log('got windows', windows);
    if (windows.length === 0) {
      console.log('calling terminate');
      const s = new WebSocket('ws://localhost:9002');
      s.onopen = () => {
        console.log('terminate sent');
        s.send(JSON.stringify({
          method: 'terminate',
          args: [],
        }));
        s.onmessage = m => {
          console.log('get terminate result', m);
        };
      };
      s.onerror = err => {
        console.log('background websocket error', err);
      };
    }
  });
});