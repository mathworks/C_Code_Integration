function [] = write_app_designer(register_address,value) %#ok<*INUSD>
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function write_app_designer()
% Goal  : Define the interface layer writing data to App external HW registers
% IN    : - register_address: address of the register in unsigned 16 bit
%         - value: value to store in the register as an unsigned 8 bit
% IN/OUT: -
% OUT   : -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Instantiate all constants for the normal application
  const = Constants;
  
  switch (register_address)
    case const.DISPLAY_REGISTER_1
      evalin('base',['app.NEW_DISPLAY_REGISTER_1 = ' num2str(value) ';']);
    case const.DISPLAY_REGISTER_2
      evalin('base',['app.NEW_DISPLAY_REGISTER_2 = ' num2str(value) ';']);
    case const.DISPLAY_REGISTER_3
      evalin('base',['app.NEW_DISPLAY_REGISTER_3 = ' num2str(value) ';']);
    case const.PERIPHERALS_REGISTER
      evalin('base',['app.NEW_PERIPHERALS_REGISTER = ' num2str(value) ';']);
    otherwise
      % Do nothing as the provided address does not match any register
  end
end
