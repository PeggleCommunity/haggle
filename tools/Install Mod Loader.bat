@echo off

set mod_loader_path="C:\ProgramData\PopCap Games\Peggle\"
set mods_path="C:\Program Files (x86)\Steam\steamapps\common\Peggle Deluxe\mods"
set legacy_loader=%mod_loader_path%\dsound.dll
xcopy "ddraw.dll" %mod_loader_path% /y /q
cls

IF EXIST %legacy_loader% (
    echo Found legacy loader!
    echo Deleting old version...
    del %legacy_loader%
    echo.
)

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
if '%choice%'=='Y' goto open
if '%choice%'=='n' goto close
if '%choice%'=='N' goto close

:close
exit

:open
explorer %mods_path%