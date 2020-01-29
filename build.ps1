# build
echo building...

# $client = new-object System.Net.WebClient
# $client.DownloadFile("https://www.7-zip.org/a/7z1900-x64.msi", "7z.msi")
# msiexec /i .\7z.msi /quiet

echo installed

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")

7z x chrome.7z

echo extracted

& 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat'

ls
cd device\vr
mkdir build
cd build
cmake --version
cmake --trace -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release /t:Clean ALL_BUILD.vcxproj
msbuild /p:Configuration=Release ALL_BUILD.vcxproj
# cd Chrome-bin
# ls

echo done