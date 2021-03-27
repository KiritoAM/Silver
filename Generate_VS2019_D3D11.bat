@echo off
cd /D "%~dp0"
call "build_generation_files\generate_project_files.bat" vs2019 d3d11 windows game
pause
exit