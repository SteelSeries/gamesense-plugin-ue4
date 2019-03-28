SETLOCAL ENABLEEXTENSIONS

SET "buildDir=%WORKSPACE%\build"
SET "ue4ScriptsPath=%programfiles%\Epic Games\UE_4.21\Engine\Build\BatchFiles"
SET "builtContentPath=%buildDir%\HostProject\Plugins\SteelSeriesGameSense"

IF NOT EXIST %buildDir% (
    MKDIR %buildDir%
) ELSE (
    DEL /Q %buildDir%\*
)

CALL "%ue4ScriptsPath%\RunUAT.bat" BuildPlugin -Plugin="%WORKSPACE%\SteelSeriesGameSense.uplugin" -Package="%buildDir%" -Rocket

IF %ERRORLEVEL% NEQ 0 (
    EXIT /B %ERRORLEVEL%
)

cd %builtContentPath%
7z a -tzip %buildDir%\gamesense-plugin-ue4.zip "Config" "Content" "Resources" "Source" "SteelSeriesGameSense.uplugin"
cd %WORKSPACE%
