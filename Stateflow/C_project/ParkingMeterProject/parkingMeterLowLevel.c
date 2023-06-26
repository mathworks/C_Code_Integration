/*
 * File: parkingMeterLowLevel.c
 *
 * MATLAB Coder version            : 5.6
 * C/C++ source code generated on  : 26-Jun-2023 17:34:49
 */

/* Include Files */
#include "parkingMeterLowLevel.h"
#include "ParkingMeterMemory.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  bool EnableAnimation;
  bool ExecuteInitStep;
  bool WarningOnUninitializedData;
  double AnimationDelay;
  double EventQueueSize;
  bool MATLABTimer;
  double ClockSpeedFactor;
} struct_T;
#endif /* typedef_struct_T */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  bool IsActiveVar_Scheduler;
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef typedef_c_struct_T
#define typedef_c_struct_T
typedef struct {
  double ActiveChildVar_Scheduler;
  double ActiveChildVar_PURCHASE_TICKET;
} c_struct_T;
#endif /* typedef_c_struct_T */

#ifndef typedef_StateMachineParameters
#define typedef_StateMachineParameters
typedef struct {
  double sampling_time;
  double refreshing_time;
  bool master_switch;
  bool green_pressed;
  bool red_pressed;
  unsigned char coins_reg_value;
  unsigned short temp_amount;
  unsigned short inserted_amount;
  unsigned short amount_to_return;
  bool flap_open;
  unsigned char register_value;
  unsigned short display_value;
  bool ISR[7];
} StateMachineParameters;
#endif /* typedef_StateMachineParameters */

#ifndef typedef_d_struct_T
#define typedef_d_struct_T
typedef struct {
  double Scheduler;
  double c_Scheduler_PURCHASE_TICKET_UPD;
} d_struct_T;
#endif /* typedef_d_struct_T */

#ifndef typedef_e_struct_T
#define typedef_e_struct_T
typedef struct {
  double CurrentTime;
  bool IsExecuting;
  struct_T ConfigurationOptions;
  b_struct_T IsActiveVars;
  c_struct_T ActiveChildVars;
  d_struct_T StepCounters;
} e_struct_T;
#endif /* typedef_e_struct_T */

#ifndef typedef_Scheduler
#define typedef_Scheduler
typedef struct {
  double REFRESHING_TICK;
  StateMachineParameters obj;
  e_struct_T StateflowInternalData;
} Scheduler;
#endif /* typedef_Scheduler */

/* Variable Definitions */
int TEST_MODE;

static bool isInitialized_parkingMeterLowLevel = false;

/* Function Declarations */
static void Scheduler_step(Scheduler *this);

static void TestMode_give_back_coin(void);

static void TestMode_write_register(void);

static void b_display_digit(unsigned char display_ID, int digit_value,
                            double dot_segment);

static void c_Scheduler_Scheduler_ExitInter(Scheduler *this);

static void display_digit(unsigned char display_ID, unsigned short digit_value,
                          double dot_segment);

static int div_nde_s32_floor(int numerator);

static void give_back_coin(unsigned short amount);

static unsigned short return_coin_value(unsigned short amount_to_return,
                                        unsigned short coin_value);

static double rt_roundd(double u);

static void standard_operation_mode(void);

/* Function Definitions */
/*
 * Arguments    : Scheduler *this
 * Return Type  : void
 */
