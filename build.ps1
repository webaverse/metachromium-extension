# build
echo building...

$client = new-object System.Net.WebClient
$client.DownloadFile("https://chromium.woolyss.com/f/chrlauncher-win64-stable-codecs-sync.zip", "chromium.zip")
Expand-Archive -Path chromium.zip
cd chromium
ls

echo done