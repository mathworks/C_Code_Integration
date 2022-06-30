classdef SevenSegmentDisplays
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Class SevenSegmentDisplays
% Goal  : This class contains all properties and methods needed to instanciate
%         and use a UI component implementing a group of 7-segment displays
%
% Author: Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Variables belonging to the object with direct external access
  properties (Access = public)
    Mask;
    Container;
    SegmentsColor(1,3) {mustBeNonnegative,mustBeNumeric} = [1 1 1];
    BackgroundColor(1,3) {mustBeNonnegative,mustBeNumeric} = [0 0 0];
    Endianness char {mustBeMember(Endianness,{'Left','Right'})} = 'Left';
  end

  % Methods of the class that can be accessed externally
  methods (Access = public)
    function obj = SevenSegmentDisplays(nbDisplays,parent,segsColor,backColor)
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function SevenSegmentDisplays()
    % Goal  : Construct a layout of several 7-segment displays instances of the
    %         SevenSegmentDisplay class
    % IN    : - nbDisplays: number of 7-segment displays in the group
    %         - parent    : parent container component from the App Designer
    %         - segsColor : color of the display' segments
    %         - backColor : color of the display's background
    %                       RGB color vector with values between 0 and 1
    % IN/OUT: -
    % OUT   : - obj : object of the class
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      % Load the labeled mask of the 7-segment display graphical component
      obj.Mask = load('SevenSegmentMask.mat');
      % Keep container properties in the SevenSegmentDisplays object
      obj.Container = parent;
      % Keep color properties in the SevenSegmentDisplays object
      obj.SegmentsColor = segsColor;
      obj.BackgroundColor = backColor;
      % Instanciate each UI axes to add them to the container (like a uigrid)
      for k=1:1:nbDisplays
        % Desired number of 7-segment displays are created to fullfil the space
        axHandler = uiaxes(obj.Container,'LooseInset',zeros(1,4),...
                           'xtick',[],'ytick',[],'Interactions',[]);
        axis(axHandler,'off');
        axHandler.Toolbar.Visible = 'off';
        axis(axHandler,'tight');
        % Enable all 7 segments plus the decimal point by default
        updateDigit(obj,(1:1:8),k);
      end
    end

    function setSevenSegmentDisplay(obj,binaryValue,digitID)
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function setSevenSegmentDisplay()
    % Goal  : Set function to change the state of one 7-segment display
    % IN    : - obj        : object of the class
    %         - binaryValue: uint8 value that represents segments to switch on
    %         - digitID    : ID of the 7-segment display to update
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      % Constants
      SEGMENTS_DIGIT_P = 0b10000000; % Decimal point segment encoding
      % Remove the decimal point bit to extract the digit only
      decimalPoint = bitand(binaryValue,SEGMENTS_DIGIT_P);
      binaryValue  = bitand(binaryValue,bitcmp(SEGMENTS_DIGIT_P));
      % New 7-segment encoded value to write
      switch (binaryValue)
        case 0b00111111 % uint8(0)
          segments = [1 2 3 4 5 6];
        case 0b00000110 % uint8(1)
          segments = [2 3];
        case 0b01011011 % uint8(2)
          segments = [1 2 4 5 7];
        case 0b01001111 % uint8(3)
          segments = [1 2 3 4 7];
        case 0b01100110 % uint8(4)
          segments = [2 3 6 7];
        case 0b01101101 % uint8(5)
          segments = [1 3 4 6 7];
        case 0b01111101 % uint8(6)
          segments = [1 3 4 5 6 7];
        case 0b00000111 % uint8(7)
          segments = [1 2 3];
        case 0b01111111 % uint8(8)
          segments = [1 2 3 4 5 6 7];
        case 0b01101111 % uint8(9)
          segments = [1 2 3 4 6 7];
        case 0b01000000 % uint8(-)
          segments = 7;
        otherwise
          % Incorrect 7 segments encoded value => do not update the segments
          segments = [];
      end
      % Add the decimal point to the digit if present
      if (decimalPoint ~= 0)
        segments = [segments 8];
      end
      if ~isempty(segments)
        updateDigit(obj,segments,digitID);
      end
    end
  end
  
  methods (Access = private)
    function updateDigit(obj,segments,digitID)
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Function updateDigit()
    % Goal  : Set function to change the state of one 7-segment display
    % IN    : - obj        : object of the class
    %         - segments   : list of segments indices to switch on
    %         - digitID    : ID of the 7-segment display to update
    % IN/OUT: -
    % OUT   : -
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      % Initialization
      nbDigits = length(obj.Container.Children);
      [nbRows,nbCols] = size(obj.Mask.labels);
      digit = permute(repmat(obj.BackgroundColor',[1 nbRows nbCols]),[2 3 1]);
      % Enable needed pixels
      for m=1:1:nbRows
        for n=1:1:nbCols
          if any(obj.Mask.labels(m,n) == segments)
            digit(m,n,:) = obj.SegmentsColor;
          end
        end
      end
      % Order of the displays, start from the left or the right
      if strcmp(obj.Endianness,'Right')
        image(digit,'parent',obj.Container.Children(nbDigits-digitID+1));
      else
        image(digit,'parent',obj.Container.Children(digitID));
      end
    end
  end
end
