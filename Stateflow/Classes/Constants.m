classdef Constants
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Class Constants
% Goal  : This class contains all the global constants needed in the Parking
%         Meter Low Level program.
%         Once an object has been created out of this class, it must then be
%         passed has an input argument to all the functions of the application.
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#codegen
  properties (Constant = true)
    % Binary encoding of base 10 digits for the 7 segments displays
    SEGMENTS_DIGIT_0 = 0b00111111;
    SEGMENTS_DIGIT_1 = 0b00000110;
    SEGMENTS_DIGIT_2 = 0b01011011;
    SEGMENTS_DIGIT_3 = 0b01001111;
    SEGMENTS_DIGIT_4 = 0b01100110;
    SEGMENTS_DIGIT_5 = 0b01101101;
    SEGMENTS_DIGIT_6 = 0b01111101;
    SEGMENTS_DIGIT_7 = 0b00000111;
    SEGMENTS_DIGIT_8 = 0b01111111;
    SEGMENTS_DIGIT_9 = 0b01101111;
    SEGMENTS_DIGIT_M = 0b01000000;
    SEGMENTS_DIGIT_P = 0b10000000;
    SEGMENTS_DIGIT_E = 0b00000000;

    % Bit mask encoding of coins
    BIT_MASK_010_CENTS = 0x01;
    BIT_MASK_020_CENTS = 0x02;
    BIT_MASK_050_CENTS = 0x04;
    BIT_MASK_100_CENTS = 0x08;
    BIT_MASK_200_CENTS = 0x10;
    BIT_MASK_CHANGE_COINS = 0x0F;
    % Bit mask encoding of buttons
    BIT_MASK_GREEN_BUTTON  = 0x01;
    BIT_MASK_RED_BUTTON    = 0x02;
    BIT_MASK_MASTER_SWITCH = 0x04;
    % Bit mask encoding of the ticket
    BIT_MASK_PRINT_TICKET = 0x10;
    % Bit mask encoding of LEDs
    BIT_MASK_RETURN_LED = 0x20;
    BIT_MASK_ADD_LED    = 0x40;
    BIT_MASK_BOTH_LEDS  = 0x60;
    % Bit mask encoding of the coin's flap
    BIT_MASK_COINS_FLAP = 0x80;

    % Integer values of coins
    INT_VAL_010_CENTS = uint16(10);
    INT_VAL_020_CENTS = uint16(20);
    INT_VAL_050_CENTS = uint16(50);
    INT_VAL_100_CENTS = uint16(100);
    INT_VAL_200_CENTS = uint16(200);

    % Integer values of switch cases constructs
    INT_CASE_ENTRY_0 = uint16(0);
    INT_CASE_ENTRY_1 = uint16(1);
    INT_CASE_ENTRY_2 = uint16(2);
    INT_CASE_ENTRY_3 = uint16(3);
    INT_CASE_ENTRY_4 = uint16(4);
    INT_CASE_ENTRY_5 = uint16(5);
    INT_CASE_ENTRY_6 = uint16(6);
    INT_CASE_ENTRY_7 = uint16(7);
    INT_CASE_ENTRY_8 = uint16(8);
    INT_CASE_ENTRY_9 = uint16(9);
    INT_CASE_ENTRY_M = uint16(45); % ASCII code for '-'

    % 7 segments displays identifiers
    NB_DISPLAYS = uint8(3);
    DISPLAY_1   = uint8(1);
    DISPLAY_2   = uint8(2);
    DISPLAY_3   = uint8(3);
    % Parking meter system constants 
    MINUS_VALUE     = Constants.INT_CASE_ENTRY_M; % Must be identical 
    TICKET_FEE      = uint16(120);
    PULSE_DURATION  = 0.25;
    REFRESHING_TIME = 0.01;
    % Addresses of the registers accessed by the 7segments displays
    DISPLAY_REGISTER_1 = 0xA000;
    DISPLAY_REGISTER_2 = 0xA001;
    DISPLAY_REGISTER_3 = 0xA002;
    % Addresses of the registers accessed by the system's peripherals/inputs
    PERIPHERALS_REGISTER     = 0xA003;
    BUTTONS_REGISTER         = 0xA010;
    INSERTED_COINS_REGISTER  = 0xA011;
    AVAILABLE_COINS_REGISTER = 0xA012;
  end
end
