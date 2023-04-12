classdef IconAlign
    %ICONALIGN Button icon alignment.
    %
    %   Copyright 2023 The MathWorks, Inc.

    enumeration
        left ("left")
        leftmargin ("left-margin")
        right ("right")
        rightmargin ("right-margin")
        top ("top")
        bottom ("bottom")
    end % enumeration

    properties (SetAccess = immutable)
        Name
    end % properties (SetAccess = immutable)

    methods
        function obj = IconAlign(in)
            obj.Name = in;
        end % constructor
    end % methods
end % classdef