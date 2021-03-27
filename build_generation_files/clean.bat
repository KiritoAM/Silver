@echo off

REM @RD /S /Q "build_output\intermediate"
del	/S /Q "build_output\*%1.exp
del	/S /Q "build_output\*%1.ilk
REM del	/S /Q "build_output\*.lib
del	/S /Q "build_output\*%1.pdb

exit /b