# build
echo building...

$client1 = new-object System.Net.WebClient
$client1.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")
7z x chrome.7z
rm chrome.7z

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/opencv/opencv/releases/download/4.2.0/opencv-4.2.0-vc14_vc15.exe", "opencv.exe")
start /b /w "installer" ".\opencv.exe" -o. -y

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