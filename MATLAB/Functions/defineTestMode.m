%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function defineTestMode()
% Goal  : contains and sets the only global variable of the project that is used
%         to toggle the mode of the Parking Meter Low Level program.
%         TEST_MODE = int32(0) => normal mode of operation will run
%         TEST_MODE = int32(1) => test mode framework will run
% IN    : - test_mode_on: define the operation mode of the program
% IN/OUT: -
% OUT   : - 
%
% Author: Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = defineTestMode(test_mode_on)
  global TEST_MODE;
  if (nargin ~= 1 || (test_mode_on ~= 0 && test_mode_on ~= 1))
    TEST_MODE = int32(0); % Disable the test mode by default
  else
    TEST_MODE = int32(test_mode_on);
  end
end
