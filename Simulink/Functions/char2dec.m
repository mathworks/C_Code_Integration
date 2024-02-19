function [dec_value] = char2dec(char_sequence)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: char2dec()
% Goal    : Convert a number encoded in binary or hexadecimal base to decimal
% IN      : - char_sequence: char representation of the encoded value with the
%           prefix for the encoding format: '0b' = binary and '0x' = hexadecimal
% IN/OUT  : -
% OUT     : - dec_value: decimal representation of the char sequence
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#codegen
  % Local constants declaration
  FORMAT_LENGTH = 2; % Number of chars for the format of the encoded value
  HEXA_PER_BYTE = 2; % Number of hexa digit per byte
  % Get the input number format of the value to store
  char_format = char_sequence(1:FORMAT_LENGTH);
  % Get the encoded value to store
  char_value = char_sequence(FORMAT_LENGTH+1:end);
  % Get the length of the encode value
  length_value = length(char_value);

  % Apply the right conversion based on the data format
  switch (char_format)
    case '0b'
      % Convert the binary char input to a UINT8 with LSB first
      dec_value = uint8(bi2de(char_value == '1', 'left-msb'));
    case '0x'
      if (length_value == HEXA_PER_BYTE)
        % Convert the hexa char input to a UINT8
        dec_value = uint8(hex2dec(char_value));
      elseif (length_value == 2*HEXA_PER_BYTE)
        % Convert the hexa char input to a UINT16
        dec_value = uint16(hex2dec(char_value));
      else
        dec_value = uint16(0);
        fprintf('Unsupported hexadecimal size.\n');
      end
    otherwise
      dec_value = uint16(0);
      fprintf('Unknown format number.\n');
  end
end
