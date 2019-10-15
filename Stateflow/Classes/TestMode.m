classdef TestMode < Constants
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Class TestMode
% Goal  : This subclass contains all the global constants needed for the test
%         mode of the Parking Meter Low Level program.
%         Once an object has been created out of the superclass, it must then be
%         passed has an input argument to all the functions of the application.
%
% Copyright 2019 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#codegen
  % The following constants will be added to the superclass "Constants"
  properties (Constant = true)
    NB_REGISTERS = 7;
    NB_VALUES    = 12;
    MILLISECONDS = 1000;
    WAIT_TIME = 100;
    REGISTERS = [Constants.DISPLAY_REGISTER_1,...
                 Constants.DISPLAY_REGISTER_2,...
                 Constants.DISPLAY_REGISTER_3,...
                 Constants.PERIPHERALS_REGISTER,...
                 Constants.BUTTONS_REGISTER,...
                 Constants.INSERTED_COINS_REGISTER,...
                 Constants.AVAILABLE_COINS_REGISTER];
    DISPLAYS_VALUES = [Constants.SEGMENTS_DIGIT_0,Constants.SEGMENTS_DIGIT_1,...
                       Constants.SEGMENTS_DIGIT_2,Constants.SEGMENTS_DIGIT_3,...
                       Constants.SEGMENTS_DIGIT_4,Constants.SEGMENTS_DIGIT_5,...
                       Constants.SEGMENTS_DIGIT_6,Constants.SEGMENTS_DIGIT_7,...
                       Constants.SEGMENTS_DIGIT_8,Constants.SEGMENTS_DIGIT_9,...
                       Constants.SEGMENTS_DIGIT_M,Constants.SEGMENTS_DIGIT_P];
    % Char separator to split sections
    TEXT_SEPARATOR = ['---------------------------------------'...
                      '----------------------------------------'];
    NEW_LINE = char(10); %#ok<CHARTEN>
  end
  
  methods(Static) %#ok<*NASGU>
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function check_get_data()
    % Goal  : Test the write access function to any shared memory register
    % IN    : - promp_text: pointer to a chain char to display in the console
    %         - min_data  : minimum value that is allowed in the range of data
    %         - max_data  : maximum value that is allowed in the range of data
    % IN/OUT: -
    % OUT   : - integer value to get from the console interface
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [data] = check_get_data(promp_text,min_data,max_data)
      % Function that is not translated into C code
      coder.extrinsic('input');
      
      % Variables declaration
      data_double = 0;
      data = int32(0);
      is_right_value = false;

      % Get and check the data from the console
      while (is_right_value == false)
        if (coder.target('MATLAB') || coder.target('MEX'))
        % Get input data using the MATLAB API
        data_text = input(promp_text,'s');
        data_double = str2double(data_text);
        % Check if the value is an integer number
        if (~isnan(data_double) && (fix(data_double) == data_double))
          data = int32(data_double);
          % Check if the value is an integer number within the allowed range
          if ((data >= min_data) && (data <= max_data))
            % The input data is valid and can be returned
            is_right_value = true;
          else
            fprintf('The value provided must be between %d and %d!\n',...
                    int32(min_data),int32(max_data));
          end
        else
          fprintf('The value to provide must be an integer between %d and %d!\n',...
                  int32(min_data),int32(max_data));
        end
        elseif coder.target('Rtw')
        % Get input data using the Windows C API
        nb_input_types = int32(0);
        terminator = ' ';
        fprintf('%s',promp_text);
        % Force the string format definition in the generated C code for scanf_s
        format = coder.opaque('char *','"%d%c"');
        nb_input_types = coder.ceval('scanf_s',format,coder.ref(data),...
                                     coder.ref(terminator),int32(1));
        % Check if the provided data is an integer number
        if (nb_input_types == 2 && strcmp(terminator,TestMode.NEW_LINE))
          % Check if the value is within the allowed range
          if ((data >= min_data) && (data <= max_data))
            is_right_value = true;
          else
            fprintf('The value provided must be between %d and %d!\n',...
                    int32(min_data),int32(max_data));
          end
        else
          fprintf('The value provided is not of the right data type!\n');
          % Force the string regular expression in the generated C code for scanf_s
          CLEAR_STDIN = coder.opaque('char *','"%*[^\n]%*1[\n]"');
          % Clear the input buffer
          coder.ceval('scanf_s',CLEAR_STDIN);
        end
        else % coder.target
        fprintf('No supported coder target has been specified.\n');
        end
      end
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function write_register()
    % Goal  : Test the write access function to any shared memory register
    % IN    : - const_obj: object containing all needed constants
    %         - f_api    : functions handler struct listing functions to access
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [] = write_register(const_obj,f_api)
      % Function that is not translated into C code
      coder.extrinsic('input');
      
      % Text constants declaration
      TEXT_INTRO  = ['Enter the address of the register to access in '...
                     'hexadecimal within the following range [0xA000-0xA003]'...
                     ' or [0xA010-0xA012]: '];
      TEXT_INPUT  = 'Enter the integer data to write at the selected register: ';
      TEXT_RESULT = ['The desired value has been successfully '...
                     'written in the selected register.'];

      % Variables declaration
      register_address = uint16(0);
      data = int32(0);
      is_right_value = false;

      % Split sections 
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);

      % Get the address of the register to access 
      while (is_right_value == false)
        if (coder.target('MATLAB') || coder.target('MEX'))
        register_address = input(TEXT_INTRO);
        elseif coder.target('Rtw')
        register_text = int32(0);
        fprintf('%s',TEXT_INTRO);
        % Force the string format definition in the generated C code for scanf_s
        format = coder.opaque('char *','"%x"');
        coder.ceval('scanf_s',format,coder.wref(register_text));
        register_address = uint16(register_text);
        else
        fprintf('No supported coder target has been specified.\n');
        end

        % Check if the provided address is pointing to an existing register 
        for i=1:1:const_obj.NB_REGISTERS
          if (register_address == const_obj.REGISTERS(i))
            is_right_value = true;
            break;
          end
        end
        % The provided address is not within the right range of addresses 
        if (is_right_value == false)
          fprintf('The address provided is not within the right range of addresses!\n');
          if coder.target('Rtw')
          % Force the string regular expression in the generated C code for scanf_s
          CLEAR_STDIN = coder.opaque('char *','"%*[^\n]%*1[\n]"');
          % Clear the input buffer
          coder.ceval('scanf_s',CLEAR_STDIN);
          end
        end
      end

      % Get the data to write in the register 
      data = const_obj.check_get_data(TEXT_INPUT,int32(0),int32(999));

      % Write the user's data to the selected register 
      f_api.write_interface(register_address,data);
      fprintf('%s\n\n',TEXT_RESULT);
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function display_value()
    % Goal  : Test the 7 segments displays by displaying any value on them
    % IN    : - const_obj: object containing all needed constants
    %         - f_api    : functions handler struct listing functions to access
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [] = display_value(const_obj,f_api)
      % Text constants declaration 
      TEXT_INPUT  = ['Enter the hundreds of cents value to '...
                     'print on the 7 segments displays: '];
      TEXT_RESULT = ['The desired value has been successfully '...
                     'written on the 7 segments displays.'];

      % Variables declaration 
      data = int32(0);

      % Split sections 
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);

      % Get the data to write in the register 
      data = const_obj.check_get_data(TEXT_INPUT,int32(0),int32(999));

      % Write the user's data to the 7 segments displays 
      f_api.display_cents_value(const_obj,data);
      fprintf('%s\n\n',TEXT_RESULT);
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function leds_return_money()
    % Goal  : Test the LEDs showing if coins can be given back or not
    % IN    : - const_obj: object containing all needed constants
    %         - f_api    : functions handler struct listing functions to access
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [] = leds_return_money(const_obj,f_api)
      % Text constants declaration 
      TEXT_INPUT  = 'State value of the give back cash LEDs [0-1]: ';
      TEXT_RESULT = ['The desired value has been successfully'...
                     'written to the give back cash LEDs.'];

      % Variables declaration 
      state = int32(0);

      % Split sections 
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);

      % Get the data to write in the register 
      state = const_obj.check_get_data(TEXT_INPUT,int32(0),int32(1));

      % Write the user's data to the 7 segments displays 
      f_api.switch_leds_on(const_obj,state);
      fprintf('%s\n\n',TEXT_RESULT);
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function give_back_coin()
    % Goal  : Test if coins are given back correctly or not
    % IN    : - const_obj: object containing all needed constants
    %         - f_api    : functions handler struct listing functions to access
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [] = give_back_coin(const_obj,f_api)
      % Text constants declaration 
      TEXT_INPUT = ['Enter the menu entry corresponding to '...
                    'the coins value to give back [0-4]: '];

      % Variables declaration 
      coin_choice = int32(1);

      % Split sections 
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);

      % Loop over the menu entries
      while (coin_choice ~= 0)
        % Menu selection 
        fprintf('Test menu to give back coins:\n');
        fprintf('>> 0 - Leave\n');
        fprintf('>> 1 - Give back a  10 cents coin\n');
        fprintf('>> 2 - Give back a  20 cents coin\n');
        fprintf('>> 3 - Give back a  50 cents coin\n');
        fprintf('>> 4 - Give back a 100 cents coin\n');
        fprintf('\n');
        % Get and check the menu entry provided at the console interface 
        coin_choice = const_obj.check_get_data(TEXT_INPUT,int32(0),int32(4));

        % Select the specific coin's value to give back 
        switch (coin_choice)
          case const_obj.INT_CASE_ENTRY_0
            % Split sections
            fprintf('%s\n\n',const_obj.TEXT_SEPARATOR);
            break;
          case const_obj.INT_CASE_ENTRY_1
            f_api.give_back_coin(const_obj,const_obj.INT_VAL_010_CENTS);
          case const_obj.INT_CASE_ENTRY_2
            f_api.give_back_coin(const_obj,const_obj.INT_VAL_020_CENTS);
          case const_obj.INT_CASE_ENTRY_3
            f_api.give_back_coin(const_obj,const_obj.INT_VAL_050_CENTS);
          case const_obj.INT_CASE_ENTRY_4
            f_api.give_back_coin(const_obj,const_obj.INT_VAL_100_CENTS);
          otherwise
            fprintf(['Incorrect menu selection. '...
                     'Please enter a value between 0 and 4.\n']);
            break;
        end
      end
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function coin_flap_position()
    % Goal  : Test if the coin's flap can be opened and closed
    % IN    : - const_obj: object containing all needed constants
    %         - f_api    : functions handler struct listing functions to access
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [] = coin_flap_position(const_obj,f_api)
      % Text constants declaration 
      TEXT_INPUT = ['Set the position of the coin''s flap '...
                    '[open => ''1'', close => ''0'']: '];

      % Variables declaration 
      flap_position = false;

      % Split sections 
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);

      % Get and check the flap position provided at the console interface 
      flap_position = logical(const_obj.check_get_data(TEXT_INPUT,int32(0),int32(1)));

      % Update the position of the flap 
      f_api.set_coin_flap_position(const_obj,flap_position);
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function input_registers()
    % Goal  : Read for a desired time the current status of the input registers
    % IN    : - const_obj: object containing all needed constants
    %         - f_api    : functions handler struct listing functions to access
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function [] = input_registers(const_obj,f_api)
      % Include the header file containing the needed functions declarations
      coder.cinclude('stdlib.h');
      coder.cinclude('ParkingMeterMemory.h');
      % Text constants declaration 
      TEXT_INPUT = ['Enter the desired time to read the input'...
                    'registers in seconds [''1''-''100'']: '];

      % Split sections 
      fprintf('%s\n',const_obj.TEXT_SEPARATOR);

      % Get and check the time limit provided at the console interface 
      monitoring_time = (const_obj.MILLISECONDS/const_obj.WAIT_TIME)*...
                         const_obj.check_get_data(TEXT_INPUT,int32(1),int32(100));

      % Read the input registers continuously 
      for i=1:1:monitoring_time+1
        fprintf('%s\n',const_obj.TEXT_SEPARATOR); % Split measurements 
        fprintf('Available coins: %x\n',...
                f_api.read_interface(const_obj.AVAILABLE_COINS_REGISTER));
        fprintf('Inserted coins : %x\n',...
                f_api.read_interface(const_obj.INSERTED_COINS_REGISTER));
        fprintf('Pushed buttons : %x\n',...
                f_api.read_interface(const_obj.BUTTONS_REGISTER));
        fprintf('Elapsed time   : %3.1f\n',...
                single(i*const_obj.WAIT_TIME/const_obj.MILLISECONDS));
        f_api.sleep_interface(const_obj.WAIT_TIME/const_obj.MILLISECONDS);
      end

      % Split sections 
      fprintf('%s\n\n',const_obj.TEXT_SEPARATOR);
    end
  end
end
