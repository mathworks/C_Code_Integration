%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function ParkingMeterLowLevel()
% Goal  : Main entry point of the parking meter application
% IN    : -
% IN/OUT: -
% OUT   : - error_flag: error code
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#codegen
function [] = ParkingMeterLowLevel()
  global TEST_MODE;

  % Initialization
  initialization_interface();

  if (coder.target('MATLAB') || coder.target('MEX') || coder.target('Rtw'))
  if (TEST_MODE == 0)
    % Instantiate all constants for the normal application
    const = Constants;
    fprintf('The normal mode of operation of the parking meter has been activated.\n');
    fprintf('Feel free to purchase tickets.\n');
    standard_operation_mode(const);
    fprintf('The Master Switch of the Parking Meter Interface is switched off.\n');
    fprintf('Press ''ENTER'' to close the console window...\n');
    pause();
  else % TEST_MODE == 1
    % Function handler API to access functions of the test mode
    f_h.standard_operation_mode = @standard_operation_mode;
    f_h.sleep_interface = @sleep_interface;
    f_h.read_interface = @read_interface;
    f_h.set_coin_flap_position = @set_coin_flap_position;
    f_h.give_back_coin = @give_back_coin;
    f_h.print_receipt = @print_receipt;
    f_h.switch_leds_on = @switch_leds_on;
    f_h.display_cents_value = @display_cents_value;
    f_h.write_interface = @write_interface;
    % Instantiate all properties and methods for the test mode
    test = TestMode;
    % Entry point of the test mode
    test_mode(test, f_h);
  end
  else
  fprintf('No supported coder target has been specified.\n');
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function test_mode()
% Goal  : Entry point of the test mode of the parking meter
% IN    : - test_obj: object having all needed properties and methods for the
%                     testing mode of operation
%         - f_api   : functions handler struct listing functions to access
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = test_mode(test_obj, f_api)
  % Text constant declaration
  TEXT_INPUT = ['Enter the menu entry of the operation '...
                'to do on the parking meter [0 - 8]: '];
  TEXT_RUN   = ['The normal mode of operation of the '...
                'parking meter has been activated.'];
  % Variables declaration
  choice = int32(1);
  % Split sections
  fprintf('%s\n', test_obj.TEXT_SEPARATOR);

  % Loop over the menu entries
  while (choice ~= 0)
    % Menu selection
    fprintf('Operations on the parking meter:\n');
    fprintf('>> 0 - Leave\n');
    fprintf('>> 1 - Write in registers\n');
    fprintf('>> 2 - Display an amount of money\n');
    fprintf('>> 3 - Switch on and off LEDs\n');
    fprintf('>> 4 - Give back a coin\n');
    fprintf('>> 5 - Print a parking ticket\n');
    fprintf('>> 6 - Open and close the coin''s flap\n');
    fprintf('>> 7 - Display status of input registers\n');
    fprintf('>> 8 - Normal handling of the parking meter\n');
    fprintf('\n');

    % Get and check the menu entry provided at the console interface
    choice = test_obj.check_get_data(TEXT_INPUT,...
                                     test_obj.INT_CASE_ENTRY_0,...
                                     test_obj.INT_CASE_ENTRY_8);
    fprintf('\n');
    switch (choice)
      case test_obj.INT_CASE_ENTRY_0
        break;
      case test_obj.INT_CASE_ENTRY_1
        test_obj.write_register(test_obj, f_api);
      case test_obj.INT_CASE_ENTRY_2
        test_obj.display_value(test_obj, f_api);
      case test_obj.INT_CASE_ENTRY_3
        test_obj.leds_return_money(test_obj, f_api);
      case test_obj.INT_CASE_ENTRY_4
        test_obj.give_back_coin(test_obj, f_api);
      case test_obj.INT_CASE_ENTRY_5
        print_receipt(test_obj);
        fprintf("%s\n\n", test_obj.TEXT_SEPARATOR);
      case test_obj.INT_CASE_ENTRY_6
        test_obj.coin_flap_position(test_obj, f_api);
      case test_obj.INT_CASE_ENTRY_7
        test_obj.input_registers(test_obj, f_api);
      case test_obj.INT_CASE_ENTRY_8
        fprintf('%s\n', TEXT_RUN);
        standard_operation_mode(test_obj);
      otherwise
        fprintf('Incorrect menu choice.\n');
    end
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function standard_operation_mode()
% Goal  : Entry point of the standard mode of operation of the parking meter
% IN    : - const_obj: constants object used in the entire application
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = standard_operation_mode(const_obj)
  master_switch_off = false;
  while(1)
    % Initialization
    display_cents_value(const_obj,const_obj.MINUS_VALUE);
    set_coin_flap_position(const_obj,0);
    % Waiting on user inputs
    while (1)
      % Check if the parking meter can give money back if needed
      switch_leds_on(const_obj,is_able_to_give_back_any_coins(const_obj));
      sleep_interface(const_obj.REFRESHING_TIME); % Pause the process
      % Check if the master switch is switched off
      if (~is_master_switch_on(const_obj))
        master_switch_off = true;
        break;
      end
	    % The process of a ticket purchase has been initiated
      if (is_green_button_pressed(const_obj))
        break;
      end
    end
    % Exit the program properly if the master switch is off
    if (master_switch_off)
      break;
    end
    % Open the coin's flap to let the user inserting coins
    set_coin_flap_position(const_obj, 1);
    % Go through the entire ticket purchase process
    handle_ticket_purchase(const_obj);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function handle_ticket_purchase()
