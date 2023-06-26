%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : Test of the main function of the Parking Meter Low Level module
%
% Copyright 2023 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear variables; clc;
global TEST_MODE; %#ok<GVMIS,NUSED>

% Initialization
TEST_MEX = 0; % Generate and test the MEX file if set to '1'
defineTestMode(1); % '0' => normal mode, '1' => test mode
% Text constants declaration
TEXT_RUN = 'The interface to the parking meter has been activated.';
CODEGEN_FOLDER = '..\MEX_functions\codegen';

% Close potential instance of the C# GUI
if (system('taskkill -f -im ParkingMeterGUI.exe') ~= 0)
  fprintf(repmat('\b',1,54)); % Remove the useless console error message
  fprintf('No running instance of the C# GUI has been detected.\n');
end
% Launch the C# GUI
system('..\\..\\ParkingMeterGUI.exe&');
% Run the interface to the Parking Meter GUI
if (TEST_MEX == 0)
  fprintf('%s\n',TEXT_RUN);
  % Call the standard MATLAB code
  parkingMeterLowLevel();
else
  % Generate the MEX function of the main file
  fprintf('Building the MEX file, please wait...\n');
  cfg = coder.config('mex');
  cfg.CustomSource = '..\Interface_C_files\write_register.c';
  cfg.CustomInclude = '..\Interface_C_files';
  cfg.CustomSourceCode = '#include "ParkingMeterMemory.h"';
  codegen('-config','cfg','parkingMeterLowLevel','-d',CODEGEN_FOLDER,'-report');
  fprintf('The MEX file has been built successfully.\n');
  movefile('parkingMeterLowLevel_mex.mexw64','..\MEX_functions');
  rmdir(CODEGEN_FOLDER,'s');
  fprintf('Cleaning of the C Code Generation folder.\n');
  fprintf('%s\n',TEXT_RUN);
  % Call the MEX function
  parkingMeterLowLevel_mex();
end
