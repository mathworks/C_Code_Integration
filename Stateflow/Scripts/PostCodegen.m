%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal : Copy the generated C and H files to an external Visual Studio project
%        and then build a x64 Debug and a Release version.
%
% Copyright 2019 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Constants definition
DESTINATION_PATH = '..\C_project\ParkingMeterProject';
BUILD_COMMAND = 'MSBuild ..\ParkingMeterProject.sln /p:Configuration=';
% Go to the codegen folder
cd('..\Codegen');
% Retrieve the lists of generated C and H files
src_files = dir('*.c');
hdr_files = dir('*.h');
% Copy the generated C and H files to the external location
for n=1:1:numel(src_files)
  copyfile(src_files(n).name,DESTINATION_PATH);
end
for n=1:1:numel(hdr_files)
  copyfile(hdr_files(n).name,DESTINATION_PATH);
end
% Copy the external C and H files to the external location
copyfile('..\Interface_C_files',DESTINATION_PATH);
% Copy the examples C and H files to the external location
copyfile('examples',DESTINATION_PATH);

% Go to the VS2019 project's folder
cd(DESTINATION_PATH);
% Build the VS2019 project
fprintf('Building the Debug executable...\n');
error_flag = system([BUILD_COMMAND 'Debug']);
fprintf('Building the Release executable...\n');
error_flag = error_flag + system([BUILD_COMMAND 'Release']);
% Check if the build succeeded
if (error_flag == 0)
  fprintf('Builds done.\n');
else
  fprintf('The builds failed.\n');
  fprintf('Add the path to the MSBuild.exe in the Windows System Path, such as:\n');
  fprintf('C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\n');
  fprintf('Once it has been done, restart your MATLAB session and it should work.\n');
end