% Goal  : higher abstraction level of the ticket purchase process
% IN    : - const_obj: constants object used in the entire application
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = handle_ticket_purchase(const_obj)
  % Local variable declarations
  inserted_amount = int32(0);
  temp_amount     = int32(0);
  register_value  = uint8(0);

  % Waiting for the full payment of the ticket or cancellation of the purchase
  while (inserted_amount < const_obj.TICKET_FEE)
    sleep_interface(const_obj.REFRESHING_TIME); % Pause the process
    % Update the display with the current amount of money to insert
    if (inserted_amount < const_obj.TICKET_FEE)
      display_cents_value(const_obj,const_obj.TICKET_FEE - inserted_amount);
    else
      display_cents_value(const_obj,uint8(0));
    end

    if (is_red_button_pressed(const_obj))
      % Ticket's purchase process canceled
      return_coins(const_obj, inserted_amount);
      return; % Go back to the entry point function level
    end
    % Update the amount of money to pay if a coin has been inserted
    [temp_amount, register_value] = amount_inserted_coins(const_obj,...
                                                          register_value);
    inserted_amount = inserted_amount + temp_amount;
  end
  % Printing of the parking ticket
  print_receipt(const_obj);
  % Give back coin's change
  return_coins(const_obj, inserted_amount - const_obj.TICKET_FEE);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function return_coins()
% Goal  : give back the desired amount of coins to the user
% IN    : - const_obj: constants object used in the entire application
%         - desired_amount: integer representing the money to give back
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = return_coins(const_obj, desired_amount)
  remaining_amount = int32(0); %#ok<*NASGU>
  % Return as much as possible higher coin's values at first
  remaining_amount = return_coin_value(const_obj, desired_amount,...
                                       const_obj.INT_VAL_100_CENTS);
  remaining_amount = return_coin_value(const_obj, remaining_amount,...
                                       const_obj.INT_VAL_050_CENTS);
  remaining_amount = return_coin_value(const_obj, remaining_amount,...
                                       const_obj.INT_VAL_020_CENTS);
  remaining_amount = return_coin_value(const_obj, remaining_amount,...
                                       const_obj.INT_VAL_010_CENTS);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function return_coin_value()
