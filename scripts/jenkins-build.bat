SETLOCAL ENABLEEXTENSIONS

IF NOT DEFINED WORKSPACE (
    SET "WORKSPACE=%CD%"
)
IF NOT DEFINED BUILD_DIR (
    SET "BUILD_DIR=%WORKSPACE%\build"
)
SET "ue4ScriptsPath=%programfiles%\Epic Games\UE_4.21\Engine\Build\BatchFiles"

IF NOT EXIST %BUILD_DIR% (
    MKDIR %BUILD_DIR%
) ELSE (
    DEL /Q %BUILD_DIR%\*
)

CALL "%ue4ScriptsPath%\RunUAT.bat" BuildPlugin -Plugin="%WORKSPACE%\SteelSeriesGameSense.uplugin" -Package="%BUILD_DIR%" -Rocket
