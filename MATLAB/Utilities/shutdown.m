function shutdown()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: shutdown()
% Goal    : Clean up the MATLAB path. This script undoes the settings applied at
%           the project's setup. It should be called by a shutdown script or
%           shortcut.
%
% IN      : -
% IN/OUT  : -
% OUT     : -
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  disp('Begin the termination of the project...');

  % Get the folders to add to the MATLAB path
  folders  = project_paths();
  root_dir = strsplit(pwd,'\\Utilities');

  % Remove these folders from the MATLAB path
  for i=1:numel(folders)
    rmpath(fullfile(root_dir{1},folders{i}));
  end

  % Clear the base workspace and the command line interface
  clear variable; clc;
  disp('Project closed.');
end
