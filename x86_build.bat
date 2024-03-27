@echo off

rem parse arguments: [[NOVARS] NOTRIAL]
if "%1" == "NOVARS" (
   set VCVARS="False"
) else (
   set VCVARS="True"
)
SHIFT
if "%1" == "NOTRIAL" (
  set TRIAL="False"
) else (
  set TRIAL="True"
)

rem set MSBuild environment variables
if %VCVARS% == "True" (
   pushd
   call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" x86
   popd
)
pushd

rem generate a pseudo build number
call build_no.bat

rem build the trial program
if %TRIAL% == "True" ( 
   call msbuild.exe .\Trial\slcan_test.vcxproj /t:Clean;Build /p:"Configuration=Debug";"Platform=Win32"
   if errorlevel 1 goto end
)
rem build the SLCAN library (dynamic and static)
call msbuild.exe .\Library\uvslcan.vcxproj /t:Clean;Build /p:"Configuration=Release_dll";"Platform=Win32"
if errorlevel 1 goto end

call msbuild.exe .\Library\uvslcan.vcxproj /t:Clean;Build /p:"Configuration=Debug_lib";"Platform=Win32"
if errorlevel 1 goto end

rem copy the arifacts into the Binaries folder
echo Copying artifacts...
set BIN=".\Binaries"
if not exist %BIN% mkdir %BIN%
set BIN="%BIN%\x86"
if not exist %BIN% mkdir %BIN%
copy /Y .\Library\Release_dll\uvslcan.dll %BIN%
copy /Y .\Library\Release_dll\uvslcan.lib %BIN%
set BIN="%BIN%\lib"
if not exist %BIN% mkdir %BIN%
copy /Y .\Library\Debug_lib\uvslcan.lib %BIN%
copy /Y .\Library\Debug_lib\uvslcan.pdb %BIN%
echo Static libraries (x86) > %BIN%\readme.txt

rem copy the header files into the Includes folder
echo Copying header files...
set INC=".\Includes"
if not exist %INC% mkdir %INC%
copy /Y .\Sources\slcan.h %INC%
copy /Y .\Sources\serial_attr.h %INC%

rem end of the job
:end
popd
if %VCVARS% == "True" (
   pause
)