% Goal  : give back the remaining amount of coins to return
% IN    : - const_obj: constants object used in the entire application
%         - amount_to_return: integer representing the money to give back
%         - coin_value : integer representing the value of the current coin
% IN/OUT: -
% OUT   : -  integer representing the remaining amount of coins to return
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [remaining_amount] = return_coin_value(const_obj, amount_to_return,...
                                                coin_value)
  remaining_amount = int32(amount_to_return);
  % Try to return as much coins as possible
  while ((remaining_amount >= coin_value) &&...
          is_this_coin_available(const_obj, coin_value))
    give_back_coin(const_obj, coin_value);
    remaining_amount = remaining_amount - coin_value;
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function is_able_to_give_back_any_coins()
% Goal  : check if a specific coin's value is still available in the cash box
% IN    : - const_obj: constants object used in the entire application
% IN/OUT: -
% OUT   : - boolean stating if this coin's value is still available or not
%           '0' => coin's value not available anymore
%           '1' => coin's value still available
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [bool] = is_able_to_give_back_any_coins(const_obj)
  % Check if any coin's value is empty
  bool = (is_this_coin_available(const_obj, const_obj.INT_VAL_010_CENTS) &...
          is_this_coin_available(const_obj, const_obj.INT_VAL_020_CENTS) &...
          is_this_coin_available(const_obj, const_obj.INT_VAL_050_CENTS) &...
          is_this_coin_available(const_obj, const_obj.INT_VAL_100_CENTS));
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function is_this_coin_available()
% Goal  : check if a specific coin's value is still available in the cash box
% IN    : - const_obj: constants object used in the entire application
%         - integer representing the coin's value
% IN/OUT: -
% OUT   : - boolean stating if this coin's value is still available or not
%           '0' => coin's value not available anymore
%           '1' => coin's value still available
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [available] = is_this_coin_available(const_obj, coin_value)
  available = false;
  % Get the current register's status of the available coins in the cash box
  register_value = read_interface(const_obj.AVAILABLE_COINS_REGISTER);

  % Select the specific coin's quantity to check
  switch (coin_value)
    case const_obj.INT_VAL_010_CENTS
      available = (bitand(register_value, const_obj.BIT_MASK_010_CENTS) ~= 0);
    case const_obj.INT_VAL_020_CENTS
      available = (bitand(register_value, const_obj.BIT_MASK_020_CENTS) ~= 0);
    case const_obj.INT_VAL_050_CENTS
      available = (bitand(register_value, const_obj.BIT_MASK_050_CENTS) ~= 0);
    case const_obj.INT_VAL_100_CENTS
      available = (bitand(register_value, const_obj.BIT_MASK_100_CENTS) ~= 0);
    otherwise
      fprintf(['Incorrect coin''s value provided to '...
               'the parking meter cash box module!\n']);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function amount_inserted_coins()
% Goal  : get the amount of the inserted coins
% IN    : - const_obj: constants object used in the entire application
%         - integer representing the current amount of inserted coins
% IN/OUT: -
% OUT   : - integer representing the updated amount of inserted coins
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [new_amount, old_reg_value] = amount_inserted_coins(const_obj,...
                                                             old_reg_value)
  new_amount = int32(0);
  % Get the very last amount of coins that have already been inserted
  new_reg_value = read_interface(const_obj.INSERTED_COINS_REGISTER);

  % A new coin has been inserted into the parking meter
  if (new_reg_value ~= old_reg_value)
    % Update the amount of coins already inserted
    if (bitand(new_reg_value, const_obj.BIT_MASK_010_CENTS) ~= 0 &&...
        bitand(old_reg_value, const_obj.BIT_MASK_010_CENTS) == 0)
      new_amount = const_obj.INT_VAL_010_CENTS;
    elseif (bitand(new_reg_value, const_obj.BIT_MASK_020_CENTS) ~= 0 &&...
            bitand(old_reg_value, const_obj.BIT_MASK_020_CENTS) == 0)
      new_amount = const_obj.INT_VAL_020_CENTS;
    elseif (bitand(new_reg_value, const_obj.BIT_MASK_050_CENTS) ~= 0 &&...
            bitand(old_reg_value, const_obj.BIT_MASK_050_CENTS) == 0)
      new_amount = const_obj.INT_VAL_050_CENTS;
    elseif (bitand(new_reg_value, const_obj.BIT_MASK_100_CENTS) ~= 0 &&...
            bitand(old_reg_value, const_obj.BIT_MASK_100_CENTS) == 0)
      new_amount = const_obj.INT_VAL_100_CENTS;
    elseif (bitand(new_reg_value, const_obj.BIT_MASK_200_CENTS) ~= 0 &&...
            bitand(old_reg_value, const_obj.BIT_MASK_200_CENTS) == 0)
      new_amount = const_obj.INT_VAL_200_CENTS;
    end
    % Record of the current register value
    old_reg_value = new_reg_value;
  else
    new_amount = int32(0);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function print_receipt()