static void Scheduler_step(Scheduler *this)
{
  if (!this->StateflowInternalData.IsExecuting) {
    this->StateflowInternalData.IsExecuting = true;
    if (!this->StateflowInternalData.IsActiveVars.IsActiveVar_Scheduler) {
      this->StateflowInternalData.IsActiveVars.IsActiveVar_Scheduler = true;
      /* SFXSourceLine:<Scheduler/Scheduler/Transition#52> REFRESHING_TICK =
       * obj.refreshing_time/obj.sampling_time; */
      this->REFRESHING_TICK =
          this->obj.refreshing_time / this->obj.sampling_time;
      /* State Scheduler.INITIALIZATION becomes active */
      this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
          3.0;
      /*  Reset of the parking meter status */
      /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.display_value =
       * uint16(double(SEGMENTS_DIGIT_M)); */
      this->obj.display_value = 45U;
      /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.flap_open =
       * false; */
      this->obj.flap_open = false;
      /*  Initial state of the 7 segments displays */
      /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.ISR(1) = true;
       */
      this->obj.ISR[0] = true;
      /*  Close the coin's flap */
      /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.ISR(2) = true;
       */
      this->obj.ISR[1] = true;
    } else {
      switch ((int)this->StateflowInternalData.ActiveChildVars
                  .ActiveChildVar_Scheduler) {
      case 1:
        /* State: CHECK_COINS */
        /* State Scheduler.CHECK_COINS becomes inactive */
        /* State Scheduler.PURCHASE_TICKET becomes active */
        this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
            13.0;
        /*  Waiting for the full paiment or the cancellation of the ticket */
        /* State Scheduler.PURCHASE_TICKET.INITIALIZATION becomes active */
        this->StateflowInternalData.ActiveChildVars
            .ActiveChildVar_PURCHASE_TICKET = 46.0;
        /*  Reset needed variables */
        /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/INITIALIZATION>
         * obj.inserted_amount = uint16(0); */
        this->obj.inserted_amount = 0U;
        break;
      case 3:
        /* State: INITIALIZATION */
        /* State Scheduler.INITIALIZATION becomes inactive */
        /* State Scheduler.PURCHASE_CHECK becomes active */
        this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
            2.0;
        break;
      case 2:
        /* State: PURCHASE_CHECK */
        if (!this->obj.master_switch) {
          /* %SFXSourceLine:<Scheduler/Scheduler/Transition#56>
           * obj.master_switch == false */
          /* State Scheduler.PURCHASE_CHECK becomes inactive */
          /* State Scheduler.STOP_EXECUTION becomes active */
          this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
              4.0;
          /*  Stop the model execution */
          /*  Trigger the terminate function to stop the execution */
          /* SFXSourceLine:<Scheduler/Scheduler/STOP_EXECUTION> obj.ISR(7) =
           * true;  */
          this->obj.ISR[6] = true;
        } else if (this->obj.green_pressed) {
          /* %SFXSourceLine:<Scheduler/Scheduler/Transition#58>
           * obj.green_pressed == true */
          /* State Scheduler.PURCHASE_CHECK becomes inactive */
          /* State Scheduler.CHECK_COINS becomes active */
          this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
              1.0;
          /*  Update of the button value state once it has been pressed */
          /* SFXSourceLine:<Scheduler/Scheduler/CHECK_COINS> obj.display_value =
           * TICKET_FEE; */
          this->obj.display_value = 120U;
          /* SFXSourceLine:<Scheduler/Scheduler/CHECK_COINS> obj.flap_open =
           * true; */
          this->obj.flap_open = true;
          /*  Send interrupts */
          /*  Display the cost of a parking ticket */
          /* SFXSourceLine:<Scheduler/Scheduler/CHECK_COINS> obj.ISR(1) = true;
           */
          this->obj.ISR[0] = true;
          /*  Open the coin's flap */
          /* SFXSourceLine:<Scheduler/Scheduler/CHECK_COINS> obj.ISR(2) = true;
           */
          this->obj.ISR[1] = true;
        } else {
          /*  Waiting on a ticket purchase request */
          /*  Leds: check if the parking meter can give money back */
          /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_CHECK> obj.ISR(3) =
           * true;  */
          this->obj.ISR[2] = true;
          /*  Check the status of the green button and master switch */
          /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_CHECK> obj.ISR(5) =
           * true;  */
          this->obj.ISR[4] = true;
        }
        break;
      case 13:
        /* State: PURCHASE_TICKET */
        switch ((int)this->StateflowInternalData.ActiveChildVars
                    .ActiveChildVar_PURCHASE_TICKET) {
        case 35:
          /* State: CANCEL_CHECK */
          if (this->obj.red_pressed) {
            /* %SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/Transition#37>
             * obj.red_pressed == true */
            /* State Scheduler.PURCHASE_TICKET.CANCEL_CHECK becomes inactive */
            /* State Scheduler.PURCHASE_TICKET.CANCEL_PURCHASE becomes active */
            this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET = 21.0;
            /*  Ticket's purchase process cancelled */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/CANCEL_PURCHASE>
             * obj.amount_to_return = obj.inserted_amount; */
            this->obj.amount_to_return = this->obj.inserted_amount;
            /*  End of the purchase process */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/CANCEL_PURCHASE>
             * obj.ISR(4) = true;  */
            this->obj.ISR[3] = true;
          } else {
            /* State Scheduler.PURCHASE_TICKET.CANCEL_CHECK becomes inactive */
            /* State Scheduler.PURCHASE_TICKET.COIN_CHECK becomes active */
            this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET = 40.0;
            /*  Update the amount to pay if a coin has been inserted */
            /*  Check current inserted coin */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/COIN_CHECK>
             * obj.ISR(6) = true;  */
            this->obj.ISR[5] = true;
          }
          break;
        case 21:
          /* State: CANCEL_PURCHASE */
          c_Scheduler_Scheduler_ExitInter(this);
          /* State Scheduler.INITIALIZATION becomes active */
          this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
              3.0;
          /*  Reset of the parking meter status */
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION>
           * obj.display_value = uint16(double(SEGMENTS_DIGIT_M)); */
          this->obj.display_value = 45U;
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.flap_open =
           * false; */
          this->obj.flap_open = false;
          /*  Initial state of the 7 segments displays */
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.ISR(1) =
           * true;  */
          this->obj.ISR[0] = true;
          /*  Close the coin's flap */
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.ISR(2) =
           * true;  */
          this->obj.ISR[1] = true;
          break;
        case 40:
          /* State: COIN_CHECK */
          if (this->obj.coins_reg_value != this->obj.register_value) {
            /* %SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/Transition#42>
             * obj.coins_reg_value ~= obj.register_value */
            /* State Scheduler.PURCHASE_TICKET.COIN_CHECK becomes inactive */
            this->StateflowInternalData.StepCounters
                .c_Scheduler_PURCHASE_TICKET_UPD = 0.0;
            /* State Scheduler.PURCHASE_TICKET.UPDATE_AMOUNT becomes active */
            this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET = 22.0;
          } else {
            /* State Scheduler.PURCHASE_TICKET.COIN_CHECK becomes inactive */
            /* State Scheduler.PURCHASE_TICKET.CANCEL_CHECK becomes active */
            this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET = 35.0;
            /*  Check if the purchase is being cancelled */
            /*  Check status of the red button */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/CANCEL_CHECK>
             * obj.ISR(5) = true;  */
            this->obj.ISR[4] = true;
          }
          break;
        case 46:
          /* State: INITIALIZATION */
          /* State Scheduler.PURCHASE_TICKET.INITIALIZATION becomes inactive */
          /* State Scheduler.PURCHASE_TICKET.CANCEL_CHECK becomes active */
          this->StateflowInternalData.ActiveChildVars
              .ActiveChildVar_PURCHASE_TICKET = 35.0;
          /*  Check if the purchase is being cancelled */
          /*  Check status of the red button */
          /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/CANCEL_CHECK>
           * obj.ISR(5) = true;  */
          this->obj.ISR[4] = true;
          break;
        case 33:
          /* State: PRINT_RECEIPT */
          c_Scheduler_Scheduler_ExitInter(this);
          /* State Scheduler.INITIALIZATION becomes active */
          this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler =
              3.0;
          /*  Reset of the parking meter status */
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION>
           * obj.display_value = uint16(double(SEGMENTS_DIGIT_M)); */
          this->obj.display_value = 45U;
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.flap_open =
           * false; */
          this->obj.flap_open = false;
          /*  Initial state of the 7 segments displays */
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.ISR(1) =
           * true;  */
          this->obj.ISR[0] = true;
          /*  Close the coin's flap */
          /* SFXSourceLine:<Scheduler/Scheduler/INITIALIZATION> obj.ISR(2) =
           * true;  */
          this->obj.ISR[1] = true;
          break;
        case 22:
          /* State: UPDATE_AMOUNT */
          this->StateflowInternalData.StepCounters
              .c_Scheduler_PURCHASE_TICKET_UPD++;
          if (this->StateflowInternalData.StepCounters
                  .c_Scheduler_PURCHASE_TICKET_UPD >= this->REFRESHING_TICK) {
            /* %SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/Transition#39>
             * after(REFRESHING_TICK, tick) */
            /* State Scheduler.PURCHASE_TICKET.UPDATE_AMOUNT becomes inactive */
            /* State Scheduler.PURCHASE_TICKET.CANCEL_CHECK becomes active */
            this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET = 35.0;
            /*  Check if the purchase is being cancelled */
            /*  Check status of the red button */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/CANCEL_CHECK>
             * obj.ISR(5) = true;  */
            this->obj.ISR[4] = true;
          } else if (this->obj.inserted_amount >= 120) {
            /* %SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/Transition#44>
             * obj.inserted_amount >= TICKET_FEE */
            /* State Scheduler.PURCHASE_TICKET.UPDATE_AMOUNT becomes inactive */
            /* State Scheduler.PURCHASE_TICKET.PRINT_RECEIPT becomes active */
            this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET = 33.0;
            /*  Printing of the parking ticket and give back coin's change */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/PRINT_RECEIPT>
             * obj.return_value = INT_MASK_PRINT_TICKET; */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/PRINT_RECEIPT>
             * obj.amount_to_return = obj.inserted_amount-TICKET_FEE; */
            this->obj.amount_to_return =
                (unsigned short)(this->obj.inserted_amount - 120);
            /*  End of the purchase process */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/PRINT_RECEIPT>
             * obj.ISR(4) = true;  */
            this->obj.ISR[3] = true;
          } else {
            /*  Update the amount to pay if a coin has been inserted */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/UPDATE_AMOUNT>
             * obj.coins_reg_value = obj.register_value; */
            this->obj.coins_reg_value = this->obj.register_value;
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/UPDATE_AMOUNT>
             * obj.display_value = TICKET_FEE-obj.inserted_amount; */
            this->obj.display_value =
                (unsigned short)(120 - this->obj.inserted_amount);
            /*  Update the remaining cents amount to pay */
            /* SFXSourceLine:<Scheduler/Scheduler/PURCHASE_TICKET/UPDATE_AMOUNT>
             * obj.ISR(1) = true;  */
            this->obj.ISR[0] = true;
          }
          break;
        }
        break;
      case 4:
        /* State: STOP_EXECUTION */
        break;
      }
    }
    this->StateflowInternalData.StepCounters.Scheduler++;
    this->StateflowInternalData.IsExecuting = false;
  }
}

/*
 * Text constants declaration
 *
 * Arguments    : void
 * Return Type  : void
 */
