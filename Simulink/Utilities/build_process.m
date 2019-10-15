function [] = build_process(mdlName)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: build_process
% Goal    : Use a generated main C file that has been customized and a generated
%          make file to create a standalone executable to run on a WIN64 desktop
%
% Author  : Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Constants
  BUILD_FOLDER  = '.\';
  UTILS_FOLDER  = '..\..\Utilities\';
  MAIN_ERT_FILE = 'ert_main.c';
  % Selection of the right set of files to build the standalone executable
  if strcmp(mdlName,'ParkingMeterLowLevel')
    MAIN_C_FILE   = 'ert_mainLowLevel.c';
    MAIN_MK_FILE  = 'ParkingMeterLowLevel.mk';
    MAIN_BAT_FILE = 'ParkingMeterLowLevel.bat';
  elseif strcmp(mdlName,'ParkingMeterSystem')
    MAIN_C_FILE   = 'ert_mainSystem.c';
    MAIN_MK_FILE  = 'ParkingMeterSystem.mk';
    MAIN_BAT_FILE = 'ParkingMeterSystem.bat';
  else
    error('Wrong model name. Build process stopped...');
  end
  % Important note:
  % To get the very first version of the generated C and make files, one option
  % in the "Code Generation" category of the "Configuration Parameters panel
  % must be set => Custom templates: Generate an example main program

  % Set the selected main C file as the main ERT C file
  copyfile([UTILS_FOLDER,MAIN_C_FILE]  , [UTILS_FOLDER,MAIN_ERT_FILE]);
  % Move the main C and the make files to the build folder
  copyfile([UTILS_FOLDER,MAIN_ERT_FILE], BUILD_FOLDER);
  copyfile([UTILS_FOLDER,MAIN_MK_FILE] , BUILD_FOLDER);
  copyfile([UTILS_FOLDER,MAIN_BAT_FILE], BUILD_FOLDER);
  disp('Build files copied successfully to the build folder.');
  % Remove the local copy of the main ERT C file
  delete([UTILS_FOLDER,MAIN_ERT_FILE])
end
