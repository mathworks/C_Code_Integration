%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : Test of the main function of the Parking Meter Low Level module.
%         Press the "Run" button to execute
% Author: Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear variables; clc;
global APP_DESIGNER; % To set low-level driver functions properly %#ok<*UNRCH>

% Initialization
APP_DESIGNER = true; % 'true' => App Designer implementation, 'false' => C# App
TEST_MEX = false;  % 'true' => Generate and test the MEX file, 'false' => No MEX
defineTestMode(1); % '1' => test mode, '0' => normal operation mode

% Text constants declaration
TEXT_RUN = 'The interface to the parking meter has been activated.';
CODEGEN_FOLDER = '..\MEX_functions\codegen';

if (APP_DESIGNER) % No MEX of the low-level interface possible here
  % Close potential instance of the App Designer GUI
  clear app;
  % Launch the App Designer GUI
  fprintf('%s\n','Instanciation of the App Designer object...');
  app = ParkingMeterGUI;
  waitfor(app,'Running','on');
  fprintf('%s\n',TEXT_RUN);
  % Call the standard MATLAB code
  parkingMeterLowLevel();
else
  % Close potential instance of the C# GUI
  if (system('taskkill -f -im ParkingMeterGUI.exe') ~= 0)
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
    codegen('parkingMeterLowLevel','..\Interface_C_files\write_register.c',...
            '-d',CODEGEN_FOLDER,'-report');
    fprintf('The MEX file has been built successfully.\n');
    movefile('parkingMeterLowLevel_mex.mexw64','..\MEX_functions');
    rmdir(CODEGEN_FOLDER,'s');
    fprintf('Cleaning of the C Code Generation folder.\n');
    fprintf('%s\n',TEXT_RUN);
    % Call the MEX function
    parkingMeterLowLevel_mex();
  end
end