% Goal  : Command the parking meter to print the corresponding receipt
% IN    : - const_obj: constants object used in the entire application
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = print_receipt(const_obj)
  % Trigger the printing of the parking receipt
  generate_peripherals_pulse(const_obj, const_obj.BIT_MASK_PRINT_TICKET);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function give_back_coin()
% Goal  : Return coins change to the user based on computed amount of money
% IN    : - const_obj: constants object used in the entire application
%         - amount: integer value corresponding to a specific coin
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = give_back_coin(const_obj, amount)
  % Select the correct coin to give back
  switch (amount)
    case const_obj.INT_VAL_010_CENTS
      generate_peripherals_pulse(const_obj, const_obj.BIT_MASK_010_CENTS);
    case const_obj.INT_VAL_020_CENTS
      generate_peripherals_pulse(const_obj, const_obj.BIT_MASK_020_CENTS);
    case const_obj.INT_VAL_050_CENTS
      generate_peripherals_pulse(const_obj, const_obj.BIT_MASK_050_CENTS);
    case const_obj.INT_VAL_100_CENTS
      generate_peripherals_pulse(const_obj, const_obj.BIT_MASK_100_CENTS);
    otherwise
      fprintf(['Incorrect coin''s value provided to '...
               'the parking meter change module!\n']);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function switch_leds_on()
% Goal  : Open or close the coin's flap
% IN    : - const_obj: constants object used in the entire application
%         - can_give_coins_back: '1' => yes, it can give coins back
%                                '0' => no, because the cash box is empty
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = switch_leds_on(const_obj, can_give_coins_back)
  % Get the current peripherals register status
  register_value = bitand(read_interface(const_obj.PERIPHERALS_REGISTER),...
                          uint8(~const_obj.BIT_MASK_BOTH_LEDS));

  % Set the corresponding bit of the register depending on can_give_coins_back
  if (can_give_coins_back == true)
    write_interface(const_obj.PERIPHERALS_REGISTER,...
                    bitor(register_value, const_obj.BIT_MASK_RETURN_LED));
  else
    write_interface(const_obj.PERIPHERALS_REGISTER,...
                    bitor(register_value, const_obj.BIT_MASK_ADD_LED));
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function set_coin_flap_position()
% Goal  : Open or close the coin's flap
% IN    : - const_obj: constants object used in the entire application
%         - flap_open: '1' => coin flap to open
%                      '0' => coin flap to close
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = set_coin_flap_position(const_obj, flap_open)
  % Get the current peripherals register status
  register_value = read_interface(const_obj.PERIPHERALS_REGISTER);

  % Set the corresponding bit of the register depending on flap_open
  if (flap_open == true)
    register_value = bitor(register_value, const_obj.BIT_MASK_COINS_FLAP);
  else
    register_value = bitand(register_value, uint8(~const_obj.BIT_MASK_COINS_FLAP));
  end
  write_interface(const_obj.PERIPHERALS_REGISTER, register_value);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function generate_peripherals_pulse()
% Goal  : Every time an action is applied to the peripherals, the
%         corresponding bit in the peripherals register is set or reset
% IN    : - const_obj: constants object used in the entire application
%         - bit_mask: mask of the specific bit to modify in the register
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = generate_peripherals_pulse(const_obj, bit_mask)
  % Read the current value stored in the register
  register_value = read_interface(const_obj.PERIPHERALS_REGISTER);

  % Set the selected bit to '1' and write the new value to the register
  register_value = bitor(register_value, bit_mask);
  write_interface(const_obj.PERIPHERALS_REGISTER, register_value);
  sleep_interface(const_obj.PULSE_DURATION);

  % Reset the selected bit only and write the new value to the register
  register_value = bitxor(register_value, bit_mask);
  write_interface(const_obj.PERIPHERALS_REGISTER, register_value);
  sleep_interface(const_obj.PULSE_DURATION);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function is_red_button_pressed()
