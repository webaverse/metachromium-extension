# build
echo building...

$client = new-object System.Net.WebClient
$client.DownloadFile("https://www.7-zip.org/a/7z1900-x64.msi", "7z.msi")
msiexec /i .\7z.msi /quiet

echo installed

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")

7z x chrome.7z
ls
cd Chrome-bin
ls

echo done