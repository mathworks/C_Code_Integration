%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script: ImportMaskImage
% Goal  : Take a 7-segment display image as a reference to create a labeled mask
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear variables; clc
% Convert the mask image into Black and White representation
BW = logical(rgb2gray(imread('SevenSegmentDisplay.png')));
% Identify all areas from the mask
[~,labels] = bwboundaries(BW,'noholes');
% Assign right labels values to the area to match the 7 segment display layout
labels(labels == 1) = -6;
labels(labels == 2) = -5;
labels(labels == 3) = -7;
labels(labels == 4) = -1;
labels(labels == 5) = -4;
labels(labels == 6) = -2;
labels(labels == 7) = -3;
labels(labels == 8) = -8;
labels = -labels;
% Save labelled mask
save('..\Components\UIClass\SevenSegmentMask.mat','labels');
