%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : Test of the main function of the Parking Meter Low Level module.
%         Press the "Run" button to execute
% Copyright 2023 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#ok<*GVMIS>
clearvars -except app; clc;
global APP_DESIGNER; % To set low-level driver functions properly %#ok<*UNRCH>
global UNIT_TESTING; % To set the automated unit testing of the App to false

%% Initialization

APP_DESIGNER = true;  % 'true' => App Designer implementation, 'false' => C# App
UNIT_TESTING = false; % 'false' => Manual testing, 'true' => Automated testing.
                      % Here it MUST always be set to false, otherwise the App
                      % will be locked as no test cases are defined in the script
TEST_MEX = false;  % 'true' => Generate and test the MEX file, 'false' => No MEX
defineTestMode(1); % '1' => test mode, '0' => normal operation mode

% Text constants declaration
TEXT_RUN = 'The interface to the parking meter has been activated.';
CODEGEN_FOLDER = '..\MEX_functions\codegen';

%% Start the system to do manual testing

if (APP_DESIGNER) % No MEX of the low-level interface possible here
  % Launch the App Designer GUI
  fprintf('%s\n','Instanciation of the App Designer object...');
  if ~exist('app','var')
    % Find and remove any remaining open figures
    allApps = findall(0,'Type','figure');
    if ~isempty(allApps)
      delete(allApps);
      clear('allApps');
    end
    % Instanciate one single app interface
    app = ParkingMeterGUI;
    waitfor(app,'Running','on');
  end
  fprintf('%s\n',TEXT_RUN);
  % Call the standard MATLAB code
  parkingMeterLowLevel();
else
  % Close potential instance of the C# GUI
  if (system('taskkill -f -im ParkingMeterGUI.exe') ~= 0) %#ok<*UNRCH>
    fprintf(repmat('\b',1,54)); % Remove the useless console error message
    fprintf('No running instance of the C# GUI has been detected.\n');
  end
  % Launch the C# GUI
  system('..\\..\\ParkingMeterGUI.exe&');
  % Run the interface to the Parking Meter GUI
  if (~TEST_MEX)
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
end
