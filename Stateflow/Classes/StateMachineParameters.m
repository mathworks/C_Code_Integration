classdef StateMachineParameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Class StateMachineParameters
% Goal  : This class contains all the inputs and outputs of the interface to the
%         state machine object.
%
% Author: Copyright 2023 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#codegen
  properties (Constant = false)
    % TS
    sampling_time   = 0.001;
    refreshing_time = 0.015;
    % Buttons trigger signals
    master_switch = true;
    green_pressed = false;
    red_pressed   = false;
    % Coins related signals
    coins_reg_value  = uint8(0);
    temp_amount      = uint8(0);
    inserted_amount  = uint16(0);
    amount_to_return = uint16(0);
    % Scheduler's output signals
    flap_open      = false;
    edge_pulse     = false;
    return_value   = uint8(0);
    register_value = uint8(0);
    display_value  = uint16(0);
    % Interrupts trigger vectors
    ISR = false(1,7);
  end
end
