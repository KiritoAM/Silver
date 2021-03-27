@echo off

echo Deleting intermediate folder and lib files (from the binary directory)...
call "build_generation_files\clean.bat" %4
echo:

echo Generating Visual Studio solution...
build_generation_files\premake5.exe --file=build_generation_files\premake.lua %*

exit /b
