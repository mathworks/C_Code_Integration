function folders = project_paths()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: project_paths()
% Goal    : Defines the folders that will be added to the MATLAB path when
%           the project is opened, and removed from the MATLAB path when it
%           is closed. Edit the definition of folders below to add them to
%           the path for the current project.
%
% IN      : -
% IN/OUT  : -
% OUT     : - folders : List of the needed folders to add to the path
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  folders = {'.',...
             'Classes',...
             'Functions',...
             'MEX_functions',...
             'Utilities'};
end
