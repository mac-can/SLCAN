@echo off
set PWD="%~dp0"
pushd
cd /D %PWD%
copy /Y .\Library\x64\Release_dll\uvslcan.dll C:\Windows\System32
popd
dir C:\Windows\System32\u*can*.dll
pause