% Goal  : Poll the button register when needed to see if the red button has
%         been pressed to cancel the ticket purchase process
% IN    : - const_obj: constants object used in the entire application
% IN/OUT: -
% OUT   : - boolean: '0' => red button not pressed
%                    '1' => red button pressed
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [bool] = is_red_button_pressed(const_obj)
  % Bit mask to extract red button status
  bool = (bitand(read_interface(const_obj.BUTTONS_REGISTER),...
                 const_obj.BIT_MASK_RED_BUTTON) ~= 0);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function is_green_button_pressed()
% Goal  : Poll the button register continuously to see if the green button
%         has been pressed
% IN    : - const_obj: constants object used in the entire application
% IN/OUT: -
% OUT   : - boolean: '0' => green button not pressed
%                    '1' => green button pressed
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [bool] = is_green_button_pressed(const_obj)
  % Bit mask to extract green button status
  bool = (bitand(read_interface(const_obj.BUTTONS_REGISTER),...
                 const_obj.BIT_MASK_GREEN_BUTTON) ~= 0);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function is_master_switch_on()
% Goal  : Poll the button register continuously to see if the master switch
%         has been switched off
% IN    : -
% IN/OUT: -
% OUT   : - boolean: '0' => master switch OFF
%                    '1' => master switch ON
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [bool] = is_master_switch_on(const_obj)
	% Bit mask to extract master switch status
  bool = (bitand(read_interface(const_obj.BUTTONS_REGISTER),...
                 const_obj.BIT_MASK_MASTER_SWITCH) ~= 0);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function display_cents_value()
