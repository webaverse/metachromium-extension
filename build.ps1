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
copy ..\build.cmd .
.\build.cmd

cd mock_vr_clients\bin
copy ..\..\..\..\..\bin\* .
copy ..\..\..\..\..\opencv\build\x64\vc15\bin\opencv_world420.dll .

.\add_hook.exe ..\..\..\..\..\Chrome-bin\chrome.exe ..\..\..\..\..\Chrome-bin\chrome2.exe
del ..\..\..\..\..\Chrome-bin\chrome.exe
move ..\..\..\..\..\Chrome-bin\chrome2.exe ..\..\..\..\..\Chrome-bin\chrome.exe
copy ..\..\..\..\..\Chrome-bin\* .
cd ..\..\..\..\..

echo zipping artifact
ls

7z a xrchrome.zip device\vr\build\mock_vr_clients\bin\

echo done zipping artifact
ls

echo done