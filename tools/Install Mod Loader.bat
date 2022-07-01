@echo off

set mod_loader_path="C:\ProgramData\PopCap Games\Peggle\"
set mods_path="C:\Program Files (x86)\Steam\steamapps\common\Peggle Deluxe\mods"
xcopy "dsound.dll" %mod_loader_path% /y /q
cls

echo Haggle installed to %mod_loader_path%
echo.

IF NOT EXIST %mods_path% (
mkdir %mods_path%
echo Mods folder created at %mods_path%
echo.
)

set choice=
set /p choice=Open Mods folder? Y/N: 
if not '%choice%'=='' set choice=%choice:~0,1%
if '%choice%'=='y' goto open
if '%choice%'=='n' goto close

:close
exit

:open
explorer %mods_path%