REM Copyright 2024 The MathWorks, Inc.
@echo ================================================================================
@echo Starting MATLAB to generate C code automatically for the low-level application
@echo ================================================================================
@matlab -wait -log -r "JobCodegen; exit"
@echo ================================================================================
@echo C code generatoin in MATLAB over
@echo ================================================================================
@exit /b 0
