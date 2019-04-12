SETLOCAL ENABLEEXTENSIONS

@REM The UE_VERSION variable should be set by the jenkinsfile as a parameter
IF NOT DEFINED UE_VERSION (
    SET "UE_VERSION=4.21"
)

IF NOT DEFINED WORKSPACE (
    SET "WORKSPACE=%CD%"
)
IF NOT DEFINED BUILD_DIR (
    SET "BUILD_DIR=%WORKSPACE%\build"
)
SET "ue4ScriptsPath=%programfiles%\Epic Games\UE_%UE_VERSION%\Engine\Build\BatchFiles"

IF NOT EXIST %BUILD_DIR% (
    MKDIR %BUILD_DIR%
) ELSE (
    DEL /Q %BUILD_DIR%\*
    FOR /D %%p IN (%BUILD_DIR%\*) DO RMDIR /S /Q "%%p"
)

CALL "%ue4ScriptsPath%\RunUAT.bat" BuildPlugin -Plugin="%WORKSPACE%\SteelSeriesGameSense.uplugin" -Package="%BUILD_DIR%" -Rocket
