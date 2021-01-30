%% Clean session
clear variables; clc;

global app;
% Text constants declaration
TEXT_INTERFACE = 'The parking meter interface has been activated.';
TEXT_LOW_LEVEL = 'The low-level application is up and running.';

%% Parking meter system initialization

fprintf('%s\n','Instanciation of the App Designer object...');
% Launch the App Designer GUI
app = ParkingMeterGUI;
% Temporisation to be sure the App is up and running
waitfor(app,'Running','on');
pause(2);
fprintf('%s\n',TEXT_INTERFACE);
% Close potential instance of the C# GUI
if (system('taskkill /F /im ParkingMeterProject.exe /im cmd.exe &') ~= 0)
%   fprintf(repmat('\b',1,57)); % Remove the useless console error message
  fprintf('No running instance of the low-level application has been detected.\n');
end
% Call the low-level MATLAB code of the application in a separate process
system('..\\Component\\UnitTesting\\ParkingMeterProject.exe&');

%% Call the unit testing framework

results = runtests('..\Component\UnitTesting\TestApp.m');
system('taskkill /F /im ParkingMeterProject.exe /im cmd.exe &');
