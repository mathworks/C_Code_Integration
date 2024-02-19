%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: setup()
% Goal    : Set-up the environment for this Simulink Project. This function
%           should be called by a startup shortcut linked to its Simulink
%           Project.
% IN      : -
% IN/OUT  : -
% OUT     : -
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function setup()
  disp('Begin the initialization of the project...');
  % Use Simulink Project API to get the current project
  project = simulinkproject;
  % Define the default folders for the generated artifacts
  prefs.myCacheFolder = fullfile(project.RootFolder, 'Cache');
  prefs.myCodeFolder  = fullfile(project.RootFolder, 'Code');
  prefs.myWorkFolder  = fullfile(project.RootFolder, 'Work');
  Simulink.fileGenControl('set',...
                          'CacheFolder', prefs.myCacheFolder,...
                          'CodeGenFolder', prefs.myCodeFolder,...
                          'createDir', true);
  % Go to the working directory
  cd(prefs.myWorkFolder);
  disp('Initialization of the project done.');
end
