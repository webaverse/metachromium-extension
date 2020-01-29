# build
echo building...

$client = new-object System.Net.WebClient
$client.DownloadFile("https://www.7-zip.org/a/7z1900-x64.exe", "7z.exe")

$client2 = new-object System.Net.WebClient
$client2.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")

.\7z.exe x chrome.7z
ls
cd chromium
ls

echo done