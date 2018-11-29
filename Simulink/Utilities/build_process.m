function [] = build_process()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script: build_process
% Goal  : Use a generated main C file that has been customized and a generated
%         make file to create a standalone executable to run on a WIN64 desktop.
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Constants
  BUILD_FOLDER  = '.\';
  UTILS_FOLDER  = '..\..\Utilities\';
  MAIN_C_FILE   = 'ert_main.c';
  MAIN_MK_FILE  = 'ParkingMeterLowLevel.mk';
  MAIN_BAT_FILE = 'ParkingMeterLowLevel.bat';
  % Important note:
  % To get the very first version of the generated C and make files, one option
  % in the "Code Generation" category of the "Configuration Parameters panel
  % must be set => Template: Generate an example main program

  % Move the main C and the make files to the build folder
  copyfile([UTILS_FOLDER,MAIN_C_FILE]  , BUILD_FOLDER);
  copyfile([UTILS_FOLDER,MAIN_MK_FILE] , BUILD_FOLDER);
  copyfile([UTILS_FOLDER,MAIN_BAT_FILE], BUILD_FOLDER);
  disp('Build files copied successfully to the build folder.');
end
