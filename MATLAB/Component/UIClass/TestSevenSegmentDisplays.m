%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script: TestSevenSegmentDisplays
% Goal  : Run an instance of a group of a 7-segment displays component
% Copyright 2020 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Clean session
clear variables; close all force; clc;

% Constants
NB_DISPLAYS      = 3;
UINT8_MAX        = 255;
BACKGROUND_COLOR = [127 127 0]/UINT8_MAX; % RGB
SEGMENTS_COLOR   = [131 131 0]/UINT8_MAX; % RGB
SEGMENTS_VALUES  = [0b10000110; 0b01011011; 0b01001111]; % 1 2 3
FIGURE_NAME      = ['Group of ' num2str(NB_DISPLAYS) ' ''7-segment displays'''];

% UI container for the 7-segment displays
fig = uifigure('Name',FIGURE_NAME,'Position',[100 100 600 315],'Color',BACKGROUND_COLOR);
objGrid = uigridlayout(fig,[1 NB_DISPLAYS]);
objGrid.ColumnSpacing = 0;
objGrid.RowSpacing = 0;
objGrid.Padding = [0 0 0 0];

% Instanciate one layout of several 7-segment displays
objUI = SevenSegmentDisplays(NB_DISPLAYS,objGrid,SEGMENTS_COLOR,BACKGROUND_COLOR);

% Change segments color to black
objUI.SegmentsColor = [0 0 0];
% objUI.Endianness = 'Right';

% Write new values
for n=1:1:NB_DISPLAYS
  setSevenSegmentDisplay(objUI,SEGMENTS_VALUES(n,:),n);
end