static void TestMode_give_back_coin(void)
{
  int coin_choice;
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function give_back_coin() */
  /*  Goal  : Test if coins are given back correctly or not */
  /*  IN    : - const_obj: object containing all needed constants */
  /*          - f_api    : functions handler struct listing functions to access
   */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Variables declaration  */
  coin_choice = 1;
  /*  Split sections  */
  printf("%s\n", "-------------------------------------------------------------"
                 "------------------");
  fflush(stdout);
  /*  Loop over the menu entries */
  int exitg1;
  do {
    exitg1 = 0;
    if (coin_choice != 0) {
      /*  Menu selection  */
      printf("Test menu to give back coins:\n");
      fflush(stdout);
      printf(">> 0 - Leave\n");
      fflush(stdout);
      printf(">> 1 - Give back a  10 cents coin\n");
      fflush(stdout);
      printf(">> 2 - Give back a  20 cents coin\n");
      fflush(stdout);
      printf(">> 3 - Give back a  50 cents coin\n");
      fflush(stdout);
      printf(">> 4 - Give back a 100 cents coin\n");
      fflush(stdout);
      printf("\n");
      fflush(stdout);
      /*  Get and check the menu entry provided at the console interface  */
      /*  Function that is not translated into C code */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       */
      /*  Function check_get_data() */
      /*  Goal  : Test the write access function to any shared memory register
       */
      /*  IN    : - promp_text: pointer to a chain char to display in the
       * console */
      /*          - min_data  : minimum value that is allowed in the range of
       * data */
      /*          - max_data  : maximum value that is allowed in the range of
       * data */
      /*  IN/OUT: - */
      /*  OUT   : - integer value to get from the console interface */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       */
      /*  Variables declaration */
      coin_choice = 0;
      /*  Get and check the data from the console */
      int exitg2;
      do {
        exitg2 = 0;
        char *format;
        int exitg3;
        int nb_input_types;
        char terminator;
        do {
          exitg3 = 0;
          /*  Get input data using the Windows C API */
          terminator = ' ';
          printf("%s", "Enter the menu entry corresponding to the coins value "
                       "to give back [0-4]: ");
          fflush(stdout);
          /*  Force the string format definition in the generated C code for
           * scanf_s */
          format = "%d%c";
          nb_input_types = scanf_s(format, &coin_choice, &terminator, 1);
          /*  Check if the provided data is an integer number */
          if ((nb_input_types == 2) && (terminator == '\n')) {
            exitg3 = 1;
          } else {
            char *CLEAR_STDIN;
            printf("The value provided is not of the right data type!\n");
            fflush(stdout);
            /*  Force the string regular expression in the generated C code for
             * scanf_s */
            CLEAR_STDIN = "%*[^\n]%*1[\n]";
            /*  Clear the input buffer */
            scanf_s(CLEAR_STDIN);
          }
        } while (exitg3 == 0);
        /*  Check if the value is within the allowed range */
        if ((coin_choice >= 0) && (coin_choice <= 4)) {
          exitg2 = 1;
        } else {
          printf("The value provided must be between %d and %d!\n", 0, 4);
          fflush(stdout);
        }
      } while (exitg2 == 0);
      /*  Select the specific coin's value to give back  */
      switch (coin_choice) {
      case 0:
        /*  Split sections */
        printf("%s\n\n", "-----------------------------------------------------"
                         "--------------------------");
        fflush(stdout);
        exitg1 = 1;
        break;
      case 1:
        give_back_coin(10U);
        break;
      case 2:
        give_back_coin(20U);
        break;
      case 3:
        give_back_coin(50U);
        break;
      default:
        give_back_coin(100U);
        break;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * Function that is not translated into C code
 *
 * Arguments    : void
 * Return Type  : void
 */
static void TestMode_write_register(void)
{
  static const unsigned short uv[7] = {40960U, 40961U, 40962U, 40963U,
                                       40976U, 40977U, 40978U};
  int data;
  int exitg1;
  int register_text;
  bool is_right_value;
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function write_register() */
  /*  Goal  : Test the write access function to any shared memory register */
  /*  IN    : - const_obj: object containing all needed constants */
  /*          - f_api    : functions handler struct listing functions to access
   */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Text constants declaration */
  /*  Variables declaration */
  is_right_value = false;
  /*  Split sections  */
  printf("%s\n", "-------------------------------------------------------------"
                 "------------------");
  fflush(stdout);
  /*  Get the address of the register to access  */
  char *format;
  int i;
  bool exitg2;
  do {
    exitg1 = 0;
    printf("%s",
           "Enter the address of the register to access in hexadecimal within "
           "the following range [0xA000-0xA003] or [0xA010-0xA012]: ");
    fflush(stdout);
    /*  Force the string format definition in the generated C code for scanf_s
     */
    format = "%x";
    scanf_s(format, &register_text);
    /*  Check if the provided address is pointing to an existing register  */
    i = 0;
    exitg2 = false;
    while ((!exitg2) && (i < 7)) {
      if ((unsigned short)register_text == uv[i]) {
        is_right_value = true;
        exitg2 = true;
      } else {
        i++;
      }
    }
    /*  The provided address is not within the right range of addresses  */
    if (!is_right_value) {
      char *CLEAR_STDIN;
      printf(
          "The address provided is not within the right range of addresses!\n");
      fflush(stdout);
      /*  Force the string regular expression in the generated C code for
       * scanf_s */
      CLEAR_STDIN = "%*[^\n]%*1[\n]";
      /*  Clear the input buffer */
      scanf_s(CLEAR_STDIN);
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  /*  Get the data to write in the register  */
  /*  Function that is not translated into C code */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function check_get_data() */
  /*  Goal  : Test the write access function to any shared memory register */
  /*  IN    : - promp_text: pointer to a chain char to display in the console */
  /*          - min_data  : minimum value that is allowed in the range of data
   */
  /*          - max_data  : maximum value that is allowed in the range of data
   */
  /*  IN/OUT: - */
  /*  OUT   : - integer value to get from the console interface */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Variables declaration */
  data = 0;
  /*  Get and check the data from the console */
  do {
    exitg1 = 0;
    char *b_format;
    int exitg3;
    int nb_input_types;
    char terminator;
    do {
      exitg3 = 0;
      /*  Get input data using the Windows C API */
      terminator = ' ';
      printf("%s",
             "Enter the integer data to write at the selected register: ");
      fflush(stdout);
      /*  Force the string format definition in the generated C code for scanf_s
       */
      b_format = "%d%c";
      nb_input_types = scanf_s(b_format, &data, &terminator, 1);
      /*  Check if the provided data is an integer number */
      if ((nb_input_types == 2) && (terminator == '\n')) {
        exitg3 = 1;
      } else {
        char *b_CLEAR_STDIN;
        printf("The value provided is not of the right data type!\n");
        fflush(stdout);
        /*  Force the string regular expression in the generated C code for
         * scanf_s */
        b_CLEAR_STDIN = "%*[^\n]%*1[\n]";
        /*  Clear the input buffer */
        scanf_s(b_CLEAR_STDIN);
      }
    } while (exitg3 == 0);
    /*  Check if the value is within the allowed range */
    if ((data >= 0) && (data <= 999)) {
      exitg1 = 1;
    } else {
      printf("The value provided must be between %d and %d!\n", 0, 999);
      fflush(stdout);
    }
  } while (exitg1 == 0);
  /*  Write the user's data to the selected register  */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function write_interface() */
  /*  Goal  : Define the interface layer writing data to external HW registers
   */
  /*  IN    : - register_address: address of the register in unsigned 16 bit */
  /*          - new_value: value to store in the register as an unsigned 8 bit
   */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  write_register((unsigned short)register_text, data);
  printf("%s\n\n", "The desired value has been successfully written in the "
                   "selected register.");
  fflush(stdout);
  printf("%s\n", "-------------------------------------------------------------"
                 "------------------");
  fflush(stdout);
}

/*
 * New 7 segments encoded value to write in the corresponding HW register
 *  Assignment of the new digit value to display
 *
 * Arguments    : unsigned char display_ID
 *                int digit_value
 *                double dot_segment
 * Return Type  : void
 */
static void b_display_digit(unsigned char display_ID, int digit_value,
                            double dot_segment)
{
  unsigned char new_reg_value;
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function display_digit() */
  /*  Goal  : Update a 7 segments display with a new digit value */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - display_ID : identification number of the 7 segments display */
  /*          - digit_value: base 10 value to display on the 7 segments display
   */
  /*          - dot_segment: enable the dot segment => '1' */
  /*                         do not enable the dot segment => '0' */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  switch (digit_value) {
  case 0:
    new_reg_value = 63U;
    break;
  case 1:
    new_reg_value = 6U;
    break;
  case 2:
    new_reg_value = 91U;
    break;
  case 3:
    new_reg_value = 79U;
    break;
  case 4:
    new_reg_value = 102U;
    break;
  case 5:
    new_reg_value = 109U;
    break;
  case 6:
    new_reg_value = 125U;
    break;
  case 7:
    new_reg_value = 7U;
    break;
  case 8:
    new_reg_value = 127U;
    break;
  case 9:
    new_reg_value = 111U;
    break;
  case 45:
    new_reg_value = 64U;
    break;
  default:
    /*  Incorrect 7 segments encoded value given to the selected HW register */
    new_reg_value = 0U;
    break;
  }
  /*  Add the encoding of the dot segment if needed */
  if (dot_segment == 1.0) {
    new_reg_value = (unsigned char)(new_reg_value | 128);
  }
  /*  Update of the desired display */
  switch (display_ID) {
  case 1U:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40960, new_reg_value);
    break;
  case 2U:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40961, new_reg_value);
    break;
  default:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40962, new_reg_value);
    break;
  }
}

/*
 * Arguments    : Scheduler *this
 * Return Type  : void
 */
static void c_Scheduler_Scheduler_ExitInter(Scheduler *this)
{
  switch ((int)this->StateflowInternalData.ActiveChildVars
              .ActiveChildVar_Scheduler) {
  case 1:
    /* State: CHECK_COINS */
    /* State Scheduler.CHECK_COINS becomes inactive */
    this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler = 0.0;
    break;
  case 3:
    /* State: INITIALIZATION */
    /* State Scheduler.INITIALIZATION becomes inactive */
    this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler = 0.0;
    break;
  case 2:
    /* State: PURCHASE_CHECK */
    /* State Scheduler.PURCHASE_CHECK becomes inactive */
    this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler = 0.0;
    break;
  case 13:
    /* State: PURCHASE_TICKET */
    switch ((int)this->StateflowInternalData.ActiveChildVars
                .ActiveChildVar_PURCHASE_TICKET) {
    case 35:
      /* State: CANCEL_CHECK */
      /* State Scheduler.PURCHASE_TICKET.CANCEL_CHECK becomes inactive */
      this->StateflowInternalData.ActiveChildVars
          .ActiveChildVar_PURCHASE_TICKET = 0.0;
      break;
    case 21:
      /* State: CANCEL_PURCHASE */
      /* State Scheduler.PURCHASE_TICKET.CANCEL_PURCHASE becomes inactive */
      this->StateflowInternalData.ActiveChildVars
          .ActiveChildVar_PURCHASE_TICKET = 0.0;
      break;
    case 40:
      /* State: COIN_CHECK */
      /* State Scheduler.PURCHASE_TICKET.COIN_CHECK becomes inactive */
      this->StateflowInternalData.ActiveChildVars
          .ActiveChildVar_PURCHASE_TICKET = 0.0;
      break;
    case 46:
      /* State: INITIALIZATION */
      /* State Scheduler.PURCHASE_TICKET.INITIALIZATION becomes inactive */
      this->StateflowInternalData.ActiveChildVars
          .ActiveChildVar_PURCHASE_TICKET = 0.0;
      break;
    case 33:
      /* State: PRINT_RECEIPT */
      /* State Scheduler.PURCHASE_TICKET.PRINT_RECEIPT becomes inactive */
      this->StateflowInternalData.ActiveChildVars
          .ActiveChildVar_PURCHASE_TICKET = 0.0;
      break;
    case 22:
      /* State: UPDATE_AMOUNT */
      /* State Scheduler.PURCHASE_TICKET.UPDATE_AMOUNT becomes inactive */
      this->StateflowInternalData.ActiveChildVars
          .ActiveChildVar_PURCHASE_TICKET = 0.0;
      break;
    }
    /* State Scheduler.PURCHASE_TICKET becomes inactive */
    this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler = 0.0;
    break;
  case 4:
    /* State: STOP_EXECUTION */
    /* State Scheduler.STOP_EXECUTION becomes inactive */
    this->StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler = 0.0;
    break;
  }
}

/*
 * New 7 segments encoded value to write in the corresponding HW register
 *  Assignment of the new digit value to display
 *
 * Arguments    : unsigned char display_ID
 *                unsigned short digit_value
 *                double dot_segment
 * Return Type  : void
 */
static void display_digit(unsigned char display_ID, unsigned short digit_value,
                          double dot_segment)
{
  unsigned char new_reg_value;
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function display_digit() */
  /*  Goal  : Update a 7 segments display with a new digit value */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - display_ID : identification number of the 7 segments display */
  /*          - digit_value: base 10 value to display on the 7 segments display
   */
  /*          - dot_segment: enable the dot segment => '1' */
  /*                         do not enable the dot segment => '0' */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  switch (digit_value) {
  case 0U:
    new_reg_value = 63U;
    break;
  case 1U:
    new_reg_value = 6U;
    break;
  case 2U:
    new_reg_value = 91U;
    break;
  case 3U:
    new_reg_value = 79U;
    break;
  case 4U:
    new_reg_value = 102U;
    break;
  case 5U:
    new_reg_value = 109U;
    break;
  case 6U:
    new_reg_value = 125U;
    break;
  case 7U:
    new_reg_value = 7U;
    break;
  case 8U:
    new_reg_value = 127U;
    break;
  case 9U:
    new_reg_value = 111U;
    break;
  case 45U:
    new_reg_value = 64U;
    break;
  default:
    /*  Incorrect 7 segments encoded value given to the selected HW register */
    new_reg_value = 0U;
    break;
  }
  /*  Add the encoding of the dot segment if needed */
  if (dot_segment == 1.0) {
    new_reg_value = (unsigned char)(new_reg_value | 128);
  }
  /*  Update of the desired display */
  switch (display_ID) {
  case 1U:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40960, new_reg_value);
    break;
  case 2U:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40961, new_reg_value);
    break;
  default:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40962, new_reg_value);
    break;
  }
}