% Goal  : Update the new parking meter cents value
% IN    : - const_obj: constants object used in the entire application
%         - cents_value: base 10 value to display on all 7 segments displays
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = display_cents_value(const_obj, cents_value)
  % Initialization value of the parking meter display
  if (cents_value == const_obj.MINUS_VALUE)
    display_digit(const_obj, const_obj.DISPLAY_1, const_obj.MINUS_VALUE, 0);
    display_digit(const_obj, const_obj.DISPLAY_2, const_obj.MINUS_VALUE, 0);
    display_digit(const_obj, const_obj.DISPLAY_3, const_obj.MINUS_VALUE, 0);
  % Compute the right value to display on the parking meter
  elseif (cents_value >= int32(0) && cents_value <= int32(999))
    % Compute the cent
    digit_value = mod(cents_value, 10);
    remainder   = cents_value - digit_value;
    display_digit(const_obj, const_obj.DISPLAY_1, digit_value, 0);
    % Compute the tens of cents
    remainder   = remainder/10;
    digit_value = mod(remainder, 10);
    remainder   = remainder - digit_value;
    display_digit(const_obj, const_obj.DISPLAY_2, digit_value, 0);
    % Compute the hundreds of cents
    remainder   = remainder/10;
    digit_value = mod(remainder, 10);
    display_digit(const_obj, const_obj.DISPLAY_3, digit_value, 1);
  else
    fprintf('Incorrect cents value provided to the parking meter display!\n');
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function display_digit()
% Goal  : Update a 7 segments display with a new digit value
% IN    : - const_obj: constants object used in the entire application
%         - display_ID : identification number of the 7 segments display
%         - digit_value: base 10 value to display on the 7 segments display
%         - dot_segment: enable the dot segment => '1'
%                        do not enable the dot segment => '0'
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = display_digit(const_obj, display_ID, digit_value, dot_segment)
  % New 7 segments encoded value to write in the corresponding HW register
  % Assignment of the new digit value to display
  switch (digit_value)
    case const_obj.INT_CASE_ENTRY_0
      new_reg_value = const_obj.SEGMENTS_DIGIT_0;
    case const_obj.INT_CASE_ENTRY_1
      new_reg_value = const_obj.SEGMENTS_DIGIT_1;
    case const_obj.INT_CASE_ENTRY_2
      new_reg_value = const_obj.SEGMENTS_DIGIT_2;
    case const_obj.INT_CASE_ENTRY_3
      new_reg_value = const_obj.SEGMENTS_DIGIT_3;
    case const_obj.INT_CASE_ENTRY_4
      new_reg_value = const_obj.SEGMENTS_DIGIT_4;
    case const_obj.INT_CASE_ENTRY_5
      new_reg_value = const_obj.SEGMENTS_DIGIT_5;
    case const_obj.INT_CASE_ENTRY_6
      new_reg_value = const_obj.SEGMENTS_DIGIT_6;
    case const_obj.INT_CASE_ENTRY_7
      new_reg_value = const_obj.SEGMENTS_DIGIT_7;
    case const_obj.INT_CASE_ENTRY_8
      new_reg_value = const_obj.SEGMENTS_DIGIT_8;
    case const_obj.INT_CASE_ENTRY_9
      new_reg_value = const_obj.SEGMENTS_DIGIT_9;
    case const_obj.INT_CASE_ENTRY_M
      new_reg_value = const_obj.SEGMENTS_DIGIT_M;
    otherwise
      % Incorrect 7 segments encoded value given to the selected HW register
      new_reg_value = const_obj.SEGMENTS_DIGIT_E;
  end
  % Add the encoding of the dot segment if needed
  if (dot_segment == 1)
    new_reg_value = bitor(new_reg_value, const_obj.SEGMENTS_DIGIT_P);
  end

  % Update of the desired display
  switch (display_ID)
    case 1
      write_interface(const_obj.DISPLAY_REGISTER_1, new_reg_value);
    case 2
      write_interface(const_obj.DISPLAY_REGISTER_2, new_reg_value);
    case 3
      write_interface(const_obj.DISPLAY_REGISTER_3, new_reg_value);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Interface layer definition for target dependent HW
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function initialization_interface()
% Goal  : Define the interface layer to initialize the main function
% IN    : -
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = initialization_interface()
  if coder.target('MATLAB')
  pause('on'); % Allow to stop MATLAB temporarily
  elseif (coder.target('MEX') || coder.target('Rtw'))
  % Set Coder settings to add the needed headers and sources paths
  coder.updateBuildInfo('addIncludePaths', '$(START_DIR)\Interface_C_files');
  coder.updateBuildInfo('addSourcePaths', '$(START_DIR)\Interface_C_files');
  % Include the header file containing the needed functions declarations
  coder.cinclude('ParkingMeterMemory.h');
  else
  fprintf('No supported coder target has been specified.\n');
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function sleep_interface()
% Goal  : Define the interface layer to pause the system for an amount of time
% IN    : - duration: time duration in seconds
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = sleep_interface(duration)
  if coder.target('MATLAB')
  pause(duration);
  else
  coder.ceval('Sleep', int32(duration*1000)); % Sleep asks milliseconds as input
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function read_interface()
% Goal  : Define the interface layer reading data from external HW registers
% IN    : - register_address: address of the register in unsigned 16 bit
% IN/OUT: -
% OUT   : - register_value: value stored in the register as an unsigned 8 bit
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [register_value] = read_interface(register_address)
  if coder.target('MATLAB')
  register_value = read_register(register_address);
  else
  coder.updateBuildInfo('addSourceFiles','read_register.c');
  register_value = uint8(0);
  register_value = coder.ceval('read_register', register_address);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function write_interface()
% Goal  : Define the interface layer writing data to external HW registers
% IN    : - register_address: address of the register in unsigned 16 bit
%         - new_value: value to store in the register as an unsigned 8 bit
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [] = write_interface(register_address, new_value)
  if coder.target('MATLAB')
  write_register(register_address, new_value);
  else
  coder.updateBuildInfo('addSourceFiles','write_register.c');
  coder.ceval('write_register', register_address, new_value);
  end
end
