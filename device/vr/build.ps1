& 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat'

cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release /m ALL_BUILD.vcxproj

cd metachromium\bin

cp -Recurse -Force ..\..\..\..\..\bin\* .

cp -Recurse -Force ..\..\..\..\..\Chrome-bin\* .

cp -Force ..\..\..\..\..\opencv\x64\vc16\bin\opencv_world420.dll .

cp -Recurse -Force ..\..\..\..\..\extension .
cp -Recurse -Force ..\..\..\..\..\metamask .

cd ..\..