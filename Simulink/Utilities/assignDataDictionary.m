%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Script : assignDataDictionary
% Goal   : Assign the right data dictionary to all referenced models with
%          their own parameter values based on the selected mode to run.
%
% Copyright 2024 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Updating the set of parameters...');

% List of all referenced models to setup
modelsNames = {'ParkingMeterSystem', ...
               'ReadRegister','WriteRegister','WriteRegisterTriggered', ...
               'Buttons','InsertedCoins', ...
               'SegmentsDisplays','AvailableCoins','Flap','GeneratePulse', ...
               'Terminate', ...
               'ButtonsFcn','InsertedCoinsFcn', ...
               'SegmentsDisplaysFcn','AvailableCoinsFcn','FlapFcn', ...
               'GeneratePulseFcn','Scheduler','TerminateFcn'};
% Get the simulation or code generation mode
mode = get_param('ParkingMeterSystem/SimCodegen','CompiledActiveChoiceControl');
% Select the corresponding data dictionary
if strcmp(mode,'(sim)')
  dataDictionary = 'Parameters.sldd';
else
  dataDictionary = 'ParametersSystemCodegen.sldd';
end
% Assign the selected data dictionary to all referenced models
for k=1:1:numel(modelsNames)
  if (k > 1)
    load_system(modelsNames{k});
  end
  set_param(modelsNames{k},'DataDictionary',dataDictionary);
  if (k > 1)
    save_system(modelsNames{k});
    close_system(modelsNames{k});
  end
end
% Update the sampling time based on the selected simulation mode
if strcmp(mode,'(sim)')
  updateSamplingTime('ParkingMeterSystem','SAMPLING_TIME');
end
save_system(modelsNames{1});
disp('Update of the set of parameters done.');
disp('Loading all referenced models...');
