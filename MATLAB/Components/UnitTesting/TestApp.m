classdef TestApp < matlab.uitest.TestCase
  % Call the test execution for example like this:
  % results = runtests('..\Components\UnitTesting\TestApp.m');
  % Copyright 2023 The MathWorks, Inc.

  properties
    App
    WaitTime = 2;
    LineWidth = 2;
    FontSize = 16;
    FontWeight = 'Bold';
  end

  methods (Access = private)
    % Print the header at the beginning of the current test case
    function [] = header(testCase,testID,testText)
      fprintf(['--> Processing the test case #' num2str(testID)...
               ': ' testText '...\n']);
      pause(testCase.WaitTime);
    end

    % Print the footer at the end of the current test case
    function [] = footer(testCase) %#ok<MANU> 
      fprintf(['----------------------------------------' ...
               '----------------------------------------\n']);
    end

    % Grab the parking ticket if it is available after the purchase process has been done
    function [] = grabParkingTicket(testCase)
      try
        testCase.press(testCase.App.ImageTicket);
      catch
        disp('The ticket was not printed because the right amount of money was not paid');
      end
      pause(testCase.WaitTime);
    end

    % Grab the change if it is available after the purchase process has been done
    function [] = grabCoinsChange(testCase)
      try
        testCase.press(testCase.App.ImageCoinSlot_1);
      catch
        disp('No change to take back because the right amount of money was not paid');
      end
      pause(testCase.WaitTime);
    end

    % Comparaison and verification of the measured results with the baseline ones
    function [] = outputsVerification(testCase,stimuli,responses,testID,testText)
      % Add the needed classes to import diagnostics and figures in the report
      import matlab.unittest.diagnostics.Diagnostic;
      import matlab.unittest.diagnostics.FigureDiagnostic;
      import matlab.unittest.Verbosity;
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
      tiledlayout(2,1,'Padding','none','TileSpacing','compact');
      for k=1:1:2
        nexttile;
        stairs(xDataRef,yDataRef(:,k),...
               'LineStyle','-','LineWidth',testCase.LineWidth);
        hold('on');
        stairs(xData,yData(:,k),...
               'LineStyle','--','Marker','o','LineWidth',testCase.LineWidth);
        hold('off');
        grid('on');
        xlim([1 max([2 nbSteps])]);
        if (k == 1)
          title(['Results of test case #' num2str(testID) ': ' testText],...
               'FontSize',testCase.FontSize,'FontWeight',testCase.FontWeight);
          xticklabels([]);
          legend('Expected: Still to pay','Measured: Still to pay');
        else
          xticks((1:1:nbSteps));
          xticklabels(categorical(stimuli));
          xtickangle(45);
          xlabel('External events',...
                 'FontSize',testCase.FontSize,'FontWeight',testCase.FontWeight);
          legend('Expected: Given back','Measured: Given back');
        end
        ylabel('Amount of money',...
               'FontSize',testCase.FontSize,'FontWeight',testCase.FontWeight);
        yticks((0:0.1:2));
        ytickformat('%.2f');
        ylim([0 inf]);
        set(gca,'FontSize',testCase.FontSize);
      end
      % Verification of the produced output sequence against the reference
      testCase.verifyEqual(testCase.App.AutoTestingTrace,responses);
      % Save the figure in the results
      testCase.log(Verbosity.Terse,Diagnostic.join(FigureDiagnostic(hFig)));
    end
  end

  methods (TestMethodSetup)
    function [] = launchApp(testCase)
      % Instantiate the App Designer GUI
      testCase.App = ParkingMeterAutoTestGUI;
      % Temporization to be sure the App is up and running
      waitfor(testCase.App,'Running','on');
      pause(testCase.WaitTime);
      testCase.addTeardown(@delete,testCase.App);
    end
  end

  methods (Test)
    function [] = testCase_StraightTicketPurchase(testCase)
      testCaseID = 1;
      testCaseTitle = 'Straight Ticket Purchase';
      testCase.header(testCaseID,testCaseTitle);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);
      % Insert a coin of 200 cents in the App
      testCase.press(testCase.App.ImageCoin_200);
      pause(testCase.WaitTime);      
      % Take back the ticket and the change from the App
      testCase.grabParkingTicket();
      testCase.grabCoinsChange();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '200 Cents'...
                      'Get Ticket' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';...
                        ' ','0.50';' ','0.20';' ','0.10';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_BiggestChangeOnTicketPurchase(testCase)
      testCaseID = 2;
      testCaseTitle = 'Biggest Change On Ticket Purchase';
      testCase.header(testCaseID,testCaseTitle);
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
      % Take back the ticket and the change from the App
      testCase.grabParkingTicket();
      testCase.grabCoinsChange();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '100 Cents' '10 Cents' '200 Cents'...
                      'Get Ticket' 'Wait' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'0.20',' ';...
                        '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
                        ' ','0.20';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_CancelTicketPurchase(testCase)
      testCaseID = 3;
      testCaseTitle = 'Cancel Ticket Purchase';
      testCase.header(testCaseID,testCaseTitle);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);
      % Insert a coin of 100 cents in the App
      testCase.press(testCase.App.ImageCoin_100);
      pause(testCase.WaitTime);
      % Cancel the purchase process
      testCase.press(testCase.App.ButtonRed);
      pause(testCase.WaitTime);
      % Take back the change from the App
      testCase.grabCoinsChange();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '100 Cents'...
                      'Red Button' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';...
                        '0.20',' ';' ','1.00';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_050CentsIncrementalTicketPurchase(testCase)
      testCaseID = 4;
      testCaseTitle = '50 Cents Incremental Ticket Purchase';
      testCase.header(testCaseID,testCaseTitle);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);
      % Repeat the insertion of the same value coin
      for k=1:1:3
        % Insert a coin of 50 cents in the App
        testCase.press(testCase.App.ImageCoin_050);
        pause(testCase.WaitTime);
      end
      pause(testCase.WaitTime);      
      % Take back the ticket and the change from the App
      testCase.grabParkingTicket();
      testCase.grabCoinsChange();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '50 Cents' '50 Cents' '50 Cents'...
                      'Get Ticket' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'0.70',' ';...
                        '0.20',' ';' ','0.20';' ','0.10';'---',' ';};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_020CentsIncrementalTicketPurchase(testCase)
      testCaseID = 5;
      testCaseTitle = '20 Cents Incremental Ticket Purchase';
      testCase.header(testCaseID,testCaseTitle);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);
      % Repeat the insertion of the same value coin
      for k=1:1:6
        % Insert a coin of 20 cents in the App
        testCase.press(testCase.App.ImageCoin_020);
        pause(testCase.WaitTime);
      end
      pause(testCase.WaitTime);      
      % Take back the ticket from the App
      testCase.grabParkingTicket();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '20 Cents' '20 Cents' '20 Cents'...
                      '20 Cents' '20 Cents' '20 Cents' 'Get Ticket' 'Wait'...
                      'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'1.00',' ';...
                        '0.80',' ';'0.60',' ';'0.40',' ';'0.20',' ';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_010CentsIncrementalTicketPurchase(testCase)
      testCaseID = 6;
      testCaseTitle = '10 Cents Incremental Ticket Purchase';
      testCase.header(testCaseID,testCaseTitle);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);
      for k=1:1:12
        % Insert a coin of 10 cents in the App
        testCase.press(testCase.App.ImageCoin_010);
        pause(testCase.WaitTime);
      end
      % Take back the ticket from the App
      testCase.grabParkingTicket();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '10 Cents' '10 Cents' '10 Cents'...
                      '10 Cents' '10 Cents' '10 Cents' '10 Cents' '10 Cents'...
                      '10 Cents' '10 Cents' '10 Cents' '10 Cents'...
                      'Get Ticket' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'1.10',' ';...
                        '1.00',' ';'0.90',' ';'0.80',' ';'0.70',' ';'0.60',' ';...
                        '0.50',' ';'0.40',' ';'0.30',' ';'0.20',' ';'0.10',' ';...
                        '---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_FullyEmptyAndReloadCashBox(testCase)
      testCaseID = 7;
      testCaseTitle = 'Fully Empty And Reload CashBox';
      testCase.header(testCaseID,testCaseTitle);
      for k=1:1:3
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
        testCase.grabParkingTicket();
      end
      % Take back the change from the App
      testCase.grabCoinsChange();
      % Press the key button to fully reload the cash box
      testCase.press(testCase.App.ImageCashBoxKey);
      pause(testCase.WaitTime);
      % Press the green button to start the purchase process
      testCase.press(testCase.App.ButtonGreen);
      pause(testCase.WaitTime);
      % Insert a coin of 200 cents in the App
      testCase.press(testCase.App.ImageCoin_200);
      pause(testCase.WaitTime);
      % Take back the ticket and the change from the App
      testCase.grabParkingTicket();
      testCase.grabCoinsChange();
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'Green Button' '100 Cents' '10 Cents' '200 Cents'...
                      'Get Ticket' 'Wait' 'Get Change' 'Wait' 'Green Button'...
                      '100 Cents' '10 Cents' '200 Cents' 'Get Ticket' 'Wait'...
                      'Get Change' 'Wait' 'Green Button' '100 Cents' '10 Cents'...
                      '200 Cents' 'Get Ticket' 'Wait' 'Get Change' 'Reload Box'...
                      'Green Button' '200 Cents' 'Get Ticket' 'Wait' 'Get Change' 'End'};
      responsesTrace = {'DISP','COIN';'---',' ';'1.20',' ';'0.20',' ';...
                        '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
                        ' ','0.20';'---',' ';'1.20',' ';'0.20',' ';...
                        '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
                        ' ','0.20';'---',' ';'1.20',' ';'0.20',' ';...
                        '0.10',' ';' ','1.00';' ','0.50';' ','0.20';...
                        ' ','0.10';' ','0.10';'---',' ';' ',' ';'1.20',' ';...
                        ' ','0.50';' ','0.20';' ','0.10';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end

    function [] = testCase_SwitchOffTheLowLevelApplication(testCase)
      testCaseID = 8;
      testCaseTitle = 'Switch Off The Low Level Application';
      testCase.header(testCaseID,testCaseTitle);
      pause(testCase.WaitTime);
      % Press the switch button to switch the low-level Application off
      testCase.press(testCase.App.SwitchMaster);
      pause(testCase.WaitTime);
      % Sequences to expect for the correct behaviour
      stimuliTrace = {'Start' 'End'};
      responsesTrace = {'DISP','COIN';'---',' '};
      testCase.outputsVerification(stimuliTrace,responsesTrace,...
	                               testCaseID,testCaseTitle);
      % Close the App
      testCase.App.CloseRequest();
      testCase.footer();
    end
  end
end
