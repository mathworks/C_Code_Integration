classdef TestApp < matlab.uitest.TestCase
  % Call the test execution like this:
  % results = runtests('..\Component\UnitTesting\TestApp.m');
  
  properties
    App
    WaitTime = 3;
    Separator= ['------------------------------------------------------------'...
                '------------------------------------------------------------\n'];
  end

  methods (TestMethodSetup)
    function launchApp(testCase)
      % Instanciate the App Designer GUI
      testCase.App = ParkingMeterGUI;
      % Temporisation to be sure the App is up and running
      waitfor(testCase.App,'Running','on');
      pause(testCase.WaitTime);
      testCase.addTeardown(@delete,testCase.App);
    end
  end

  methods (Test)
    function testCase_1_StraightTicketPurchase(testCase)
      fprintf(testCase.Separator);
      fprintf('.Test case #1 => | ');
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      fprintf('PRESS GREEN BUTTON | ');
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);      
      % Insert a coin of 200 cents in the App
      fprintf('INSERT 200 CENTS | ');
      testCase.press(testCase.App.ImageCoin_200);
      pause(testCase.WaitTime);      
      % Take back the ticket from the App
      fprintf('GRAB PARKING TICKET | ');
      testCase.press(testCase.App.ImageTicket);
      pause(testCase.WaitTime);
      % Take back the change from the App
      fprintf('GRAB CHANGE      | ');
      testCase.press(testCase.App.ImageCoinSlot_1);
      pause(testCase.WaitTime);
      fprintf('END OF SEQUENCE    |\n');
      fprintf(testCase.Separator);
      % Kill the running timer of the App
      evalin('base','stop(timerfind); delete(timerfind);');
    end

    function testCase_2_CancelTicketPurchase(testCase)
      fprintf('Test case #2 => | ');
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      fprintf('PRESS GREEN BUTTON | ');
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);      
      % Insert a coin of 100 cents in the App
      fprintf('INSERT 100 CENTS | ');
      testCase.press(testCase.App.ImageCoin_100);
      pause(testCase.WaitTime);
      % Cancel the purchase process
      fprintf('PRESS RED BUTTON    | ');
      testCase.press(testCase.App.ButtonRed);
      pause(testCase.WaitTime);
      % Take back the return coins from the App
      fprintf('GRAB CHANGE      | ');
      testCase.press(testCase.App.ImageCoinSlot_1);
      pause(testCase.WaitTime);
      fprintf('END OF SEQUENCE    |\n');
      fprintf(testCase.Separator);
      % Kill the running timer of the App
      evalin('base','stop(timerfind); delete(timerfind);');
    end
    
    function testCase_3_BiggestChangeOnTicketPurchase(testCase)
      fprintf('Test case #3 => | ');
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      fprintf('PRESS GREEN BUTTON | ');
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);      
      % Insert a coin of 100 cents in the App
      fprintf('INSERT 100 CENTS | ');
      testCase.press(testCase.App.ImageCoin_100);
      pause(testCase.WaitTime);      
      % Insert a coin of 10 cents in the App
      fprintf('INSERT 10 CENTS     | ');
      testCase.press(testCase.App.ImageCoin_010);
      pause(testCase.WaitTime);      
      % Insert a coin of 200 cents in the App
      fprintf('INSERT 200 CENTS | ');
      testCase.press(testCase.App.ImageCoin_200);
      pause(testCase.WaitTime);      
      % Take back the ticket from the App
      fprintf('GRAB PARKING TICKET |\n');
      fprintf('                   ');
      testCase.press(testCase.App.ImageTicket);
      pause(testCase.WaitTime);
      % Take back the change from the App
      fprintf('GRAB CHANGE        | ');
      testCase.press(testCase.App.ImageCoinSlot_1);
      pause(testCase.WaitTime);
      fprintf('END OF SEQUENCE  |\n');
      fprintf(testCase.Separator);
      % Kill the running timer of the App
      evalin('base','stop(timerfind); delete(timerfind);');
%       testCase.verifyEqual(testCase.App.TabGroup.SelectedTab.Title,'Data')
    end
  end
end
