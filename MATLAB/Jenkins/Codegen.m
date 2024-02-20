%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Goal  : Create the MATLAB Coder object with all needed settings and generate C
%         code. Then, it builds the source files using the Visual Studio Project
%         and starts the standalone executable and the Parking Meter GUI.
% Script partially generated from project 'ParkingMeterLowLevel_C_source.prj'
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear variables; clc;

% Initialization
global TEST_MODE; %#ok<NUSED,GVMIS> 
defineTestMode(0); % '0' => normal mode, '1' => test mode

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('lib','ecoder',true);
cfg.IncludeTerminateFcn = true;
cfg.GenerateCodeMetricsReport = true;
cfg.EnableStrengthReduction = true;
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;
cfg.SaturateOnIntegerOverflow = false;
cfg.CustomInclude = sprintf('..\\Interface_C_files\n');
cfg.CustomSource = sprintf(['..\\Interface_C_files\\read_register.c\n'...
                            '..\\Interface_C_files\\write_register.c\n'...
                            '..\\Interface_C_files\\ParkingMeterMemory.h']);
cfg.FilePartitionMethod = 'SingleFile';
cfg.InitFltsAndDblsToZero = false;
cfg.PreserveVariableNames = 'All';
cfg.RowMajor = true;
cfg.EnableOpenMP = false;
cfg.GenCodeOnly = true;
cfg.PostCodeGenCommand = 'PostCodegen';
cfg.BuildConfiguration = 'Faster Runs';
cfg.CodeReplacementLibrary = 'Intel SSE (Windows)';
cfg.SupportNonFinite = false;
cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Windows64)';
cfg.HardwareImplementation.TargetHWDeviceType = 'Intel->x86-64 (Windows64)';

%% Invoke MATLAB Coder
fprintf('Starting the C code generation and building process...\n');
codegen('-config','cfg','parkingMeterLowLevel','-nargout','0','-d','..\Codegen'); 
