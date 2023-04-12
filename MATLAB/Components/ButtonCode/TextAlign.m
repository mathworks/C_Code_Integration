classdef TextAlign
    %TEXTALIGN Button text alignment.
    %
    %   Copyright 2023 The MathWorks, Inc.

    enumeration
        left ("left")
        center ("center")
        right ("right")
    end % enumeration

    properties (SetAccess = immutable)
        Name
    end % properties (SetAccess = immutable)

    methods
        function obj = TextAlign(in)
            obj.Name = in;
        end % constructor
    end % methods
end % classdef