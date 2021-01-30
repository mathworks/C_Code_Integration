%% Clean session

clear variables; clc;
try
  stop(timerfind);
  delete(timerfind);
catch
  disp('No timers are running.');
end

%% Parking meter system initialization

global unitTest;
% Set to true if the MATLAB unit testing API is used, otherwise always false
unitTest = true;
% Close any potential running instance of the low-level application
if (system('taskkill /F /im ParkingMeterProject.exe /im cmd.exe &') ~= 0)
  fprintf('No running instance of the low-level application has been detected.\n');
end
% Call the low-level MATLAB code of the application in a separate process
fprintf('Starting the low-level application instance...\n');
system('..\\Component\\UnitTesting\\ParkingMeterProject.exe&');
pause(3);

%% Call the unit testing framework

results = runtests('..\Component\UnitTesting\TestApp.m');
system('taskkill /F /im ParkingMeterProject.exe /im cmd.exe &');
