%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script  : shutdown
% Goal    : Clean up the environment for the current project. This script
%           undoes the settings applied at the project's setup. It should
%           be called by a shutdown shortcut linked to its Simulink Project
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Begin the termination of the project...');
% Use Simulink Project API to get the current project
p = slproject.getCurrentProject;
projectRoot = p.RootFolder;

% Reset the location of slprj.
Simulink.fileGenControl('reset');
cd ..
disp('Project closed.');
clear variables; clc;
