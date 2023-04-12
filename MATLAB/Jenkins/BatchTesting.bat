REM Copyright 2023 The MathWorks, Inc.
@echo ================================================================================
@echo Move to the C_project folder of the built low-level application
@cd "..\C_project\ParkingMeterProject\x64\Release
@echo ================================================================================
@echo Low-level program running for the duration of the testing phase...
@start cmd.exe @cmd /k ParkingMeterProject.exe
@echo ================================================================================
@echo Move to the root folder
@cd "..\..\..\..\Jenkins"
@echo ================================================================================
@echo Starting MATLAB to run all test cases
@echo ================================================================================
@matlab -wait -log -r "JobTesting; exit"
@echo ================================================================================
@echo Unit testing in MATLAB over
@echo Closing all openned cmd windows...
@echo ================================================================================
@ping -n 3 127.0.0.1 >NUL
@taskkill /F /IM ParkingMeterProject.exe
@exit /b 0