/*
 * Arguments    : int numerator
 * Return Type  : int
 */
static int div_nde_s32_floor(int numerator)
{
  int i;
  if ((numerator < 0) && (numerator % 10 != 0)) {
    i = -1;
  } else {
    i = 0;
  }
  return numerator / 10 + i;
}

/*
 * Select the correct coin to give back
 *
 * Arguments    : unsigned short amount
 * Return Type  : void
 */
static void give_back_coin(unsigned short amount)
{
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function give_back_coin() */
  /*  Goal  : Return coins change to the user based on computed amount of money
   */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount: integer value corresponding to a specific coin */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  switch (amount) {
  case 10U: {
    unsigned char a;
    unsigned char register_value;
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW
     * registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8
     * bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    a = read_register(40963);
    /*  Set the selected bit to '1' and write the new value to the register */
    register_value = (unsigned char)(a | 1);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, register_value);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, (unsigned char)(register_value ^ 1));
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
  } break;
  case 20U: {
    unsigned char b_a;
    unsigned char b_register_value;
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW
     * registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8
     * bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    b_a = read_register(40963);
    /*  Set the selected bit to '1' and write the new value to the register */
    b_register_value = (unsigned char)(b_a | 2);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, b_register_value);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, (unsigned char)(b_register_value ^ 2));
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
  } break;
  case 50U: {
    unsigned char c_a;
    unsigned char c_register_value;
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW
     * registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8
     * bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    c_a = read_register(40963);
    /*  Set the selected bit to '1' and write the new value to the register */
    c_register_value = (unsigned char)(c_a | 4);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, c_register_value);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, (unsigned char)(c_register_value ^ 4));
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
  } break;
  case 100U: {
    unsigned char d_a;
    unsigned char d_register_value;
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW
     * registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8
     * bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    d_a = read_register(40963);
    /*  Set the selected bit to '1' and write the new value to the register */
    d_register_value = (unsigned char)(d_a | 8);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, d_register_value);
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers
     */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*          - new_value: value to store in the register as an unsigned 8 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    write_register(40963, (unsigned char)(d_register_value ^ 8));
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of
     * time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    Sleep(250);
    /*  Sleep asks milliseconds as input */
  } break;
  default:
    printf("Incorrect coin\'s value provided to the parking meter change "
           "module!\n");
    fflush(stdout);
    break;
  }
}

/*
 * Arguments    : unsigned short amount_to_return
 *                unsigned short coin_value
 * Return Type  : unsigned short
 */
