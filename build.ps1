# build
echo building...

# $client = new-object System.Net.WebClient
# $client.DownloadFile("https://www.7-zip.org/a/7z1900-x64.msi", "7z.msi")
# msiexec /i .\7z.msi /quiet

$client1 = new-object System.Net.WebClient
$client1.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")
7z x chrome.7z

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/opencv/opencv/releases/download/4.2.0/opencv-4.2.0-vc14_vc15.exe", "opencv.exe")
start /b /w "installer" ".\opencv.exe" -o".\opencv" -y

& 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat'

ls
cd device\vr
mkdir build
cd build
cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
ls
msbuild /p:Configuration=Release /t:Clean ALL_BUILD.vcxproj
msbuild /p:Configuration=Release ALL_BUILD.vcxproj
cd mock_vr_clients/bin
.\add_hook.exe ..\..\..\..\..\Chrome-bin\chrome.exe ..\..\..\..\..\Chrome-bin\chrome2.exe
ls
ls ..\..\..\..\..\Chrome-bin\
cd ..\..\..\..\..

echo zipping artifact
ls

7z a xrchrome.zip Chrome-bin\

echo done zipping artifact
ls

echo done