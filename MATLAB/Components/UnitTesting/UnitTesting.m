%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : Unit testing of the graphical App of the Parking Meter system.
%         Press the "Run" button to execute
% Copyright 2023 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear variables; close all; clc;
try
  stop(timerfind);
  delete(timerfind);
catch
  disp('No timers are running.');
end

%% Parking meter system initialization

global UNIT_TESTING; %#ok<GVMIS> 
% Set to true if the MATLAB unit testing API is used, otherwise always false
UNIT_TESTING = true;
% Close any potential running instance of the low-level application
system('start /b taskkill /F /im ParkingMeterProject.exe /im cmd.exe &');
pause(2);
% Call the low-level MATLAB code of the application in a separate process
fprintf('Starting the low-level application instance...\n');
system('start /b ..\\C_project\\ParkingMeterProject\\x64\\Release\\ParkingMeterProject.exe&');

%% Call the unit testing framework for automated testing

% Add the needed classes to run the test cases and generate reports
import matlab.unittest.TestRunner;
import matlab.unittest.Verbosity;
import matlab.unittest.plugins.CodeCoveragePlugin;
import matlab.unittest.plugins.TestReportPlugin;
import matlab.unittest.plugins.XMLPlugin;
import matlab.unittest.plugins.codecoverage.CoberturaFormat;
% Setup the test suite
suite = testsuite('..\Components\UnitTesting\TestApp.m');
% Build test runner and add needed reports plugins
runner = TestRunner.withTextOutput('OutputDetail', Verbosity.Detailed);
runner.addPlugin(TestReportPlugin.producingPDF('Report.pdf'));
runner.addPlugin(XMLPlugin.producingJUnitFormat('JunitTestResults.xml'));
runner.addPlugin(CodeCoveragePlugin.forFolder({'..\Components'},...
                 'Producing',CoberturaFormat('cobertura.xml')));
results = runner.run(suite);
% Close the running instance of the low-level application and the figures
system('taskkill /F /im ParkingMeterProject.exe /im cmd.exe &');
close all;
% Display end results
disp(results.table);
nfailed = nnz([results.Failed]);
assert(nfailed == 0, [num2str(nfailed) ' test(s) failed.']);