static unsigned short return_coin_value(unsigned short amount_to_return,
                                        unsigned short coin_value)
{
  unsigned short remaining_amount;
  bool exitg1;
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function return_coin_value() */
  /*  Goal  : give back the remaining amount of coins to return */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount_to_return: integer representing the money to give back */
  /*          - coin_value : integer representing the value of the current coin
   */
  /*  IN/OUT: - */
  /*  OUT   : -  integer representing the remaining amount of coins to return */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  remaining_amount = amount_to_return;
  /*  Try to return as much coins as possible */
  exitg1 = false;
  while ((!exitg1) && (remaining_amount >= coin_value)) {
    unsigned char register_value;
    bool available;
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function is_this_coin_available() */
    /*  Goal  : check if a specific coin's value is still available in the cash
     * box */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - integer representing the coin's value */
    /*  IN/OUT: - */
    /*  OUT   : - boolean stating if this coin's value is still available or not
     */
    /*            '0' => coin's value not available anymore */
    /*            '1' => coin's value still available */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    available = false;
    /*  Get the current register's status of the available coins in the cash box
     */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW
     * registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit
     */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8
     * bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    register_value = read_register(40978);
    /*  Select the specific coin's quantity to check */
    switch (coin_value) {
    case 10U:
      available = ((register_value & 1) != 0);
      break;
    case 20U:
      available = ((register_value & 2) != 0);
      break;
    case 50U:
      available = ((register_value & 4) != 0);
      break;
    case 100U:
      available = ((register_value & 8) != 0);
      break;
    default:
      printf("Incorrect coin\'s value provided to the parking meter cash box "
             "module!\n");
      fflush(stdout);
      break;
    }
    if (available) {
      give_back_coin(coin_value);
      remaining_amount -= coin_value;
    } else {
      exitg1 = true;
    }
  }
  return remaining_amount;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

/*
 * Initialization
 *
 * Arguments    : void
 * Return Type  : void
 */
static void standard_operation_mode(void)
{
  Scheduler chart;
  int i;
  int i1;
  int i2;
  bool master_switch_off;
  bool red_button_pressed;
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function standard_operation_mode() */
  /*  Goal  : Entry point of the standard mode of operation of the parking meter
   */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  red_button_pressed = false;
  master_switch_off = false;
  /*  Instanciation of the Stateflow Chart Object */
  chart.REFRESHING_TICK = 0.0;
  chart.obj.sampling_time = 0.001;
  chart.obj.refreshing_time = 0.015;
  chart.obj.master_switch = true;
  chart.obj.green_pressed = false;
  chart.obj.red_pressed = false;
  chart.obj.coins_reg_value = 0U;
  chart.obj.inserted_amount = 0U;
  chart.obj.amount_to_return = 0U;
  chart.obj.flap_open = false;
  chart.obj.register_value = 0U;
  chart.obj.display_value = 0U;
  for (i = 0; i < 7; i++) {
    chart.obj.ISR[i] = false;
  }
  chart.StateflowInternalData.CurrentTime = 0.0;
  chart.StateflowInternalData.IsExecuting = false;
  chart.StateflowInternalData.ConfigurationOptions.EnableAnimation = true;
  chart.StateflowInternalData.ConfigurationOptions.ExecuteInitStep = true;
  chart.StateflowInternalData.ConfigurationOptions.WarningOnUninitializedData =
      true;
  chart.StateflowInternalData.ConfigurationOptions.AnimationDelay = 0.0;
  chart.StateflowInternalData.ConfigurationOptions.EventQueueSize = 20.0;
  chart.StateflowInternalData.ConfigurationOptions.MATLABTimer = true;
  chart.StateflowInternalData.ConfigurationOptions.ClockSpeedFactor = 1.0;
  chart.StateflowInternalData.IsActiveVars.IsActiveVar_Scheduler = false;
  chart.StateflowInternalData.ActiveChildVars.ActiveChildVar_Scheduler = -1.0;
  chart.StateflowInternalData.ActiveChildVars.ActiveChildVar_PURCHASE_TICKET =
      -1.0;
  chart.StateflowInternalData.StepCounters.Scheduler = 0.0;
  chart.StateflowInternalData.StepCounters.c_Scheduler_PURCHASE_TICKET_UPD =
      0.0;
  Scheduler_step(&chart);
  /*  Infinite loop */
  do {
    /*  Run the scheduler in Stateflow */
    Scheduler_step(&chart);
    /*  Process ISRs when raised */
    int exitg1;
    bool x[7];
    do {
      int k;
      bool exitg2;
      bool y;
      exitg1 = 0;
      for (i1 = 0; i1 < 7; i1++) {
        x[i1] = chart.obj.ISR[i1];
      }
      y = false;
      k = 0;
      exitg2 = false;
      while ((!exitg2) && (k < 7)) {
        if (x[k]) {
          y = true;
          exitg2 = true;
        } else {
          k++;
        }
      }
      if (y) {
        int b_k;
        int idx;
        int ii;
        int ii_size_idx_1;
        signed char ii_data[7];
        /*  Identified raised ISRs */
        for (i2 = 0; i2 < 7; i2++) {
          x[i2] = chart.obj.ISR[i2];
        }
        idx = 0;
        ii = 0;
        exitg2 = false;
        while ((!exitg2) && (ii < 7)) {
          if (x[ii]) {
            idx++;
            ii_data[idx - 1] = (signed char)(ii + 1);
            if (idx >= 7) {
              exitg2 = true;
            } else {
              ii++;
            }
          } else {
            ii++;
          }
        }
        if (idx < 1) {
          ii_size_idx_1 = 0;
        } else {
          ii_size_idx_1 = idx;
        }
        b_k = 0;
        exitg2 = false;
        while ((!exitg2) && (b_k <= ii_size_idx_1 - 1)) {
          bool guard1;
          guard1 = false;
          switch (ii_data[b_k]) {
          case 1: {
            /*  Update the values of the 7 segment displays */
            /*  Initialization value of the parking meter display */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function display_cents_value() */
            /*  Goal  : Update the new parking meter cents value */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - cents_value: base 10 value to display on all 7
             * segments displays */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            if (chart.obj.display_value == 45) {
              display_digit(1U, 45U, 0.0);
              display_digit(2U, 45U, 0.0);
              display_digit(3U, 45U, 0.0);
              /*  Compute the right value to display on the parking meter */
            } else if (chart.obj.display_value <= 999) {
              unsigned short b_remainder;
              unsigned short b_x;
              unsigned short digit_value;
              /*  Compute the cent */
              digit_value =
                  (unsigned short)(chart.obj.display_value -
                                   (unsigned int)((int)(chart.obj
                                                            .display_value /
                                                        10U) *
                                                  10));
              display_digit(1U, digit_value, 0.0);
              /*  Compute the tens of cents */
              b_remainder = (unsigned short)rt_roundd(
                  (double)(unsigned short)(chart.obj.display_value -
                                           digit_value) /
                  10.0);
              digit_value =
                  (unsigned short)(b_remainder -
                                   (unsigned int)((int)(b_remainder / 10U) *
                                                  10));
              display_digit(2U, digit_value, 0.0);
              /*  Compute the hundreds of cents */
              b_x = (unsigned short)rt_roundd(
                  (double)(unsigned short)(b_remainder - digit_value) / 10.0);
              display_digit(
                  3U,
                  (unsigned short)(b_x - (unsigned int)((int)(b_x / 10U) * 10)),
                  1.0);
            } else {
              printf("Incorrect cents value provided to the parking meter "
                     "display!\n");
              fflush(stdout);
            }
            guard1 = true;
          } break;
          case 2: {
            int i3;
            unsigned char register_value;
            /*  Update the coins flap status */
            /*  Get the current peripherals register status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function set_coin_flap_position() */
            /*  Goal  : Open or close the coin's flap */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - flap_open: '1' => coin flap to open */
            /*                       '0' => coin flap to close */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            register_value = read_register(40963);
            /*  Set the corresponding bit of the register depending on flap_open
             */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function write_interface() */
            /*  Goal  : Define the interface layer writing data to external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*          - new_value: value to store in the register as an
             * unsigned 8 bit */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            if (chart.obj.flap_open) {
              i3 = register_value | 128;
            } else {
              i3 = register_value & 127;
            }
            write_register(40963, (unsigned char)i3);
            guard1 = true;
          } break;
          case 3: {
            unsigned char c_register_value;
            unsigned char d_a;
            unsigned char f_a;
            unsigned char h_a;
            unsigned char i_a;
            unsigned char j_a;
            /*  Check if the parking meter can give money back if needed */
            /*  Check if any coin's value is empty */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_able_to_give_back_any_coins() */
            /*  Goal  : check if a specific coin's value is still available in
             * the cash box */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still
             * available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in
             * the cash box */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still
             * available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Get the current register's status of the available coins in the
             * cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            d_a = read_register(40978);
            /*  Select the specific coin's quantity to check */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in
             * the cash box */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still
             * available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Get the current register's status of the available coins in the
             * cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            f_a = read_register(40978);
            /*  Select the specific coin's quantity to check */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in
             * the cash box */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still
             * available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Get the current register's status of the available coins in the
             * cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            h_a = read_register(40978);
            /*  Select the specific coin's quantity to check */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in
             * the cash box */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still
             * available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Get the current register's status of the available coins in the
             * cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            i_a = read_register(40978);
            /*  Select the specific coin's quantity to check */
            /*  Get the current peripherals register status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function switch_leds_on() */
            /*  Goal  : Open or close the coin's flap */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - can_give_coins_back: '1' => yes, it can give coins
             * back */
            /*                                 '0' => no, because the cash box
             * is empty */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            j_a = read_register(40963);
            c_register_value = (unsigned char)(j_a & 159);
            /*  Set the corresponding bit of the register depending on
             * can_give_coins_back */
            if (((d_a & 1) != 0) && ((f_a & 2) != 0) && ((h_a & 4) != 0) &&
                ((i_a & 8) != 0)) {
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW
               * registers */
              /*  IN    : - register_address: address of the register in
               * unsigned 16 bit */
              /*          - new_value: value to store in the register as an
               * unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              write_register(40963, (unsigned char)(c_register_value | 32));
            } else {
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW
               * registers */
              /*  IN    : - register_address: address of the register in
               * unsigned 16 bit */
              /*          - new_value: value to store in the register as an
               * unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              write_register(40963, (unsigned char)(c_register_value | 64));
            }
            guard1 = true;
          } break;
          case 4: {
            unsigned short remaining_amount;
            if (!chart.obj.red_pressed) {
              unsigned char b_register_value;
              unsigned char c_a;
              /*  Print the parking ticket */
              /*  Trigger the printing of the parking receipt */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function print_receipt() */
              /*  Goal  : Command the parking meter to print the corresponding
               * receipt */
              /*  IN    : - const_obj: constants object used in the entire
               * application */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Read the current value stored in the register */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function generate_peripherals_pulse() */
              /*  Goal  : Every time an action is applied to the peripherals,
               * the */
              /*          corresponding bit in the peripherals register is set
               * or reset */
              /*  IN    : - const_obj: constants object used in the entire
               * application */
              /*          - bit_mask: mask of the specific bit to modify in the
               * register */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function read_interface() */
              /*  Goal  : Define the interface layer reading data from external
               * HW registers */
              /*  IN    : - register_address: address of the register in
               * unsigned 16 bit */
              /*  IN/OUT: - */
              /*  OUT   : - register_value: value stored in the register as an
               * unsigned 8 bit */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              c_a = read_register(40963);
              /*  Set the selected bit to '1' and write the new value to the
               * register */
              b_register_value = (unsigned char)(c_a | 16);
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW
               * registers */
              /*  IN    : - register_address: address of the register in
               * unsigned 16 bit */
              /*          - new_value: value to store in the register as an
               * unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              write_register(40963, b_register_value);
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function sleep_interface() */
              /*  Goal  : Define the interface layer to pause the system for an
               * amount of time */
              /*  IN    : - duration: time duration in seconds */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              Sleep(250);
              /*  Sleep asks milliseconds as input */
              /*  Reset the selected bit only and write the new value to the
               * register */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW
               * registers */
              /*  IN    : - register_address: address of the register in
               * unsigned 16 bit */
              /*          - new_value: value to store in the register as an
               * unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              write_register(40963, (unsigned char)(b_register_value ^ 16));
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function sleep_interface() */
              /*  Goal  : Define the interface layer to pause the system for an
               * amount of time */
              /*  IN    : - duration: time duration in seconds */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              Sleep(250);
              /*  Sleep asks milliseconds as input */
            }
            /*  Give back coin's change */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function return_coins() */
            /*  Goal  : give back the desired amount of coins to the user */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - desired_amount: integer representing the money to give
             * back */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Return as much as possible higher coin's values at first */
            remaining_amount =
                return_coin_value(chart.obj.amount_to_return, 100U);
            remaining_amount = return_coin_value(remaining_amount, 50U);
            remaining_amount = return_coin_value(remaining_amount, 20U);
            return_coin_value(remaining_amount, 10U);
            chart.obj.amount_to_return = 0U;
            guard1 = true;
          } break;
          case 5: {
            unsigned char b_a;
            unsigned char e_a;
            unsigned char g_a;
            /*  Check if the buttons have changed their states */
            /*  Bit mask to extract green button status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_green_button_pressed() */
            /*  Goal  : Poll the button register continuously to see if the
             * green button has */
            /*          been pressed */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean: '0' => green button not pressed */
            /*                     '1' => green button pressed */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            b_a = read_register(40976);
            chart.obj.green_pressed = ((b_a & 1) != 0);
            /*  Bit mask to extract red button status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_red_button_pressed() */
            /*  Goal  : Poll the button register when needed to see if the red
             * button has been */
            /*          pressed to cancel the ticket purchase process */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean: '0' => red button not pressed */
            /*                     '1' => red button pressed */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            e_a = read_register(40976);
            chart.obj.red_pressed = ((e_a & 2) != 0);
            /*  Bit mask to extract master switch status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function is_master_switch_on() */
            /*  Goal  : Check the button register to see if the master switch
             * has been */
            /*          switched off */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean: '0' => master switch is OFF */
            /*                     '1' => master switch is ON */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            g_a = read_register(40976);
            chart.obj.master_switch = ((g_a & 4) != 0);
            /*  Ticket's purchase process canceled */
            if (chart.obj.red_pressed) {
              unsigned short b_remaining_amount;
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Function return_coins() */
              /*  Goal  : give back the desired amount of coins to the user */
              /*  IN    : - const_obj: constants object used in the entire
               * application */
              /*          - desired_amount: integer representing the money to
               * give back */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
               */
              /*  Return as much as possible higher coin's values at first */
              b_remaining_amount =
                  return_coin_value(chart.obj.amount_to_return, 100U);
              b_remaining_amount = return_coin_value(b_remaining_amount, 50U);
              b_remaining_amount = return_coin_value(b_remaining_amount, 20U);
              return_coin_value(b_remaining_amount, 10U);
              red_button_pressed = true;
              exitg2 = true;
            } else {
              guard1 = true;
            }
          } break;
          case 6: {
            unsigned short u;
            unsigned char a;
            unsigned char new_reg_value;
            /*  Update the amount of money to pay if a coin has been inserted */
            a = chart.obj.register_value;
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function amount_inserted_coins() */
            /*  Goal  : get the amount of the inserted coins */
            /*  IN    : - const_obj: constants object used in the entire
             * application */
            /*          - integer representing the current amount of inserted
             * coins */
            /*  IN/OUT: - */
            /*  OUT   : - integer representing the updated amount of inserted
             * coins */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            u = 0U;
            /*  Get the very last amount of coins that have already been
             * inserted */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            new_reg_value = read_register(40977);
            /*  A new coin has been inserted into the parking meter */
            if (new_reg_value != chart.obj.register_value) {
              /*  Update the amount of coins already inserted */
              if (((new_reg_value & 1) != 0) &&
                  ((chart.obj.register_value & 1) == 0)) {
                u = 10U;
              } else if (((new_reg_value & 2) != 0) &&
                         ((chart.obj.register_value & 2) == 0)) {
                u = 20U;
              } else if (((new_reg_value & 4) != 0) &&
                         ((chart.obj.register_value & 4) == 0)) {
                u = 50U;
              } else if (((new_reg_value & 8) != 0) &&
                         ((chart.obj.register_value & 8) == 0)) {
                u = 100U;
              } else if (((new_reg_value & 16) != 0) &&
                         ((chart.obj.register_value & 16) == 0)) {
                u = 200U;
              }
              /*  Record of the current register value */
              a = new_reg_value;
            }
            chart.obj.temp_amount = u;
            chart.obj.register_value = a;
            chart.obj.inserted_amount += u;
            guard1 = true;
          } break;
          default:
            /*  Terminate the execution of the application */
            master_switch_off = true;
            exitg2 = true;
            break;
          }
          if (guard1) {
            /*  Reset the ISR once it has been served */
            chart.obj.ISR[ii_data[b_k] - 1] = false;
            b_k++;
          }
        }
        /*  Exit the inner loop as a ticket purchase will not be performed */
        if (master_switch_off || red_button_pressed) {
          exitg1 = 1;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    /*  Exit the program properly if the master switch is off */
  } while (!master_switch_off);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void parkingMeterLowLevel(void)
{
  int b_i;
  if (!isInitialized_parkingMeterLowLevel) {
    parkingMeterLowLevel_initialize();
  }
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Function parkingMeterLowLevel() */
  /*  Goal  : Main entry point of the parking meter application */
  /*  IN    : - */
  /*  IN/OUT: - */
  /*  OUT   : - error_flag: error code */
  /*  */
  /*  Copyright 2023 The MathWorks, Inc. */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   */
  /*  Initialization */
  if (TEST_MODE == 0) {
    /*  Instantiate all constants for the normal application */
    printf("The normal mode of operation of the parking meter has been "
           "activated.\n");
    fflush(stdout);
    printf("Feel free to purchase tickets.\n");
    fflush(stdout);
    standard_operation_mode();
    printf(
        "The Master Switch of the Parking Meter Interface is switched off.\n");
    fflush(stdout);
    printf("Press \'ENTER\' to close the console window...\n");
    fflush(stdout);
    getchar();
  } else {
    int choice;
    /*  TEST_MODE == 1 */
    /*  Function handler API to access functions of the test mode */
    /*  Instantiate all properties and methods for the test mode */
    /*  Entry point of the test mode */
    /*  Text constant declaration */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Function test_mode() */
    /*  Goal  : Entry point of the test mode of the parking meter */
    /*  IN    : - test_obj: object having all needed properties and methods for
     * the */
    /*                      testing mode of operation */
    /*          - f_api   : functions handler struct listing functions to access
     */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     */
    /*  Variables declaration */
    choice = 1;
    /*  Split sections */
    printf("%s\n", "-----------------------------------------------------------"
                   "--------------------");
    fflush(stdout);
    /*  Loop over the menu entries */
    int exitg1;
    do {
      exitg1 = 0;
      if (choice != 0) {
        int exitg2;
        int exitg3;
        /*  Menu selection */
        printf("Operations on the parking meter:\n");
        fflush(stdout);
        printf(">> 0 - Leave\n");
        fflush(stdout);
        printf(">> 1 - Write in registers\n");
        fflush(stdout);
        printf(">> 2 - Display an amount of money\n");
        fflush(stdout);
        printf(">> 3 - Switch on and off LEDs\n");
        fflush(stdout);
        printf(">> 4 - Give back a coin\n");
        fflush(stdout);
        printf(">> 5 - Print a parking ticket\n");
        fflush(stdout);
        printf(">> 6 - Open and close the coin\'s flap\n");
        fflush(stdout);
        printf(">> 7 - Display status of input registers\n");
        fflush(stdout);
        printf(">> 8 - Normal handling of the parking meter\n");
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        /*  Get and check the menu entry provided at the console interface */
        /*  Function that is not translated into C code */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
         */
        /*  Function check_get_data() */
        /*  Goal  : Test the write access function to any shared memory register
         */
        /*  IN    : - promp_text: pointer to a chain char to display in the
         * console */
        /*          - min_data  : minimum value that is allowed in the range of
         * data */
        /*          - max_data  : maximum value that is allowed in the range of
         * data */
        /*  IN/OUT: - */
        /*  OUT   : - integer value to get from the console interface */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
         */
        /*  Variables declaration */
        choice = 0;
        /*  Get and check the data from the console */
        do {
          exitg2 = 0;
          char *format;
          int nb_input_types;
          char terminator;
          do {
            exitg3 = 0;
            /*  Get input data using the Windows C API */
            terminator = ' ';
            printf("%s", "Enter the menu entry of the operation to do on the "
                         "parking meter [0 - 8]: ");
            fflush(stdout);
            /*  Force the string format definition in the generated C code for
             * scanf_s */
            format = "%d%c";
            nb_input_types = scanf_s(format, &choice, &terminator, 1);
            /*  Check if the provided data is an integer number */
            if ((nb_input_types == 2) && (terminator == '\n')) {
              exitg3 = 1;
            } else {
              char *CLEAR_STDIN;
              printf("The value provided is not of the right data type!\n");
              fflush(stdout);
              /*  Force the string regular expression in the generated C code
               * for scanf_s */
              CLEAR_STDIN = "%*[^\n]%*1[\n]";
              /*  Clear the input buffer */
              scanf_s(CLEAR_STDIN);
            }
          } while (exitg3 == 0);
          /*  Check if the value is within the allowed range */
          if ((choice >= 0) && (choice <= 8)) {
            exitg2 = 1;
          } else {
            printf("The value provided must be between %d and %d!\n", 0, 8);
            fflush(stdout);
          }
        } while (exitg2 == 0);
        printf("\n");
        fflush(stdout);
        switch (choice) {
        case 0:
          exitg1 = 1;
          break;
        case 1:
          TestMode_write_register();
          break;
        case 2: {
          int data;
          /*  Text constants declaration  */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function display_value() */
          /*  Goal  : Test the 7 segments displays by displaying any value on
           * them */
          /*  IN    : - const_obj: object containing all needed constants */
          /*          - f_api    : functions handler struct listing functions to
           * access */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration  */
          /*  Split sections  */
          printf("%s\n", "-----------------------------------------------------"
                         "--------------------------");
          fflush(stdout);
          /*  Get the data to write in the register  */
          /*  Function that is not translated into C code */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function check_get_data() */
          /*  Goal  : Test the write access function to any shared memory
           * register */
          /*  IN    : - promp_text: pointer to a chain char to display in the
           * console */
          /*          - min_data  : minimum value that is allowed in the range
           * of data */
          /*          - max_data  : maximum value that is allowed in the range
           * of data */
          /*  IN/OUT: - */
          /*  OUT   : - integer value to get from the console interface */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration */
          data = 0;
          /*  Get and check the data from the console */
          do {
            exitg2 = 0;
            char *b_format;
            int b_nb_input_types;
            char b_terminator;
            do {
              exitg3 = 0;
              /*  Get input data using the Windows C API */
              b_terminator = ' ';
              printf("%s", "Enter the hundreds of cents value to print on the "
                           "7 segments displays: ");
              fflush(stdout);
              /*  Force the string format definition in the generated C code for
               * scanf_s */
              b_format = "%d%c";
              b_nb_input_types = scanf_s(b_format, &data, &b_terminator, 1);
              /*  Check if the provided data is an integer number */
              if ((b_nb_input_types == 2) && (b_terminator == '\n')) {
                exitg3 = 1;
              } else {
                char *b_CLEAR_STDIN;
                printf("The value provided is not of the right data type!\n");
                fflush(stdout);
                /*  Force the string regular expression in the generated C code
                 * for scanf_s */
                b_CLEAR_STDIN = "%*[^\n]%*1[\n]";
                /*  Clear the input buffer */
                scanf_s(b_CLEAR_STDIN);
              }
            } while (exitg3 == 0);
            /*  Check if the value is within the allowed range */
            if ((data >= 0) && (data <= 999)) {
              exitg2 = 1;
            } else {
              printf("The value provided must be between %d and %d!\n", 0, 999);
              fflush(stdout);
            }
          } while (exitg2 == 0);
          /*  Write the user's data to the 7 segments displays  */
          /*  Initialization value of the parking meter display */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function display_cents_value() */
          /*  Goal  : Update the new parking meter cents value */
          /*  IN    : - const_obj: constants object used in the entire
           * application */
          /*          - cents_value: base 10 value to display on all 7 segments
           * displays */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          if (data == 45) {
            display_digit(1U, 45U, 0.0);
            display_digit(2U, 45U, 0.0);
            display_digit(3U, 45U, 0.0);
            /*  Compute the right value to display on the parking meter */
          } else {
            int b_remainder;
            int digit_value;
            int x;
            /*  Compute the cent */
            digit_value = data - data / 10 * 10;
            b_display_digit(1U, digit_value, 0.0);
            /*  Compute the tens of cents */
            b_remainder = (int)rt_roundd((double)(data - digit_value) / 10.0);
            digit_value = b_remainder - div_nde_s32_floor(b_remainder) * 10;
            b_display_digit(2U, digit_value, 0.0);
            /*  Compute the hundreds of cents */
            x = (int)rt_roundd((double)(b_remainder - digit_value) / 10.0);
            b_display_digit(3U, x - div_nde_s32_floor(x) * 10, 1.0);
          }
          printf("%s\n\n", "The desired value has been successfully written on "
                           "the 7 segments displays.");
          fflush(stdout);
          printf("%s\n", "-----------------------------------------------------"
                         "--------------------------");
          fflush(stdout);
        } break;
        case 3: {
          int state;
          unsigned char c_register_value;
          /*  Text constants declaration  */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function leds_return_money() */
          /*  Goal  : Test the LEDs showing if coins can be given back or not */
          /*  IN    : - const_obj: object containing all needed constants */
          /*          - f_api    : functions handler struct listing functions to
           * access */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration  */
          /*  Split sections  */
          printf("%s\n", "-----------------------------------------------------"
                         "--------------------------");
          fflush(stdout);
          /*  Get the data to write in the register  */
          /*  Function that is not translated into C code */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function check_get_data() */
          /*  Goal  : Test the write access function to any shared memory
           * register */
          /*  IN    : - promp_text: pointer to a chain char to display in the
           * console */
          /*          - min_data  : minimum value that is allowed in the range
           * of data */
          /*          - max_data  : maximum value that is allowed in the range
           * of data */
          /*  IN/OUT: - */
          /*  OUT   : - integer value to get from the console interface */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration */
          state = 0;
          /*  Get and check the data from the console */
          do {
            exitg2 = 0;
            char *c_format;
            int c_nb_input_types;
            char c_terminator;
            do {
              exitg3 = 0;
              /*  Get input data using the Windows C API */
              c_terminator = ' ';
              printf("%s", "State value of the give back cash LEDs [0-1]: ");
              fflush(stdout);
              /*  Force the string format definition in the generated C code for
               * scanf_s */
              c_format = "%d%c";
              c_nb_input_types = scanf_s(c_format, &state, &c_terminator, 1);
              /*  Check if the provided data is an integer number */
              if ((c_nb_input_types == 2) && (c_terminator == '\n')) {
                exitg3 = 1;
              } else {
                char *c_CLEAR_STDIN;
                printf("The value provided is not of the right data type!\n");
                fflush(stdout);
                /*  Force the string regular expression in the generated C code
                 * for scanf_s */
                c_CLEAR_STDIN = "%*[^\n]%*1[\n]";
                /*  Clear the input buffer */
                scanf_s(c_CLEAR_STDIN);
              }
            } while (exitg3 == 0);
            /*  Check if the value is within the allowed range */
            if ((state >= 0) && (state <= 1)) {
              exitg2 = 1;
            } else {
              printf("The value provided must be between %d and %d!\n", 0, 1);
              fflush(stdout);
            }
          } while (exitg2 == 0);
          unsigned char b_a;
          /*  Write the user's data to the peripherals */
          /*  Get the current peripherals register status */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function switch_leds_on() */
          /*  Goal  : Open or close the coin's flap */
          /*  IN    : - const_obj: constants object used in the entire
           * application */
          /*          - can_give_coins_back: '1' => yes, it can give coins back
           */
          /*                                 '0' => no, because the cash box is
           * empty */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function read_interface() */
          /*  Goal  : Define the interface layer reading data from external HW
           * registers */
          /*  IN    : - register_address: address of the register in unsigned 16
           * bit */
          /*  IN/OUT: - */
          /*  OUT   : - register_value: value stored in the register as an
           * unsigned 8 bit */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          b_a = read_register(40963);
          c_register_value = (unsigned char)(b_a & 159);
          /*  Set the corresponding bit of the register depending on
           * can_give_coins_back */
          if (state == 1) {
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function write_interface() */
            /*  Goal  : Define the interface layer writing data to external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*          - new_value: value to store in the register as an
             * unsigned 8 bit */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            write_register(40963, (unsigned char)(c_register_value | 32));
          } else {
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function write_interface() */
            /*  Goal  : Define the interface layer writing data to external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*          - new_value: value to store in the register as an
             * unsigned 8 bit */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            write_register(40963, (unsigned char)(c_register_value | 64));
          }
          printf("%s\n\n", "The desired value has been successfully written to "
                           "the give back cash LEDs.");
          fflush(stdout);
          printf("%s\n", "-----------------------------------------------------"
                         "--------------------------");
          fflush(stdout);
        } break;
        case 4:
          TestMode_give_back_coin();
          break;
        case 5: {
          unsigned char a;
          unsigned char register_value;
          /*  Trigger the printing of the parking receipt */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function print_receipt() */
          /*  Goal  : Command the parking meter to print the corresponding
           * receipt */
          /*  IN    : - const_obj: constants object used in the entire
           * application */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Read the current value stored in the register */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function generate_peripherals_pulse() */
          /*  Goal  : Every time an action is applied to the peripherals, the */
          /*          corresponding bit in the peripherals register is set or
           * reset */
          /*  IN    : - const_obj: constants object used in the entire
           * application */
          /*          - bit_mask: mask of the specific bit to modify in the
           * register */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function read_interface() */
          /*  Goal  : Define the interface layer reading data from external HW
           * registers */
          /*  IN    : - register_address: address of the register in unsigned 16
           * bit */
          /*  IN/OUT: - */
          /*  OUT   : - register_value: value stored in the register as an
           * unsigned 8 bit */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          a = read_register(40963);
          /*  Set the selected bit to '1' and write the new value to the
           * register */
          register_value = (unsigned char)(a | 16);
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function write_interface() */
          /*  Goal  : Define the interface layer writing data to external HW
           * registers */
          /*  IN    : - register_address: address of the register in unsigned 16
           * bit */
          /*          - new_value: value to store in the register as an unsigned
           * 8 bit */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          write_register(40963, register_value);
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an
           * amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          Sleep(250);
          /*  Sleep asks milliseconds as input */
          /*  Reset the selected bit only and write the new value to the
           * register */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function write_interface() */
          /*  Goal  : Define the interface layer writing data to external HW
           * registers */
          /*  IN    : - register_address: address of the register in unsigned 16
           * bit */
          /*          - new_value: value to store in the register as an unsigned
           * 8 bit */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          write_register(40963, (unsigned char)(register_value ^ 16));
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an
           * amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          Sleep(250);
          /*  Sleep asks milliseconds as input */
          printf("%s\n\n", "---------------------------------------------------"
                           "----------------------------");
          fflush(stdout);
        } break;
        case 6: {
          int b_data;
          int i1;
          unsigned char b_register_value;
          /*  Text constants declaration  */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function coin_flap_position() */
          /*  Goal  : Test if the coin's flap can be opened and closed */
          /*  IN    : - const_obj: object containing all needed constants */
          /*          - f_api    : functions handler struct listing functions to
           * access */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration  */
          /*  Split sections  */
          printf("%s\n", "-----------------------------------------------------"
                         "--------------------------");
          fflush(stdout);
          /*  Get and check the flap position provided at the console interface
           */
          /*  Function that is not translated into C code */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function check_get_data() */
          /*  Goal  : Test the write access function to any shared memory
           * register */
          /*  IN    : - promp_text: pointer to a chain char to display in the
           * console */
          /*          - min_data  : minimum value that is allowed in the range
           * of data */
          /*          - max_data  : maximum value that is allowed in the range
           * of data */
          /*  IN/OUT: - */
          /*  OUT   : - integer value to get from the console interface */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration */
          b_data = 0;
          /*  Get and check the data from the console */
          do {
            exitg2 = 0;
            char *d_format;
            int d_nb_input_types;
            char d_terminator;
            do {
              exitg3 = 0;
              /*  Get input data using the Windows C API */
              d_terminator = ' ';
              printf("%s", "Set the position of the coin\'s flap [open => "
                           "\'1\', close => \'0\']: ");
              fflush(stdout);
              /*  Force the string format definition in the generated C code for
               * scanf_s */
              d_format = "%d%c";
              d_nb_input_types = scanf_s(d_format, &b_data, &d_terminator, 1);
              /*  Check if the provided data is an integer number */
              if ((d_nb_input_types == 2) && (d_terminator == '\n')) {
                exitg3 = 1;
              } else {
                char *d_CLEAR_STDIN;
                printf("The value provided is not of the right data type!\n");
                fflush(stdout);
                /*  Force the string regular expression in the generated C code
                 * for scanf_s */
                d_CLEAR_STDIN = "%*[^\n]%*1[\n]";
                /*  Clear the input buffer */
                scanf_s(d_CLEAR_STDIN);
              }
            } while (exitg3 == 0);
            /*  Check if the value is within the allowed range */
            if ((b_data >= 0) && (b_data <= 1)) {
              exitg2 = 1;
            } else {
              printf("The value provided must be between %d and %d!\n", 0, 1);
              fflush(stdout);
            }
          } while (exitg2 == 0);
          /*  Update the position of the flap  */
          /*  Get the current peripherals register status */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function set_coin_flap_position() */
          /*  Goal  : Open or close the coin's flap */
          /*  IN    : - const_obj: constants object used in the entire
           * application */
          /*          - flap_open: '1' => coin flap to open */
          /*                       '0' => coin flap to close */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function read_interface() */
          /*  Goal  : Define the interface layer reading data from external HW
           * registers */
          /*  IN    : - register_address: address of the register in unsigned 16
           * bit */
          /*  IN/OUT: - */
          /*  OUT   : - register_value: value stored in the register as an
           * unsigned 8 bit */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          b_register_value = read_register(40963);
          /*  Set the corresponding bit of the register depending on flap_open
           */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function write_interface() */
          /*  Goal  : Define the interface layer writing data to external HW
           * registers */
          /*  IN    : - register_address: address of the register in unsigned 16
           * bit */
          /*          - new_value: value to store in the register as an unsigned
           * 8 bit */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          if (b_data != 0) {
            i1 = b_register_value | 128;
          } else {
            i1 = b_register_value & 127;
          }
          write_register(40963, (unsigned char)i1);
        } break;
        case 7: {
          int b;
          int i;
          /*  Include the header file containing the needed functions
           * declarations */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function input_registers() */
          /*  Goal  : Read for a desired time the current status of the input
           * registers */
          /*  IN    : - const_obj: object containing all needed constants */
          /*          - f_api    : functions handler struct listing functions to
           * access */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Text constants declaration  */
          /*  Split sections  */
          printf("%s\n", "-----------------------------------------------------"
                         "--------------------------");
          fflush(stdout);
          /*  Get and check the time limit provided at the console interface  */
          /*  Function that is not translated into C code */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Function check_get_data() */
          /*  Goal  : Test the write access function to any shared memory
           * register */
          /*  IN    : - promp_text: pointer to a chain char to display in the
           * console */
          /*          - min_data  : minimum value that is allowed in the range
           * of data */
          /*          - max_data  : maximum value that is allowed in the range
           * of data */
          /*  IN/OUT: - */
          /*  OUT   : - integer value to get from the console interface */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           */
          /*  Variables declaration */
          b = 0;
          /*  Get and check the data from the console */
          do {
            exitg2 = 0;
            char *e_format;
            int e_nb_input_types;
            char e_terminator;
            do {
              exitg3 = 0;
              /*  Get input data using the Windows C API */
              e_terminator = ' ';
              printf("%s", "Enter the desired time to read the inputregisters "
                           "in seconds [\'1\'-\'100\']: ");
              fflush(stdout);
              /*  Force the string format definition in the generated C code for
               * scanf_s */
              e_format = "%d%c";
              e_nb_input_types = scanf_s(e_format, &b, &e_terminator, 1);
              /*  Check if the provided data is an integer number */
              if ((e_nb_input_types == 2) && (e_terminator == '\n')) {
                exitg3 = 1;
              } else {
                char *e_CLEAR_STDIN;
                printf("The value provided is not of the right data type!\n");
                fflush(stdout);
                /*  Force the string regular expression in the generated C code
                 * for scanf_s */
                e_CLEAR_STDIN = "%*[^\n]%*1[\n]";
                /*  Clear the input buffer */
                scanf_s(e_CLEAR_STDIN);
              }
            } while (exitg3 == 0);
            /*  Check if the value is within the allowed range */
            if ((b >= 1) && (b <= 100)) {
              exitg2 = 1;
            } else {
              printf("The value provided must be between %d and %d!\n", 1, 100);
              fflush(stdout);
            }
          } while (exitg2 == 0);
          /*  Read the input registers continuously  */
          i = 10 * b;
          for (b_i = 0; b_i <= i; b_i++) {
            unsigned char validatedHoleFilling_idx_0;
            printf("%s\n", "---------------------------------------------------"
                           "----------------------------");
            fflush(stdout);
            /*  Split measurements  */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            validatedHoleFilling_idx_0 = read_register(40978);
            printf("Available coins: %x\n", validatedHoleFilling_idx_0);
            fflush(stdout);
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            validatedHoleFilling_idx_0 = read_register(40977);
            printf("Inserted coins : %x\n", validatedHoleFilling_idx_0);
            fflush(stdout);
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW
             * registers */
            /*  IN    : - register_address: address of the register in unsigned
             * 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an
             * unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            validatedHoleFilling_idx_0 = read_register(40976);
            printf("Pushed buttons : %x\n", validatedHoleFilling_idx_0);
            fflush(stdout);
            printf("Elapsed time   : %3.1f\n",
                   (float)rt_roundd(((double)b_i + 1.0) * 100.0 / 1000.0));
            fflush(stdout);
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            /*  Function sleep_interface() */
            /*  Goal  : Define the interface layer to pause the system for an
             * amount of time */
            /*  IN    : - duration: time duration in seconds */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             */
            Sleep(100);
            /*  Sleep asks milliseconds as input */
          }
          /*  Split sections  */
          printf("%s\n\n", "---------------------------------------------------"
                           "----------------------------");
          fflush(stdout);
        } break;
        default:
          printf("%s\n", "The normal mode of operation of the parking meter "
                         "has been activated.");
          fflush(stdout);
          standard_operation_mode();
          break;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void parkingMeterLowLevel_initialize(void)
{
  TEST_MODE = 1;
  isInitialized_parkingMeterLowLevel = true;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void parkingMeterLowLevel_terminate(void)
{
  isInitialized_parkingMeterLowLevel = false;
}

/*
 * File trailer for parkingMeterLowLevel.c
 *
 * [EOF]
 */
