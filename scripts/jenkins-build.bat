SETLOCAL ENABLEEXTENSIONS

IF NOT DEFINED WORKSPACE (
    SET "WORKSPACE=%CD%"
)
IF NOT DEFINED BUILD_DIR (
    SET "BUILD_DIR=%WORKSPACE%\build"
)
SET "ue4ScriptsPath=%programfiles%\Epic Games\UE_4.21\Engine\Build\BatchFiles"
SET "builtContentPath=%BUILD_DIR%\HostProject\Plugins\SteelSeriesGameSense"

IF NOT EXIST %BUILD_DIR% (
    MKDIR %BUILD_DIR%
) ELSE (
    DEL /Q %BUILD_DIR%\*
)

CALL "%ue4ScriptsPath%\RunUAT.bat" BuildPlugin -Plugin="%WORKSPACE%\SteelSeriesGameSense.uplugin" -Package="%BUILD_DIR%" -Rocket

IF %ERRORLEVEL% NEQ 0 (
    EXIT /B %ERRORLEVEL%
)

cd %builtContentPath%
7z a -tzip %BUILD_DIR%\gamesense-plugin-ue4.zip "Config" "Content" "Resources" "Source" "SteelSeriesGameSense.uplugin"
cd %WORKSPACE%
