# build
echo building...

$ProgressPreference = 'SilentlyContinue'

Invoke-WebRequest "https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z" -OutFile "chrome.7z"
7z x chrome.7z -aoa
rm chrome.7z

git clone https://github.com/exokitxr/opencv-bin.git opencv

mkdir -Force metamask
cd metamask
Invoke-WebRequest "https://github.com/MetaMask/metamask-extension/releases/download/v7.7.4/metamask-chrome-7.7.4.zip" -OutFile "metamask.zip"
7z x metamask.zip -aoa
(Get-Content -Encoding UTF8 background.js) -replace '(openExtensionInBrowser\(e=null,t=null\)\{)', '$1return;' | Set-Content -Encoding UTF8 background.js
cd ..

ls
cd device\vr
mkdir -Force build
cd build

cp ..\build.ps1 .
& '.\build.ps1'
cd ..\..\..

echo zipping artifact... 
7z a xrchrome.zip -r .\device\vr\build\mock_vr_clients\bin\
echo done zipping artifact

ls

echo done