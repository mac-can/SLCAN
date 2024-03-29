@echo off
set PWD="%~dp0"
pushd
cd /D %PWD%
copy /Y .\Library\Release_dll\uvslcan.dll C:\Windows\SysWOW64
popd
dir C:\Windows\SysWOW64\u*can*.dll
pause
