%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : This script check that the access to the shared memory of the Parking
%         Meter GUI from the MATLAB API works correctly.
%
% Author: Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear variables; clc;

% Constants declaration
NB_SYMBOLS = 13;
NB_NUM_SYMBOLS = 10;
NB_DISPLAYS = 3;
CONST = Constants; % Instantiate all the constants of the application

% Data vectors initialization
SEGMENTS_DIGIT = zeros(1,NB_SYMBOLS,'uint8');
DISPLAY_REGISTER = zeros(1,NB_DISPLAYS,'uint16');

% Digits definition for the 7 segments displays
for k=1:1:NB_NUM_SYMBOLS
  SEGMENTS_DIGIT(k) = eval(sprintf('CONST.SEGMENTS_DIGIT_%d',mod(k,NB_NUM_SYMBOLS)));
end
SEGMENTS_DIGIT(11) = CONST.SEGMENTS_DIGIT_M;
SEGMENTS_DIGIT(12) = CONST.SEGMENTS_DIGIT_P;
SEGMENTS_DIGIT(13) = CONST.SEGMENTS_DIGIT_E;

% 7 segments displays definition
for k=1:1:NB_DISPLAYS
  DISPLAY_REGISTER(k) = eval(sprintf('CONST.DISPLAY_REGISTER_%d',k));
  % Reset the registers values
  write_register(DISPLAY_REGISTER(k),SEGMENTS_DIGIT(NB_SYMBOLS));
end

% Launch the C# GUI
system('..\\..\\ParkingMeterGUI.exe&');

% Use the displays has counters
for n=1:1:NB_DISPLAYS
  disp(['Display number: ' num2str(n)]);
  disp(['having the address: 0x' num2str(dec2hex(DISPLAY_REGISTER(n)))]);
  disp('Segment ID #: P  G  F  E  D  C  B  A');
  for m=1:1:NB_SYMBOLS-1
    write_register(DISPLAY_REGISTER(n),SEGMENTS_DIGIT(m));
    register_data = read_register(DISPLAY_REGISTER(n));
    disp(['Bits enabled: ' num2str(de2bi(register_data,8,'left-msb'))]);
    pause(1);
  end
  disp('-------------------------------------');
end

% Close the C# GUI
system('taskkill -f -im ParkingMeterGUI.exe');
