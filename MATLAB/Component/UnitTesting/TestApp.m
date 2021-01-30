classdef TestApp < matlab.uitest.TestCase
  %TESTAPP Summary of this class goes here
  % Call the test execution like this:
  % results = runtests('..\Component\UnitTesting\TestApp.m');
  
  properties
    App
    WaitTime = 2;
  end

  methods (TestMethodSetup)
    function launchApp(testCase)
      global app;
      testCase.App = app;
      testCase.addTeardown(@delete,testCase.App);
    end
  end

  methods (Test)
    function testCase_1_StraightTicketPurchase(testCase)
      disp('Test case #1 starting...');
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      % Wait for the next event
      pause(testCase.WaitTime);      
      % Insert a coin of 200 cents in the App
      testCase.press(testCase.App.ImageCoin_200);
      % Wait for the next event
      pause(testCase.WaitTime);      
      % Take back the ticket from the App
      testCase.press(testCase.App.ImageTicket);
      % Wait for the next event
      pause(testCase.WaitTime);
      % Take back the change from the App
      testCase.press(testCase.App.ImageCoinSlot_1);
      % Wait for the next event
      pause(testCase.WaitTime);
      % Pause the App execution
      stop(timerfind);
    end

    function testCase_2_CancelTicketPurchase(testCase)
      % Resume the App execution
      start(timerfind);
      disp('Test case #2 starting...');
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      % Wait for the next event
      pause(testCase.WaitTime);      
      % Insert a coin of 100 cents in the App
      testCase.press(testCase.App.ImageCoin_100);
      % Wait for the next event
      pause(testCase.WaitTime);      
      % Cancel the purchase process
      testCase.press(testCase.App.ButtonRed);
      % Wait for the next event
      pause(testCase.WaitTime);
      % Take back the return coins from the App
      testCase.press(testCase.App.ImageCoinSlot_1);
      % Wait for the next event
      pause(testCase.WaitTime);
      % Switch off the App
      testCase.press(testCase.App.SwitchMaster);
      % Kill the running timer of the App
      stop(timerfind);
      delete(timerfind);
      % Verify Data Tab is selected
%       testCase.verifyEqual(testCase.App.TabGroup.SelectedTab.Title,'Data')
    end 
  end
end

