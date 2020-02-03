# build
echo building...

$client1 = new-object System.Net.WebClient
$client1.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")
7z x chrome.7z
rm chrome.7z

& 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat'

ls
cd device\vr
mkdir build
cd build
cp ..\build.cmd .
.\build.cmd

cd mock_vr_clients\bin
cp -Recurse ..\..\..\..\..\bin\* .

ls ..\..\..\..\..\Chrome-bin\
ls ..\..\..\..\..\Chrome-bin\79.0.3945.130\
Start-Process -FilePath "add_hook.exe" -ArgumentList "..\..\..\..\..\Chrome-bin\chrome.exe ..\..\..\..\..\Chrome-bin\chrome2.exe" -Wait
del ..\..\..\..\..\Chrome-bin\chrome.exe
move ..\..\..\..\..\Chrome-bin\chrome2.exe ..\..\..\..\..\Chrome-bin\chrome.exe
cp -Recurse ..\..\..\..\..\Chrome-bin\* .
cd ..\..\..\..\..

echo zipping artifact... 
7z a xrchrome.zip -r .\device\vr\build\mock_vr_clients\bin\
echo done zipping artifact

ls device\vr\build\mock_vr_clients\bin\
ls device\vr\build\mock_vr_clients\bin\79.0.3945.130\
ls

echo done