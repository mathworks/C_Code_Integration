%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : Unit testing of the graphical App of the Parking Meter system.
%         Jenkins CI/CD server runs it automatically
% Author: Sebastien Dupertuis
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

%% Call the unit testing framework for automated testing

% Add the needed classes to run the test cases and generate reports
import matlab.unittest.TestRunner;
import matlab.unittest.Verbosity;
import matlab.unittest.plugins.CodeCoveragePlugin;
import matlab.unittest.plugins.TestReportPlugin;
import matlab.unittest.plugins.XMLPlugin;
import matlab.unittest.plugins.codecoverage.CoberturaFormat;
% Setup the test suite
suite = testsuite('..\Component\UnitTesting\TestApp.m');
% Build test runner and add needed reports plugins
runner = TestRunner.withTextOutput('OutputDetail', Verbosity.Detailed);
runner.addPlugin(TestReportPlugin.producingPDF('Report.pdf'));
runner.addPlugin(TestReportPlugin.producingHTML('Report.html'));
runner.addPlugin(XMLPlugin.producingJUnitFormat('JunitTestResults.xml'));
runner.addPlugin(CodeCoveragePlugin.forFolder({'..\Component'},...
                 'Producing',CoberturaFormat('cobertura.xml')));
results = runner.run(suite);
% Close the figures
close all;
% Display end results
disp(results.table);
nfailed = nnz([results.Failed]);
assert(nfailed == 0, [num2str(nfailed) ' test(s) failed.']);
