function [] = closeGUI()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function closeGUI()
% Goal  : Close the Parking Meter C# graphical interface
% IN    : -
% IN/OUT: -
% OUT   : -
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Close potential instance of the C# GUI
  if (system('taskkill -f -im ParkingMeterGUI.exe') ~= 0)
    fprintf(repmat('\b', 1, 54)); % Remove the useless console error message
    fprintf('No running instance of the C# GUI has been detected.\n');
  end
end
