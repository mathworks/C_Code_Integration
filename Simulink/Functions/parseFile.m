function [] = parseFile(file_name)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function: parseFile()
% Goal    : Automatically modify the generated C file.
% IN      : - file_name: name of the C file to modify to support multiple instances
% IN/OUT  : -
% OUT     : -
%
% Author  : Sebastien Dupertuis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Custom code to add to support multiple execution instances
  CODE_TO_ADD = {'/* Function added to have the model running in normal mode */'
                 '#define MDL_SET_WORK_WIDTHS'
                 'static void mdlSetWorkWidths(SimStruct *S)'
                 '{'
                 '    ssSupportsMultipleExecInstances(S, true);'
                 '}'
                };
  NB_LINES_ADD = length(CODE_TO_ADD);
  
  % Open the text file and get its handler
  file_write_ID = fopen(file_name,'r+t');
  % Initialization
  start_count = false;
  counter = 0;
  offset = 0;
  saved_line = cell(NB_LINES_ADD,1);

  % Read all lines of the text file separately
  while(1)
    % Read the current line
    line_data = fgets(file_write_ID);
    % Leave the loop if the end of file has been reached
    if feof(file_write_ID)
      break;
    end
    % Count the number of lines to go over once the expression has been found
    if (start_count == true)
      counter = counter + 1;
    end
    if regexp(line_data,'static void mdlTerminate')
      % Found the line identifier after which the custom code will be added
      start_count = true;
    end
    
    if (counter == 2)
      for i=1:NB_LINES_ADD
        % Save the current text line
        saved_line{i,1} = fgets(file_write_ID);
        offset = offset + length(saved_line{i,1});
      end
      % Get current line position
      position = ftell(file_write_ID)-4;
      % Go to the identified expression line
      fseek(file_write_ID,position - offset,'bof');
      % Write the custom code at the right location
      for i=1:NB_LINES_ADD
        fprintf(file_write_ID,'%s',[CODE_TO_ADD{i,1} newline]);
      end
      % Rewrite the saved code at the right location
      for i=1:NB_LINES_ADD
        fprintf(file_write_ID,'%s',[saved_line{i,1}]);
      end
    end
  end

  % Close text files
  fclose(file_write_ID);
end
