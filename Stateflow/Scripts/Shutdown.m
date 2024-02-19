%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script: shutdown
% Goal  : Clean up the environment for the current project. This script undoes
%         the settings applied at the project's setup. It should be called by a
%         shutdown shortcut linked to its Project
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Project closing.');
% Move to the root folder of the project
cd('..')
clear variables; clc;
