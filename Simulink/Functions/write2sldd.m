function write2sldd(file_name,data_section,var_names,var_values)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: write2sldd()
% Goal    : Update data entries of the SLDD file linked to the SLX model.
%
% IN      : - file_name   : name of the Simulink Data Dictionary file
%           - data_section: name of the data section to modify in the sldd
%           - var_names   : list of variables to write
%           - var_values  : list of corresponding values to write 
% IN/OUT  : -
% OUT     : - error_flag  : 0 = no error, 1 = odd number of input arguments
%
% Author  : Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Initialization
  nb_variable_params = length(var_names);
  nb_variable_values = length(var_values);

  % Check if there is an even number of input arguments
  if (nb_variable_params ~= nb_variable_values)
    % Raised an error if there is a different number of input arguments
    disp(['Different number of parameters and values provided.'...
          'SLDD file not modified.']);
  else
    % Use SLDD API to work with the SLDD file to modify
    sldd    = Simulink.data.dictionary.open(file_name);
    section = getSection(sldd,data_section);
    
    % Update SLDD entries
    for i=1:1:nb_variable_params
      try 
        % Get existing SLDD entry
        sldd_entry = getEntry(section,var_names{i});
        % Write a new value to the already existing SLDD entry
        setValue(sldd_entry,var_values(i));
      catch
        % Write a new SLDD entry with its value
        addEntry(section,var_names{1,i},var_values(i));
      end
    end
    % Write of the updated data to the SLDD
    saveChanges(sldd);
    % Clean the workspace
    clear variables;
  end
end
