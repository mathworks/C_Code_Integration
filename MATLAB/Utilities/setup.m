function setup()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: setup()
% Goal    : Set-up the MATLAB path for the project. This function should be
%           called by an initialization script or shortcut.
%
% IN      : -
% IN/OUT  : -
% OUT     : -
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  disp('Begin the initialization of the project...');

  % Get the folders to add to the MATLAB path
  folders  = project_paths();
  root_dir = strsplit(pwd,'\\Utilities');

  % Add these folders to the MATLAB path
  for i=1:numel(folders)
    addpath(fullfile(root_dir{1},folders{i}));
  end

  % Go to the working directory
  cd(root_dir{1});
  disp('Initialization of the project done.');
end
