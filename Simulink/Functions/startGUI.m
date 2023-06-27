function [] = startGUI()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: startGUI()
% Goal    : Launch the Parking Meter C# graphical interface to communicate with
% IN      : -
% IN/OUT  : -
% OUT     : -
%
% Copyright 2023 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Close potential instance of the C# GUI
  if (system('taskkill -f -im ParkingMeterGUI.exe') ~= 0)
    fprintf(repmat('\b', 1, 54)); % Remove the useless console error message
    fprintf('\nNo running instance of the C# GUI has been detected.\n');
  end
  % Launch the C# GUI
  system('..\\..\\ParkingMeterGUI.exe&');
end
