function [value] = read_app_designer(register_address) %#ok<*INUSD>
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function read_app_designer()
% Goal  : Define the interface layer reading data from App external HW registers
% IN    : - register_address: address of the register in unsigned 16 bit
% IN/OUT: -
% OUT   : - value: value to read from the register as an unsigned 8 bit
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Instantiate all constants for the normal application
  const = Constants;
  
  switch (register_address)
    case const.BUTTONS_REGISTER
      value = evalin('base','app.BUTTONS_REGISTER');
    case const.INSERTED_COINS_REGISTER
      value = evalin('base','app.INSERTED_COINS_REGISTER');
    case const.AVAILABLE_COINS_REGISTER
      value = evalin('base','app.AVAILABLE_COINS_REGISTER');
    case const.PERIPHERALS_REGISTER
      value = evalin('base','app.PERIPHERALS_REGISTER');
    otherwise
      % Do nothing as the provided address does not match any register
  end
end
