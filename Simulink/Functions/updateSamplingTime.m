function updateSamplingTime(model,parameter)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: updateSamplingTime()
% Goal    : Change the sampling time value if the rapid accelarator mode is/has
%           been selected. All other modes remain at the same sampling time of
%           1 ms.
% IN      : - model    : name of the Simulink model
%           - parameter: name of the parameter to modify
% IN/OUT  : -
% OUT     : -
%
% Author  : Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Set the Data Dictionary parameters
  sldd = get_param(model,'DataDictionary');
  section = 'Design Data';
  % Retrieve the current value of the sampling time in the Data Dictionary
  slddObj = Simulink.data.dictionary.open(sldd);
  sectionObj = getSection(slddObj,section);
  tsObj = getEntry(sectionObj,parameter);
  tsOld = getValue(tsObj);
  % Get the selected simulation mode
  simMode = get_param(model,'SimulationMode');
  % Set the new sampling time accordingly
  tsNew = 1e-3;
  if strcmp(simMode,'rapid-accelerator')
    tsNew = tsNew/57.35;
  end
  if (tsNew ~= tsOld)
    % Update the new sampling time value
    write2sldd(sldd,section,{parameter},tsNew);
    cacheFiles = [dir('*.slxc');dir('*.mexw64')];
    % Clear all cache and mex files to force rebuilding all models
    for n=1:length(cacheFiles)
      delete(cacheFiles(n).name);
    end
  end
  % Clean the workspace
  clear sldd section slddObj sectionObj tsObj tsOld tsNew;
end
