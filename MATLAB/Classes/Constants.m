classdef Constants
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Class Constants
% Goal  : This class contains all the global constants needed in the Parking
%         Meter Low Level program.
%         Once an object has been created out of this class, it must then be
%         passed has an input argument to all the functions of the application.
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#codegen
  properties (Constant = true)
    % Binary encoding of base 10 digits for the 7 segments displays
    SEGMENTS_DIGIT_0 = char2dec('0b00111111');
    SEGMENTS_DIGIT_1 = char2dec('0b00000110');
    SEGMENTS_DIGIT_2 = char2dec('0b01011011');
    SEGMENTS_DIGIT_3 = char2dec('0b01001111');
    SEGMENTS_DIGIT_4 = char2dec('0b01100110');
    SEGMENTS_DIGIT_5 = char2dec('0b01101101');
    SEGMENTS_DIGIT_6 = char2dec('0b01111101');
    SEGMENTS_DIGIT_7 = char2dec('0b00000111');
    SEGMENTS_DIGIT_8 = char2dec('0b01111111');
    SEGMENTS_DIGIT_9 = char2dec('0b01101111');
    SEGMENTS_DIGIT_M = char2dec('0b01000000');
    SEGMENTS_DIGIT_P = char2dec('0b10000000');
    SEGMENTS_DIGIT_E = char2dec('0b00000000');

    % Bit mask encoding of coins
    BIT_MASK_010_CENTS = char2dec('0x01');
    BIT_MASK_020_CENTS = char2dec('0x02');
    BIT_MASK_050_CENTS = char2dec('0x04');
    BIT_MASK_100_CENTS = char2dec('0x08');
    BIT_MASK_200_CENTS = char2dec('0x10');
    % Bit mask encoding of buttons
    BIT_MASK_GREEN_BUTTON  = char2dec('0x01');
    BIT_MASK_RED_BUTTON    = char2dec('0x02');
    BIT_MASK_MASTER_SWITCH = char2dec('0x04');
    % Bit mask encoding of the ticket
    BIT_MASK_PRINT_TICKET = char2dec('0x10');
    % Bit mask encoding of LEDs
    BIT_MASK_RETURN_LED = char2dec('0x20');
    BIT_MASK_ADD_LED    = char2dec('0x40');
    BIT_MASK_BOTH_LEDS  = char2dec('0x60');
    % Bit mask encoding of the coin's flap
    BIT_MASK_COINS_FLAP = char2dec('0x80');

    % Integer values of coins
    INT_VAL_010_CENTS = int32(10);
    INT_VAL_020_CENTS = int32(20);
    INT_VAL_050_CENTS = int32(50);
    INT_VAL_100_CENTS = int32(100);
    INT_VAL_200_CENTS = int32(200);

    % Integer values of switch cases constructs
    INT_CASE_ENTRY_0 = int32(0);
    INT_CASE_ENTRY_1 = int32(1);
    INT_CASE_ENTRY_2 = int32(2);
    INT_CASE_ENTRY_3 = int32(3);
    INT_CASE_ENTRY_4 = int32(4);
    INT_CASE_ENTRY_5 = int32(5);
    INT_CASE_ENTRY_6 = int32(6);
    INT_CASE_ENTRY_7 = int32(7);
    INT_CASE_ENTRY_8 = int32(8);
    INT_CASE_ENTRY_9 = int32(9);
    INT_CASE_ENTRY_M = int32(45); % ASCII code for '-'

    % 7 segments displays identifiers
    DISPLAY_1 = uint8(1); 
    DISPLAY_2 = uint8(2); 
    DISPLAY_3 = uint8(3); 
    % Parking meter system constants 
    MINUS_VALUE     = Constants.INT_CASE_ENTRY_M; % Must be identical 
    TICKET_FEE      = int32(120);
    PULSE_DURATION  = 0.1;
    REFRESHING_TIME = 0.01;
    % Addresses of the registers accessed by the 7segments displays
    DISPLAY_REGISTER_1 = char2dec('0xA000');
    DISPLAY_REGISTER_2 = char2dec('0xA001');
    DISPLAY_REGISTER_3 = char2dec('0xA002');
    % Addresses of the registers accessed by the system's peripherals/inputs
    PERIPHERALS_REGISTER     = char2dec('0xA003');
    BUTTONS_REGISTER         = char2dec('0xA010');
    INSERTED_COINS_REGISTER  = char2dec('0xA011');
    AVAILABLE_COINS_REGISTER = char2dec('0xA012');
  end
end
