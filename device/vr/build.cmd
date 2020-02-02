cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release ALL_BUILD.vcxproj
copy /Y mock_vr_clients\bin\vrclient_x64.dll ..\..\..\Chrome-bin\