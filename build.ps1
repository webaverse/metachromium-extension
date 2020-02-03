# build
echo building...

$client1 = new-object System.Net.WebClient
$client1.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")
7z x chrome.7z
rm chrome.7z

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/opencv/opencv/releases/download/4.2.0/opencv-4.2.0-vc14_vc15.exe", "opencv.exe")
start /b /w "installer" ".\opencv.exe" -o. -y

& 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat'

ls
cd device\vr
mkdir build
cd build
cp ..\build.cmd .
.\build.cmd

cd mock_vr_clients\bin
cp -Recurse ..\..\..\..\..\bin\* .
copy ..\..\..\..\..\opencv\build\x64\vc15\bin\opencv_world420.dll .

ls ..\..\..\..\..\Chrome-bin\
ls ..\..\..\..\..\Chrome-bin\79.0.3945.130\
Start-Process -FilePath "add_hook.exe" -ArgumentList "..\..\..\..\..\Chrome-bin\chrome.exe ..\..\..\..\..\Chrome-bin\chrome2.exe" -Wait
del ..\..\..\..\..\Chrome-bin\chrome.exe
move ..\..\..\..\..\Chrome-bin\chrome2.exe ..\..\..\..\..\Chrome-bin\chrome.exe
cp -Recurse ..\..\..\..\..\Chrome-bin\* .
cd ..\..\..\..\..

echo zipping artifact... 
Compress-Archive -Path .\device\vr\build\mock_vr_clients\bin\ -DestinationPath xrchrome.zip
echo done zipping artifact

ls device\vr\build\mock_vr_clients\bin\
ls device\vr\build\mock_vr_clients\bin\79.0.3945.130\
ls

echo done