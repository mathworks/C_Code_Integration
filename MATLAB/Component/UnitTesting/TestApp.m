classdef TestApp < matlab.uitest.TestCase
  % Call the test execution like this:
  % results = runtests('..\Component\UnitTesting\TestApp.m');

  properties
    App
    WaitTime = 3;
  end

  methods (Access = private)
    function [] = outputsVerification(testCase,stimuli,responses,testID)
      % Add the needed classes to import diagnostics and figures in the report
      import matlab.unittest.diagnostics.Diagnostic;
      import matlab.unittest.diagnostics.FigureDiagnostic;
      import matlab.unittest.Verbosity;
      % Kill the running timer of the App
      evalin('base','stop(timerfind); delete(timerfind);');
      % Initialization
      yDataRef = str2double(responses(2:end,:));
      [nbSteps,nbParams] = size(testCase.App.AutoTestingTrace);
      xData = (1:1:nbSteps);
      yData = nan(nbSteps,nbParams);
      % Output sequence to expect for the correct behaviour
      for m=1:1:nbSteps-1
        for n=1:1:nbParams
          yData(m,n) = str2double(testCase.App.AutoTestingTrace{m+1,n});
        end
      end
      yDataRef(nbSteps,:) = [0;0];
      yData(nbSteps,:) = [0;0];
      xDataRef = (1:1:length(yDataRef))';
      % Replace potential NaNs in the results by zeros
      yDataRef(isnan(yDataRef)) = 0;
      yData(isnan(yData)) = 0;
      % Display results
      hFig = figure('units','normalized','outerposition',[0 0 0.75 0.75]);
      stairs(xDataRef,yDataRef(:,1),'LineStyle','-','LineWidth',2); hold('on');
      stairs(xDataRef,yDataRef(:,2),'LineStyle','-','LineWidth',2);
      stairs(xData,yData(:,1),'LineStyle','--','Marker','o','LineWidth',2);
      stairs(xData,yData(:,2),'LineStyle',':','Marker','d','LineWidth',2);
      hold('off');
      xticks((1:1:nbSteps));
      xticklabels(categorical(stimuli));
      xtickangle(45);
      xlabel('External events','FontSize',14,'FontWeight','Bold');
      ylabel('Amount of money','FontSize',14,'FontWeight','Bold');
      yticks((0:0.1:2));
      ytickformat('%.2f');
      ax = gca; ax.FontSize = 16; 
      title(['Results of test case #' num2str(testID)],'FontSize',18,'FontWeight','Bold');
      legend('Expected: Still to pay','Expected: Given back',...
             'Measured: Still to pay','Measured: Given back');
      % Verification of the produced output sequence against the reference
      testCase.verifyEqual(testCase.App.AutoTestingTrace,responses);
      % Save the figure in the results
      testCase.log(Verbosity.Terse,Diagnostic.join(FigureDiagnostic(hFig)));
    end
  end

  methods (TestMethodSetup)
    function [] = launchApp(testCase)
      % Instantiate the App Designer GUI
      testCase.App = ParkingMeterGUI;
      % Temporization to be sure the App is up and running
      waitfor(testCase.App,'Running','on');
      pause(testCase.WaitTime);
      testCase.addTeardown(@delete,testCase.App);
    end
  end

  methods (Test)
    function [] = testCase_1_StraightTicketPurchase(testCase)
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
      stimuliTrace = {'Start' 'Green Button' '200 Cents'...
                      'Get Ticket' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';...
                        ' ','0.50';' ','0.20';' ','0.10';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,1);
    end

    function [] = testCase_2_CancelTicketPurchase(testCase)
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
      stimuliTrace = {'Start' 'Green Button' '100 Cents'...
                      'Red Button' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';...
                        '0.20',' ';' ','1.00';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,2);
    end

    function [] = testCase_3_BiggestChangeOnTicketPurchase(testCase)
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
                      'Get Ticket' 'Wait' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'0.20',' ';...
                        '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
                        ' ','0.20';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,3);
    end

%     function [] = testCase_4_FullyEmptyAndReloadCashBox(testCase)
%       fprintf(' Processing the test case #4...\n');
%       pause(testCase.WaitTime);
%       for k=1:1:3
%         % Press the green button to start the purchase process
%         testCase.press(testCase.App.ButtonGreen);
%         pause(testCase.WaitTime);      
%         % Insert a coin of 100 cents in the App
%         testCase.press(testCase.App.ImageCoin_100);
%         pause(testCase.WaitTime);      
%         % Insert a coin of 10 cents in the App
%         testCase.press(testCase.App.ImageCoin_010);
%         pause(testCase.WaitTime);      
%         % Insert a coin of 200 cents in the App
%         testCase.press(testCase.App.ImageCoin_200);
%         pause(testCase.WaitTime);      
%         % Take back the ticket from the App
%         testCase.press(testCase.App.ImageTicket);
%         pause(testCase.WaitTime);
%         % Take back the change from the App
%         testCase.press(testCase.App.ImageCoinSlot_1);
%         pause(testCase.WaitTime);
%       end
%       % Press the key button to fully reload the cash box
%       testCase.press(testCase.App.ImageCashBoxKey);
%       pause(testCase.WaitTime);
%       % Press the green button to start the purchase process
%       testCase.press(testCase.App.ButtonGreen);
%       pause(testCase.WaitTime);      
%       % Insert a coin of 200 cents in the App
%       testCase.press(testCase.App.ImageCoin_200);
%       pause(testCase.WaitTime);      
%       % Take back the ticket from the App
%       testCase.press(testCase.App.ImageTicket);
%       pause(testCase.WaitTime);
%       % Take back the change from the App
%       testCase.press(testCase.App.ImageCoinSlot_1);
%       pause(testCase.WaitTime);
%       % Sequences to expect for the correct behaviour
%       stimuliTrace = {'Start' 'Green Button' '100 Cents' '10 Cents' '200 Cents'...
%                       'Get Ticket' 'Wait' 'Get Change' 'Wait' 'Green Button'...
%                       '100 Cents' '10 Cents' '200 Cents' 'Get Ticket' 'Wait'...
%                       'Get Change' 'Wait' 'Green Button' '100 Cents' '10 Cents'...
%                       '200 Cents' 'Get Ticket' 'Wait' 'Get Change' 'Reload Box'...
%                       'Green Button' '200 Cents' 'Get Ticket' 'Wait' 'Get Change' 'End'};
%       responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'0.20',' ';...
%                         '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
%                         ' ','0.20';'---',' ';'1.20',' ';'0.20',' ';...
%                         '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
%                         ' ','0.20';'---',' ';'1.20',' ';'0.20',' ';...
%                         '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
%                         '---',' ';' ',' ';'1.20',' ';' ','0.50';...
%                         ' ','0.20';' ','0.10';'---',' '};
%       testCase.outputsVerification(stimuliTrace,responsesTrace,4);
%     end
  end
end
