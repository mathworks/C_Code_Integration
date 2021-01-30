classdef TestApp < matlab.uitest.TestCase
  %TESTAPP Summary of this class goes here
  % Call the test execution like this:
  % results = runtests('..\Component\UnitTesting\TestApp.m');
  
  properties
    App
  end

  methods (TestMethodSetup)
    function launchApp(testCase)
      global app;
      testCase.App = app;
      testCase.addTeardown(@delete,testCase.App);
    end
  end

  methods (Test)
    function testTicketPurchase(testCase)
      disp('Starting the testing sequence...');
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      % Wait for the next event
      pause(2);      
      % Insert a coin of 100 cents in the App
      testCase.press(testCase.App.ImageCoin_100);
      % Wait for the next event
      pause(2);      
      % Insert a coin of 20 cents in the App
      testCase.press(testCase.App.ImageCoin_020);
      % Wait for the next event
      pause(2);      
      % Take back the ticket from the App
      testCase.press(testCase.App.ImageTicket);
      % Wait for the next event
      pause(2);
      % Take back the change from the App
%       for k=1:1:9
%         currentCoinSlot = ['ImageCoinSlot_' num2str(k)];
%         testCase.press(testCase.App.(currentCoinSlot));
%       end
      % Verify Data Tab is selected
%       testCase.verifyEqual(testCase.App.TabGroup.SelectedTab.Title,'Data')
    end
  end
end

