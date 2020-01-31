# build
echo building...

# $client = new-object System.Net.WebClient
# $client.DownloadFile("https://www.7-zip.org/a/7z1900-x64.msi", "7z.msi")
# msiexec /i .\7z.msi /quiet

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")
7z x chrome.7z
rm chrome.7z

$client3 = new-object System.Net.WebClient
$client3.DownloadFile("https://nodejs.org/dist/v13.7.0/node-v13.7.0-win-x64.zip", "node.zip")
7z x node.zip
rm node.zip
mv node* node

& 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat'

ls
cd device\vr
mkdir build
cd build
cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
ls
msbuild /p:Configuration=Release ALL_BUILD.vcxproj

cd mock_vr_clients/bin
copy ..\..\..\..\..\bin\* .

.\add_hook.exe ..\..\..\..\..\Chrome-bin\chrome.exe ..\..\..\..\..\Chrome-bin\chrome2.exe
move ..\..\..\..\..\Chrome-bin\chrome.exe ..\..\..\..\..\Chrome-bin\chrome3.exe
move ..\..\..\..\..\Chrome-bin\chrome2.exe ..\..\..\..\..\Chrome-bin\chrome.exe
copy .\glfw3.dll ..\..\..\..\..\Chrome-bin\
copy .\glew32.dll ..\..\..\..\..\Chrome-bin\
copy .\vrclient_x64.dll ..\..\..\..\..\Chrome-bin\
cd ..\..\..\..\..

cd node
$env:PUPPETEER_SKIP_CHROMIUM_DOWNLOAD = '1'
.\npm.cmd install puppeteer
cd ..

echo zipping artifact
ls

7z a xrchrome.zip Chrome-bin\

echo done zipping artifact
ls

echo done