classdef TestApp < matlab.uitest.TestCase
  % Call the test execution like this:
  % results = runtests('..\Component\UnitTesting\TestApp.m');

  properties
    App
    WaitTime = 3;
  end

  methods (Access = private)
    function outputsVerification(testCase,stimuli,responses,testID)
      % Kill the running timer of the App
      evalin('base','stop(timerfind); delete(timerfind);');
      % Initialization
      [nbSteps,nbParams] = size(responses);
      xData = (1:1:nbSteps);
      yData = nan(nbSteps,nbParams);
      % Output sequence to expect for the correct behaviour
      for m=1:1:nbSteps-1
        for n=1:1:nbParams
          yData(m,n) = str2double(testCase.App.AutoTestingTrace{m+1,n});
        end
      end
      yData(isnan(yData)) = 0;
      % Display results
      figure(testID);
      stairs(xData,yData(:,1),'LineStyle','--','Marker','o','LineWidth',1.5);
      hold('on');
      stairs(xData,yData(:,2),'LineStyle',':','Marker','d','LineWidth',1.5);
      xticks((1:1:nbSteps));
      xticklabels(categorical(stimuli));
      xlabel('External events');
      ylabel('Amount of money');
      yticks((0:0.1:2));
      ytickformat('%.2f');
      title(['Results of test case #' num2str(testID)]);
      legend('Still to pay','Given back');
      % Verification of the produced output sequence against the reference
      testCase.verifyEqual(testCase.App.AutoTestingTrace,responses)
    end
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
      fprintf('. Processing the test case #1...\n');
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);      
      % Insert a coin of 200 cents in the App
      testCase.press(testCase.App.ImageCoin_200);
      pause(testCase.WaitTime);      
      % Take back the ticket from the App
      testCase.press(testCase.App.ImageTicket);
      pause(testCase.WaitTime);
      % Take back the change from the App
      testCase.press(testCase.App.ImageCoinSlot_1);
      pause(testCase.WaitTime);
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '200 Cents' 'Wait' 'Grab Ticket'...
                      'Grab Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';...
                        ' ','0.50';' ','0.20';' ','0.10';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,1);
    end

    function testCase_2_CancelTicketPurchase(testCase)
      fprintf(' Processing the test case #2...\n');
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);      
      % Insert a coin of 100 cents in the App
      testCase.press(testCase.App.ImageCoin_100);
      pause(testCase.WaitTime);
      % Cancel the purchase process
      testCase.press(testCase.App.ButtonRed);
      pause(testCase.WaitTime);
      % Take back the return coins from the App
      testCase.press(testCase.App.ImageCoinSlot_1);
      pause(testCase.WaitTime);
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '100 Cents' 'Red Button'...
                      'Grab Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';...
                        '0.20',' ';' ','1.00';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,2);
    end

    function testCase_3_BiggestChangeOnTicketPurchase(testCase)
      fprintf(' Processing the test case #3...\n');
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);      
      % Insert a coin of 100 cents in the App
      testCase.press(testCase.App.ImageCoin_100);
      pause(testCase.WaitTime);      
      % Insert a coin of 10 cents in the App
      testCase.press(testCase.App.ImageCoin_010);
      pause(testCase.WaitTime);      
      % Insert a coin of 200 cents in the App
      testCase.press(testCase.App.ImageCoin_200);
      pause(testCase.WaitTime);      
      % Take back the ticket from the App
      testCase.press(testCase.App.ImageTicket);
      pause(testCase.WaitTime);
      % Take back the change from the App
      testCase.press(testCase.App.ImageCoinSlot_1);
      pause(testCase.WaitTime);
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '100 Cents' '10 Cents' '200 Cents'...
                      'Wait' 'Grab Ticket' 'Wait' 'Grab Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'0.20',' ';...
                        '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
                        ' ','0.20';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,3);
    end
  end
end
