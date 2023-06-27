%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script : shutdown
% Goal   : Clean up the environment for the current project. This script
%          undoes the settings applied at the project's setup. It should
%          be called by a shutdown shortcut linked to its Simulink Project
%
% Copyright 2023 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Begin the termination of the project...');
% Close all opened models
bdclose('all');
% Use Simulink Project API to get the current project
project = simulinkproject;
% Move to the root folder of the project
try
  cd(project.RootFolder)
catch
  disp('Root folder has not been found.');
end
% Reset the location of the project
Simulink.fileGenControl('reset');
disp('Project closed.');
clear variables; clc;
