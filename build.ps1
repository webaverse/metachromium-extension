# build
echo building...

$ProgressPreference = 'SilentlyContinue'

Invoke-WebRequest "https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z" -OutFile "chrome.7z"
7z x chrome.7z
rm chrome.7z

Invoke-WebRequest "https://github.com/opencv/opencv/releases/download/4.2.0/opencv-4.2.0-vc14_vc15.exe" -OutFile "opencv.exe"
Start-Process -Wait ".\opencv.exe" -ArgumentList "-o. -y"

mkdir metamask
cd metamask
Invoke-WebRequest "https://github.com/MetaMask/metamask-extension/releases/download/v7.7.4/metamask-chrome-7.7.4.zip" -OutFile "metamask.zip"
7z x metamask.zip
(Get-Content -Encoding UTF8 background.js) -replace '(openExtensionInBrowser\s*\(.*\)\s*.)', '$1return;' | Set-Content -Encoding UTF8 background2.js
openExtensionInBrowser(e = null, t = null) {
cd ..

ls
cd device\vr
mkdir build
cd build

cp ..\build.ps1 .
& '.\build.ps1'
cd ..\..\..

echo zipping artifact... 
7z a xrchrome.zip -r .\device\vr\build\mock_vr_clients\bin\
echo done zipping artifact

ls

echo done