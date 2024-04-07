rem Requires administrator rights!
@echo off
set PWD="%~dp0"
pushd
cd /D %PWD%
copy /Y .\Binary\x86\uvslcan.dll C:\Windows\SysWOW64
popd
dir C:\Windows\SysWOW64\u*can*.dll
pause
