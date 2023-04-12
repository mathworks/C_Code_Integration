classdef TextFont
    %TEXTFONT Button text font.
    %
    %   Copyright 2023 The MathWorks, Inc.

   enumeration
      normal ("normal")
      bold ("bold")
      bolder ("bolder")
      lighter ("lighter")
   end % enumeration

   properties (SetAccess = immutable)
       Name
   end % properties (SetAccess = immutable)

   methods
       function obj = TextFont(in)
           obj.Name = in;
       end % constructor
   end % methods
end % classdef