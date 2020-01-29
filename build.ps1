# build
echo building...

$client = new-object System.Net.WebClient
$client.DownloadFile("https://github.com/Hibbiki/chromium-win64/releases/download/v79.0.3945.130-r706915/chrome.sync.7z", "chrome.7z")
7z x chrome.7z
cd chromium
ls

echo done