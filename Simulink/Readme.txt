- First, double click on "ParkingMeter.prj" in MATLAB to load the full project
- To open/run the model implementation in Simulink click on the "Main Model" project's shortcut in "1-MODELS", then press the "play" button for simulation
- To open/run the system implementation in System Composer click on the "Main System" project's shortcut in "2-COMPONENTS", then press the "play" button for simulation
- To generate, build and run C code, click on the "build" button in Simulink from the "Embeddeded Coder" App shortcut
- To run the standalone executables, click on their shortcuts "Debug" or "Release" in "6-STANDALONE"
- List of tools needed to run the demo: MATLAB, Simulink, Stateflow, System Composer, Communication System Toolbox, MATLAB Coder, Simulink Coder, Embedded Coder

Remarks:
- Completely clear the "Cache" folder contents when you change the simulation mode to "Rapid Accelerator Mode" or from "Rapid Accelerator Mode" to something else
  => This will avoid an error message while building the model
- When generating code out of the model for standalone deployment, set the simulation mode to something else than "Rapid Accelerator Mode", otherwise it will run too slowly
