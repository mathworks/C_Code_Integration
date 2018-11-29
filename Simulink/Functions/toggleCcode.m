function toggleCcode(model,parameter)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: toggleCcode()
% Goal    : Change the technique to import C code in the Simulink model.
%           Toggle between C caller block and S-Function techniques.
% IN      : - model    : name of the Simulink model
%           - parameter: name of the parameter to modify
% IN/OUT  : -
% OUT     : -
%
% Copyright 2018 The MathWorks, Inc.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Set the Data Dictionary parameters
  sldd = get_param(model,'DataDictionary');
  section = 'Design Data';
  % Retrieve the current value of the variant condition in the Data Dictionary
  sldd_obj = Simulink.data.dictionary.open(sldd);
  section_obj = getSection(sldd_obj,section);
  switch_obj = getEntry(section_obj,parameter);
  current_value = getValue(switch_obj);
  % Toggle the value of the switch
  write2sldd(sldd,section,{parameter},double(~current_value));
  % Update the model accordingly
  set_param(model,'SimulationCommand','Update');
  % Clean the workspace
  clear sldd section sldd_obj section_obj switch_obj current_value;
end
