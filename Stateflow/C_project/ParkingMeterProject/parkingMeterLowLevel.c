/*
 * File: parkingMeterLowLevel.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 14-Oct-2019 19:10:03
 */

/* Include Files */
#include "parkingMeterLowLevel.h"
#include "ParkingMeterMemory.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Type Definitions */
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

#endif                                 /*typedef_StateMachineParameters*/

#ifndef typedef_cell_1
#define typedef_cell_1

typedef struct {
  char f1[15];
  char f2[3];
} cell_1;

#endif                                 /*typedef_cell_1*/

#ifndef typedef_cell_2
#define typedef_cell_2

typedef struct {
  char f1[15];
  char f2[3];
  char f3[21];
  char f4[16];
  char f5[10];
} cell_2;

#endif                                 /*typedef_cell_2*/

#ifndef typedef_cell_3
#define typedef_cell_3

typedef struct {
  char f1[21];
  char f2[16];
  char f3[10];
} cell_3;

#endif                                 /*typedef_cell_3*/

#ifndef typedef_struct_T
#define typedef_struct_T

typedef struct {
  cell_1 chartLocalData;
  double ctorUserChoices[7];
  cell_2 chartAllData;
  double chartAllDataSSID[5];
  cell_3 chartConstantData;
  double stepCount;
  bool enableDataLogging;
  double clockSpeedUp;
  bool enableAnimation;
  double animationDelay;
  bool externalClock;
  bool executionTimeForTimers;
  bool useMATLABTimerForSFTemporals;
  bool executeAtInitialization;
} struct_T;

#endif                                 /*typedef_struct_T*/

#ifndef typedef_Scheduler
#define typedef_Scheduler

typedef struct {
  double REFRESHING_TICK;
  StateMachineParameters obj;
  double Scheduler_activeChild_SFX_16;
  double c_PURCHASE_TICKET_activeChild_S;
  bool Scheduler_isActive_SFX_105;
  struct_T sfInternalObj;
  double Counter_UPDATE_AMOUNT_SFX_176;
} Scheduler;

#endif                                 /*typedef_Scheduler*/

/* Variable Definitions */
int TEST_MODE;
static boolean_T isInitialized_parkingMeterLowLevel = false;

/* Function Declarations */
static void TestMode_display_value(void);
static void TestMode_give_back_coin(void);
static void TestMode_write_register(void);
static void b_display_digit(unsigned char display_ID, int digit_value, double
  dot_segment);
static void c_Scheduler_Scheduler_during_SF(Scheduler *this);
static void c_Scheduler_Scheduler_exitInter(Scheduler *this);
static void display_digit(unsigned char display_ID, unsigned short digit_value,
  double dot_segment);
static int div_nde_s32_floor(int numerator, int denominator);
static void give_back_coin(unsigned short amount);
static void return_coins(unsigned short desired_amount);
static double rt_roundd(double u);
static void standard_operation_mode(void);
static void test_mode(void);

/* Function Definitions */

/*
 * Text constants declaration
 * Arguments    : void
 * Return Type  : void
 */
static void TestMode_display_value(void)
{
  int data;
  int exitg1;
  char terminator;
  char * format;
  int nb_input_types;
  bool guard1 = false;
  bool b_bool;
  char * CLEAR_STDIN;
  int digit_value;
  int b_remainder;
  int x;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function display_value() */
  /*  Goal  : Test the 7 segments displays by displaying any value on them */
  /*  IN    : - const_obj: object containing all needed constants */
  /*          - f_api    : functions handler struct listing functions to access */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Variables declaration  */
  /*  Split sections  */
  printf("%s\n",
         "-------------------------------------------------------------------------------");
  fflush(stdout);

  /*  Get the data to write in the register  */
  /*  Function that is not translated into C code */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Class TestMode */
  /*  Goal  : This subclass contains all the global constants needed for the test */
  /*          mode of the Parking Meter Low Level program. */
  /*          Once an object has been created out of the superclass, it must then be */
  /*          passed has an input argument to all the functions of the application. */
  /*  */
  /*  Author: Sebastien Dupertuis */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  The following constants will be added to the superclass "Constants" */
  /*  Char separator to split sections */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function check_get_data() */
  /*  Goal  : Test the write access function to any shared memory register */
  /*  IN    : - promp_text: pointer to a chain char to display in the console */
  /*          - min_data  : minimum value that is allowed in the range of data */
  /*          - max_data  : maximum value that is allowed in the range of data */
  /*  IN/OUT: - */
  /*  OUT   : - integer value to get from the console interface */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Variables declaration */
  data = 0;

  /*  Get and check the data from the console */
  do {
    exitg1 = 0;

    /*  Get input data using the Windows C API */
    terminator = ' ';
    printf("%s",
           "Enter the hundreds of cents value to print on the 7 segments displays: ");
    fflush(stdout);

    /*  Force the string format definition in the generated C code for scanf_s */
    format = "%d%c";
    nb_input_types = scanf_s(format, &data, &terminator, 1);

    /*  Check if the provided data is an integer number */
    guard1 = false;
    if (nb_input_types == 2) {
      b_bool = !(terminator != '\x0a');
      if (b_bool) {
        /*  Check if the value is within the allowed range */
        if ((data >= 0) && (data <= 999)) {
          exitg1 = 1;
        } else {
          printf("The value provided must be between %d and %d!\n", 0, 999);
          fflush(stdout);
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      printf("The value provided is not of the right data type!\n");
      fflush(stdout);

      /*  Force the string regular expression in the generated C code for scanf_s */
      CLEAR_STDIN = "%*[^\n]%*1[\n]";

      /*  Clear the input buffer */
      scanf_s(CLEAR_STDIN);
    }
  } while (exitg1 == 0);

  /*  Write the user's data to the 7 segments displays  */
  /*  Initialization value of the parking meter display */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function display_cents_value() */
  /*  Goal  : Update the new parking meter cents value */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - cents_value: base 10 value to display on all 7 segments displays */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  if (data == 45) {
    display_digit(1U, 45U, 0.0);
    display_digit(2U, 45U, 0.0);
    display_digit(3U, 45U, 0.0);

    /*  Compute the right value to display on the parking meter */
  } else if ((data >= 0) && (data <= 999)) {
    /*  Compute the cent */
    digit_value = data - div_nde_s32_floor(data, 10) * 10;
    b_display_digit(1U, digit_value, 0.0);

    /*  Compute the tens of cents */
    b_remainder = (int)rt_roundd((double)(data - digit_value) / 10.0);
    digit_value = b_remainder - div_nde_s32_floor(b_remainder, 10) * 10;
    b_display_digit(2U, digit_value, 0.0);

    /*  Compute the hundreds of cents */
    x = (int)rt_roundd((double)(b_remainder - digit_value) / 10.0);
    b_display_digit(3U, x - div_nde_s32_floor(x, 10) * 10, 1.0);
  } else {
    printf("Incorrect cents value provided to the parking meter display!\n");
    fflush(stdout);
  }

  printf("%s\n\n",
         "The desired value has been successfully written on the 7 segments displays.");
  fflush(stdout);
  printf("%s\n",
         "-------------------------------------------------------------------------------");
  fflush(stdout);
}

/*
 * Text constants declaration
 * Arguments    : void
 * Return Type  : void
 */
static void TestMode_give_back_coin(void)
{
  int coin_choice;
  int exitg1;
  int exitg2;
  char terminator;
  char * format;
  int nb_input_types;
  bool guard1 = false;
  bool b_bool;
  char * CLEAR_STDIN;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function give_back_coin() */
  /*  Goal  : Test if coins are given back correctly or not */
  /*  IN    : - const_obj: object containing all needed constants */
  /*          - f_api    : functions handler struct listing functions to access */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Variables declaration  */
  coin_choice = 1;

  /*  Split sections  */
  printf("%s\n",
         "-------------------------------------------------------------------------------");
  fflush(stdout);

  /*  Loop over the menu entries */
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
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Class TestMode */
      /*  Goal  : This subclass contains all the global constants needed for the test */
      /*          mode of the Parking Meter Low Level program. */
      /*          Once an object has been created out of the superclass, it must then be */
      /*          passed has an input argument to all the functions of the application. */
      /*  */
      /*  Author: Sebastien Dupertuis */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  The following constants will be added to the superclass "Constants" */
      /*  Char separator to split sections */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Function check_get_data() */
      /*  Goal  : Test the write access function to any shared memory register */
      /*  IN    : - promp_text: pointer to a chain char to display in the console */
      /*          - min_data  : minimum value that is allowed in the range of data */
      /*          - max_data  : maximum value that is allowed in the range of data */
      /*  IN/OUT: - */
      /*  OUT   : - integer value to get from the console interface */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Variables declaration */
      coin_choice = 0;

      /*  Get and check the data from the console */
      do {
        exitg2 = 0;

        /*  Get input data using the Windows C API */
        terminator = ' ';
        printf("%s",
               "Enter the menu entry corresponding to the coins value to give back [0-4]: ");
        fflush(stdout);

        /*  Force the string format definition in the generated C code for scanf_s */
        format = "%d%c";
        nb_input_types = scanf_s(format, &coin_choice, &terminator, 1);

        /*  Check if the provided data is an integer number */
        guard1 = false;
        if (nb_input_types == 2) {
          b_bool = !(terminator != '\x0a');
          if (b_bool) {
            /*  Check if the value is within the allowed range */
            if ((coin_choice >= 0) && (coin_choice <= 4)) {
              exitg2 = 1;
            } else {
              printf("The value provided must be between %d and %d!\n", 0, 4);
              fflush(stdout);
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          printf("The value provided is not of the right data type!\n");
          fflush(stdout);

          /*  Force the string regular expression in the generated C code for scanf_s */
          CLEAR_STDIN = "%*[^\n]%*1[\n]";

          /*  Clear the input buffer */
          scanf_s(CLEAR_STDIN);
        }
      } while (exitg2 == 0);

      /*  Select the specific coin's value to give back  */
      switch (coin_choice) {
       case 0:
        /*  Split sections */
        printf("%s\n\n",
               "-------------------------------------------------------------------------------");
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

       case 4:
        give_back_coin(100U);
        break;

       default:
        printf("Incorrect menu selection. Please enter a value between 0 and 4.\n");
        fflush(stdout);
        exitg1 = 1;
        break;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * Function that is not translated into C code
 * Arguments    : void
 * Return Type  : void
 */
static void TestMode_write_register(void)
{
  bool is_right_value;
  int exitg1;
  char * format;
  int register_text;
  int i;
  bool exitg2;
  static const unsigned short uv[7] = { 40960U, 40961U, 40962U, 40963U, 40976U,
    40977U, 40978U };

  char * CLEAR_STDIN;
  int data;
  char terminator;
  char * b_format;
  int nb_input_types;
  bool guard1 = false;
  bool b_bool;
  char * b_CLEAR_STDIN;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function write_register() */
  /*  Goal  : Test the write access function to any shared memory register */
  /*  IN    : - const_obj: object containing all needed constants */
  /*          - f_api    : functions handler struct listing functions to access */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Text constants declaration */
  /*  Variables declaration */
  is_right_value = false;

  /*  Split sections  */
  printf("%s\n",
         "-------------------------------------------------------------------------------");
  fflush(stdout);

  /*  Get the address of the register to access  */
  do {
    exitg1 = 0;
    printf("%s",
           "Enter the address of the register to access in hexadecimal within the following range [0xA000-0xA003] or [0xA010-0xA012]: ");
    fflush(stdout);

    /*  Force the string format definition in the generated C code for scanf_s */
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
      printf("The address provided is not within the right range of addresses!\n");
      fflush(stdout);

      /*  Force the string regular expression in the generated C code for scanf_s */
      CLEAR_STDIN = "%*[^\n]%*1[\n]";

      /*  Clear the input buffer */
      scanf_s(CLEAR_STDIN);
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  /*  Get the data to write in the register  */
  /*  Function that is not translated into C code */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Class TestMode */
  /*  Goal  : This subclass contains all the global constants needed for the test */
  /*          mode of the Parking Meter Low Level program. */
  /*          Once an object has been created out of the superclass, it must then be */
  /*          passed has an input argument to all the functions of the application. */
  /*  */
  /*  Author: Sebastien Dupertuis */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  The following constants will be added to the superclass "Constants" */
  /*  Char separator to split sections */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function check_get_data() */
  /*  Goal  : Test the write access function to any shared memory register */
  /*  IN    : - promp_text: pointer to a chain char to display in the console */
  /*          - min_data  : minimum value that is allowed in the range of data */
  /*          - max_data  : maximum value that is allowed in the range of data */
  /*  IN/OUT: - */
  /*  OUT   : - integer value to get from the console interface */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Variables declaration */
  data = 0;

  /*  Get and check the data from the console */
  do {
    exitg1 = 0;

    /*  Get input data using the Windows C API */
    terminator = ' ';
    printf("%s", "Enter the integer data to write at the selected register: ");
    fflush(stdout);

    /*  Force the string format definition in the generated C code for scanf_s */
    b_format = "%d%c";
    nb_input_types = scanf_s(b_format, &data, &terminator, 1);

    /*  Check if the provided data is an integer number */
    guard1 = false;
    if (nb_input_types == 2) {
      b_bool = !(terminator != '\x0a');
      if (b_bool) {
        /*  Check if the value is within the allowed range */
        if ((data >= 0) && (data <= 999)) {
          exitg1 = 1;
        } else {
          printf("The value provided must be between %d and %d!\n", 0, 999);
          fflush(stdout);
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      printf("The value provided is not of the right data type!\n");
      fflush(stdout);

      /*  Force the string regular expression in the generated C code for scanf_s */
      b_CLEAR_STDIN = "%*[^\n]%*1[\n]";

      /*  Clear the input buffer */
      scanf_s(b_CLEAR_STDIN);
    }
  } while (exitg1 == 0);

  /*  Write the user's data to the selected register  */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function write_interface() */
  /*  Goal  : Define the interface layer writing data to external HW registers */
  /*  IN    : - register_address: address of the register in unsigned 16 bit */
  /*          - new_value: value to store in the register as an unsigned 8 bit */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  write_register((unsigned short)register_text, data);
  printf("%s\n\n",
         "The desired value has been successfully written in the selected register.");
  fflush(stdout);
  printf("%s\n",
         "-------------------------------------------------------------------------------");
  fflush(stdout);
}

/*
 * New 7 segments encoded value to write in the corresponding HW register
 *  Assignment of the new digit value to display
 * Arguments    : unsigned char display_ID
 *                int digit_value
 *                double dot_segment
 * Return Type  : void
 */
static void b_display_digit(unsigned char display_ID, int digit_value, double
  dot_segment)
{
  unsigned char new_reg_value;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function display_digit() */
  /*  Goal  : Update a 7 segments display with a new digit value */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - display_ID : identification number of the 7 segments display */
  /*          - digit_value: base 10 value to display on the 7 segments display */
  /*          - dot_segment: enable the dot segment => '1' */
  /*                         do not enable the dot segment => '0' */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
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
   case 1:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40960, new_reg_value);
    break;

   case 2:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40961, new_reg_value);
    break;

   default:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40962, new_reg_value);
    break;
  }
}

/*
 * Arguments    : Scheduler *this
 * Return Type  : void
 */
static void c_Scheduler_Scheduler_during_SF(Scheduler *this)
{
  /*     <a href="matlab:sfhelp('sf4ml')">Stateflow Documentation Link</a> */
  /*     <a href="matlab:edit Scheduler.sfx">edit Scheduler.sfx</a> opens Stateflow Chart */
  /*     <strong>SchedulerObject = Scheduler(Name, Value)</strong> constructs Stateflow chart object */
  /*     with optional name-value pair arguments  to initialize chart data.  */
  /*     e.g. SchedulerObject = Scheduler() default constructor */
  /*          SchedulerObject = Scheduler('REFRESHING_TICK',0, 'obj',0) constructor with initialization of chart data 'REFRESHING_TICK' and 'obj' */
  /*     <strong>step(SchedulerObject, Name, Value)</strong> executes Stateflow chart object */
  /*     with optional name-value pair arguments to set data values. */
  /*  This file is automatically generated by Stateflow. */
  /* __SFX_CLASS_START__ */
  /* Scheduler */
  switch ((int)this->Scheduler_activeChild_SFX_16) {
   case 1:
    /* For State: CHECK_COINS */
    c_Scheduler_Scheduler_exitInter(this);
    this->Scheduler_activeChild_SFX_16 = 13.0;

    /* State PURCHASE_TICKET becomes active */
    /*  Waiting for the full paiment or the cancellation of the ticket */
    this->c_PURCHASE_TICKET_activeChild_S = 46.0;

    /* State INITIALIZATION becomes active */
    /*  Reset needed variables */
    this->obj.inserted_amount = 0U;

    /* #__SFDEBUGSTART__#46#0#47#79#0#4#__SFDEBUGEND__ */
    break;

   case 3:
    /* For State: INITIALIZATION */
    c_Scheduler_Scheduler_exitInter(this);
    this->Scheduler_activeChild_SFX_16 = 2.0;

    /* State PURCHASE_CHECK becomes active */
    break;

   case 2:
    /* For State: PURCHASE_CHECK */
    if (!this->obj.master_switch) {
      /* #__SFDEBUGSTART__#28#0#1#26#0#2#__SFDEBUGEND__ */
      c_Scheduler_Scheduler_exitInter(this);
      this->Scheduler_activeChild_SFX_16 = 4.0;

      /* State STOP_EXECUTION becomes active */
      /*  Stop the model execution */
      this->obj.ISR[6] = true;

      /*  Trigger the terminate function to stop the execution%#__SFDEBUGSTART__#4#0#49#122#0#4#__SFDEBUGEND__ */
    } else if (this->obj.green_pressed) {
      /* #__SFDEBUGSTART__#53#0#1#25#0#2#__SFDEBUGEND__ */
      c_Scheduler_Scheduler_exitInter(this);
      this->Scheduler_activeChild_SFX_16 = 1.0;

      /* State CHECK_COINS becomes active */
      /*  Update of the button value state once it has been pressed */
      this->obj.display_value = 120U;

      /* #__SFDEBUGSTART__#1#0#80#111#0#4#__SFDEBUGEND__ */
      this->obj.flap_open = true;

      /* #__SFDEBUGSTART__#1#0#113#134#0#4#__SFDEBUGEND__ */
      /*  Send interrupts */
      this->obj.ISR[0] = true;

      /*  Display the cost of a parking ticket%#__SFDEBUGSTART__#1#0#155#212#0#4#__SFDEBUGEND__ */
      this->obj.ISR[1] = true;

      /*  Open the coin's flap%#__SFDEBUGSTART__#1#0#214#255#0#4#__SFDEBUGEND__ */
    } else {
      /*  Waiting on a ticket purchase request */
      this->obj.ISR[2] = true;

      /*  Leds: check if the parking meter can give money back%#__SFDEBUGSTART__#2#0#62#135#0#5#__SFDEBUGEND__ */
      this->obj.ISR[4] = true;

      /*  Check the status of the green button and master switch%#__SFDEBUGSTART__#2#0#137#212#0#5#__SFDEBUGEND__ */
    }
    break;

   case 13:
    /* For State: PURCHASE_TICKET */
    /*  Waiting for the full paiment or the cancellation of the ticket */
    switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
     case 35:
      /* For State: CANCEL_CHECK */
      if (this->obj.red_pressed) {
        /* #__SFDEBUGSTART__#34#0#1#23#0#2#__SFDEBUGEND__ */
        switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
         case 35:
          /* For State: CANCEL_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_CHECK becomes inactive */
          break;

         case 21:
          /* For State: CANCEL_PURCHASE */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_PURCHASE becomes inactive */
          break;

         case 40:
          /* For State: COIN_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State COIN_CHECK becomes inactive */
          break;

         case 46:
          /* For State: INITIALIZATION */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State INITIALIZATION becomes inactive */
          break;

         case 33:
          /* For State: PRINT_RECEIPT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State PRINT_RECEIPT becomes inactive */
          break;

         case 22:
          /* For State: UPDATE_AMOUNT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State UPDATE_AMOUNT becomes inactive */
          break;
        }

        this->c_PURCHASE_TICKET_activeChild_S = 21.0;

        /* State CANCEL_PURCHASE becomes active */
        /*  Ticket's purchase process cancelled */
        this->obj.amount_to_return = this->obj.inserted_amount;

        /* #__SFDEBUGSTART__#21#0#61#104#0#4#__SFDEBUGEND__ */
        this->obj.ISR[3] = true;

        /*  End of the purchase process%#__SFDEBUGSTART__#21#0#106#154#0#4#__SFDEBUGEND__ */
      } else {
        switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
         case 35:
          /* For State: CANCEL_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_CHECK becomes inactive */
          break;

         case 21:
          /* For State: CANCEL_PURCHASE */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_PURCHASE becomes inactive */
          break;

         case 40:
          /* For State: COIN_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State COIN_CHECK becomes inactive */
          break;

         case 46:
          /* For State: INITIALIZATION */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State INITIALIZATION becomes inactive */
          break;

         case 33:
          /* For State: PRINT_RECEIPT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State PRINT_RECEIPT becomes inactive */
          break;

         case 22:
          /* For State: UPDATE_AMOUNT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State UPDATE_AMOUNT becomes inactive */
          break;
        }

        this->c_PURCHASE_TICKET_activeChild_S = 40.0;

        /* State COIN_CHECK becomes active */
        /*  Update the amount to pay if a coin has been inserted */
        this->obj.ISR[5] = true;

        /*  Check current inserted coin%#__SFDEBUGSTART__#40#0#73#121#0#4#__SFDEBUGEND__ */
      }
      break;

     case 21:
      /* For State: CANCEL_PURCHASE */
      c_Scheduler_Scheduler_exitInter(this);
      this->Scheduler_activeChild_SFX_16 = 3.0;

      /* State INITIALIZATION becomes active */
      /*  Reset of the parking meter status */
      this->obj.display_value = 45U;

      /* #__SFDEBUGSTART__#3#0#58#111#0#4#__SFDEBUGEND__ */
      this->obj.flap_open = false;

      /* #__SFDEBUGSTART__#3#0#113#135#0#4#__SFDEBUGEND__ */
      this->obj.ISR[0] = true;

      /*  Initial state of the 7 segments displays%#__SFDEBUGSTART__#3#0#137#198#0#4#__SFDEBUGEND__ */
      this->obj.ISR[1] = true;

      /*  Close the coin's flap%#__SFDEBUGSTART__#3#0#200#242#0#4#__SFDEBUGEND__ */
      break;

     case 40:
      /* For State: COIN_CHECK */
      if (this->obj.coins_reg_value != this->obj.register_value) {
        /* #__SFDEBUGSTART__#23#0#1#41#0#2#__SFDEBUGEND__ */
        switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
         case 35:
          /* For State: CANCEL_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_CHECK becomes inactive */
          break;

         case 21:
          /* For State: CANCEL_PURCHASE */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_PURCHASE becomes inactive */
          break;

         case 40:
          /* For State: COIN_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State COIN_CHECK becomes inactive */
          break;

         case 46:
          /* For State: INITIALIZATION */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State INITIALIZATION becomes inactive */
          break;

         case 33:
          /* For State: PRINT_RECEIPT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State PRINT_RECEIPT becomes inactive */
          break;

         case 22:
          /* For State: UPDATE_AMOUNT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State UPDATE_AMOUNT becomes inactive */
          break;
        }

        this->Counter_UPDATE_AMOUNT_SFX_176 = 0.0;
        this->c_PURCHASE_TICKET_activeChild_S = 22.0;

        /* State UPDATE_AMOUNT becomes active */
      } else {
        switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
         case 35:
          /* For State: CANCEL_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_CHECK becomes inactive */
          break;

         case 21:
          /* For State: CANCEL_PURCHASE */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_PURCHASE becomes inactive */
          break;

         case 40:
          /* For State: COIN_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State COIN_CHECK becomes inactive */
          break;

         case 46:
          /* For State: INITIALIZATION */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State INITIALIZATION becomes inactive */
          break;

         case 33:
          /* For State: PRINT_RECEIPT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State PRINT_RECEIPT becomes inactive */
          break;

         case 22:
          /* For State: UPDATE_AMOUNT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State UPDATE_AMOUNT becomes inactive */
          break;
        }

        this->c_PURCHASE_TICKET_activeChild_S = 35.0;

        /* State CANCEL_CHECK becomes active */
        /*  Check if the purchase is being cancelled */
        this->obj.ISR[4] = true;

        /*  Check status of the red button%#__SFDEBUGSTART__#35#0#63#114#0#4#__SFDEBUGEND__ */
      }
      break;

     case 46:
      /* For State: INITIALIZATION */
      switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
       case 35:
        /* For State: CANCEL_CHECK */
        this->c_PURCHASE_TICKET_activeChild_S = 0.0;

        /* State CANCEL_CHECK becomes inactive */
        break;

       case 21:
        /* For State: CANCEL_PURCHASE */
        this->c_PURCHASE_TICKET_activeChild_S = 0.0;

        /* State CANCEL_PURCHASE becomes inactive */
        break;

       case 40:
        /* For State: COIN_CHECK */
        this->c_PURCHASE_TICKET_activeChild_S = 0.0;

        /* State COIN_CHECK becomes inactive */
        break;

       case 46:
        /* For State: INITIALIZATION */
        this->c_PURCHASE_TICKET_activeChild_S = 0.0;

        /* State INITIALIZATION becomes inactive */
        break;

       case 33:
        /* For State: PRINT_RECEIPT */
        this->c_PURCHASE_TICKET_activeChild_S = 0.0;

        /* State PRINT_RECEIPT becomes inactive */
        break;

       case 22:
        /* For State: UPDATE_AMOUNT */
        this->c_PURCHASE_TICKET_activeChild_S = 0.0;

        /* State UPDATE_AMOUNT becomes inactive */
        break;
      }

      this->c_PURCHASE_TICKET_activeChild_S = 35.0;

      /* State CANCEL_CHECK becomes active */
      /*  Check if the purchase is being cancelled */
      this->obj.ISR[4] = true;

      /*  Check status of the red button%#__SFDEBUGSTART__#35#0#63#114#0#4#__SFDEBUGEND__ */
      break;

     case 33:
      /* For State: PRINT_RECEIPT */
      c_Scheduler_Scheduler_exitInter(this);
      this->Scheduler_activeChild_SFX_16 = 3.0;

      /* State INITIALIZATION becomes active */
      /*  Reset of the parking meter status */
      this->obj.display_value = 45U;

      /* #__SFDEBUGSTART__#3#0#58#111#0#4#__SFDEBUGEND__ */
      this->obj.flap_open = false;

      /* #__SFDEBUGSTART__#3#0#113#135#0#4#__SFDEBUGEND__ */
      this->obj.ISR[0] = true;

      /*  Initial state of the 7 segments displays%#__SFDEBUGSTART__#3#0#137#198#0#4#__SFDEBUGEND__ */
      this->obj.ISR[1] = true;

      /*  Close the coin's flap%#__SFDEBUGSTART__#3#0#200#242#0#4#__SFDEBUGEND__ */
      break;

     case 22:
      /* For State: UPDATE_AMOUNT */
      this->Counter_UPDATE_AMOUNT_SFX_176++;
      if (this->Counter_UPDATE_AMOUNT_SFX_176 >= this->REFRESHING_TICK) {
        /* #__SFDEBUGSTART__#20#0#0#27#0#1#__SFDEBUGEND__ */
        switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
         case 35:
          /* For State: CANCEL_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_CHECK becomes inactive */
          break;

         case 21:
          /* For State: CANCEL_PURCHASE */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_PURCHASE becomes inactive */
          break;

         case 40:
          /* For State: COIN_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State COIN_CHECK becomes inactive */
          break;

         case 46:
          /* For State: INITIALIZATION */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State INITIALIZATION becomes inactive */
          break;

         case 33:
          /* For State: PRINT_RECEIPT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State PRINT_RECEIPT becomes inactive */
          break;

         case 22:
          /* For State: UPDATE_AMOUNT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State UPDATE_AMOUNT becomes inactive */
          break;
        }

        this->c_PURCHASE_TICKET_activeChild_S = 35.0;

        /* State CANCEL_CHECK becomes active */
        /*  Check if the purchase is being cancelled */
        this->obj.ISR[4] = true;

        /*  Check status of the red button%#__SFDEBUGSTART__#35#0#63#114#0#4#__SFDEBUGEND__ */
      } else if (this->obj.inserted_amount >= 120) {
        /* #__SFDEBUGSTART__#31#0#1#33#0#2#__SFDEBUGEND__ */
        switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
         case 35:
          /* For State: CANCEL_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_CHECK becomes inactive */
          break;

         case 21:
          /* For State: CANCEL_PURCHASE */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State CANCEL_PURCHASE becomes inactive */
          break;

         case 40:
          /* For State: COIN_CHECK */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State COIN_CHECK becomes inactive */
          break;

         case 46:
          /* For State: INITIALIZATION */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State INITIALIZATION becomes inactive */
          break;

         case 33:
          /* For State: PRINT_RECEIPT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State PRINT_RECEIPT becomes inactive */
          break;

         case 22:
          /* For State: UPDATE_AMOUNT */
          this->c_PURCHASE_TICKET_activeChild_S = 0.0;

          /* State UPDATE_AMOUNT becomes inactive */
          break;
        }

        this->c_PURCHASE_TICKET_activeChild_S = 33.0;

        /* State PRINT_RECEIPT becomes active */
        /*  Printing of the parking ticket and give back coin's change */
        /* #__SFDEBUGSTART__#33#0#82#123#0#4#__SFDEBUGEND__ */
        this->obj.amount_to_return = (unsigned short)(this->obj.inserted_amount
          - 120U);

        /* #__SFDEBUGSTART__#33#0#125#179#0#4#__SFDEBUGEND__ */
        this->obj.ISR[3] = true;

        /*  End of the purchase process%#__SFDEBUGSTART__#33#0#181#229#0#4#__SFDEBUGEND__ */
      } else {
        /*  Update the amount to pay if a coin has been inserted */
        this->obj.coins_reg_value = this->obj.register_value;

        /* #__SFDEBUGSTART__#22#0#77#118#0#5#__SFDEBUGEND__ */
        this->obj.display_value = (unsigned short)(120U -
          this->obj.inserted_amount);

        /* #__SFDEBUGSTART__#22#0#120#171#0#5#__SFDEBUGEND__ */
        this->obj.ISR[0] = true;

        /*  Update the remaining cents amount to pay%#__SFDEBUGSTART__#22#0#173#234#0#5#__SFDEBUGEND__ */
      }
      break;
    }
    break;

   case 4:
    /* For State: STOP_EXECUTION */
    break;
  }
}

/*
 * Arguments    : Scheduler *this
 * Return Type  : void
 */
static void c_Scheduler_Scheduler_exitInter(Scheduler *this)
{
  switch ((int)this->Scheduler_activeChild_SFX_16) {
   case 1:
    /* For State: CHECK_COINS */
    this->Scheduler_activeChild_SFX_16 = 0.0;

    /* State CHECK_COINS becomes inactive */
    break;

   case 3:
    /* For State: INITIALIZATION */
    this->Scheduler_activeChild_SFX_16 = 0.0;

    /* State INITIALIZATION becomes inactive */
    break;

   case 2:
    /* For State: PURCHASE_CHECK */
    this->Scheduler_activeChild_SFX_16 = 0.0;

    /* State PURCHASE_CHECK becomes inactive */
    break;

   case 13:
    /* For State: PURCHASE_TICKET */
    switch ((int)this->c_PURCHASE_TICKET_activeChild_S) {
     case 35:
      /* For State: CANCEL_CHECK */
      this->c_PURCHASE_TICKET_activeChild_S = 0.0;

      /* State CANCEL_CHECK becomes inactive */
      break;

     case 21:
      /* For State: CANCEL_PURCHASE */
      this->c_PURCHASE_TICKET_activeChild_S = 0.0;

      /* State CANCEL_PURCHASE becomes inactive */
      break;

     case 40:
      /* For State: COIN_CHECK */
      this->c_PURCHASE_TICKET_activeChild_S = 0.0;

      /* State COIN_CHECK becomes inactive */
      break;

     case 46:
      /* For State: INITIALIZATION */
      this->c_PURCHASE_TICKET_activeChild_S = 0.0;

      /* State INITIALIZATION becomes inactive */
      break;

     case 33:
      /* For State: PRINT_RECEIPT */
      this->c_PURCHASE_TICKET_activeChild_S = 0.0;

      /* State PRINT_RECEIPT becomes inactive */
      break;

     case 22:
      /* For State: UPDATE_AMOUNT */
      this->c_PURCHASE_TICKET_activeChild_S = 0.0;

      /* State UPDATE_AMOUNT becomes inactive */
      break;
    }

    this->Scheduler_activeChild_SFX_16 = 0.0;

    /* State PURCHASE_TICKET becomes inactive */
    break;

   case 4:
    /* For State: STOP_EXECUTION */
    this->Scheduler_activeChild_SFX_16 = 0.0;

    /* State STOP_EXECUTION becomes inactive */
    break;
  }
}

/*
 * New 7 segments encoded value to write in the corresponding HW register
 *  Assignment of the new digit value to display
 * Arguments    : unsigned char display_ID
 *                unsigned short digit_value
 *                double dot_segment
 * Return Type  : void
 */
static void display_digit(unsigned char display_ID, unsigned short digit_value,
  double dot_segment)
{
  unsigned char new_reg_value;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function display_digit() */
  /*  Goal  : Update a 7 segments display with a new digit value */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - display_ID : identification number of the 7 segments display */
  /*          - digit_value: base 10 value to display on the 7 segments display */
  /*          - dot_segment: enable the dot segment => '1' */
  /*                         do not enable the dot segment => '0' */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
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
   case 1:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40960, new_reg_value);
    break;

   case 2:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40961, new_reg_value);
    break;

   default:
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40962, new_reg_value);
    break;
  }
}

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_nde_s32_floor(int numerator, int denominator)
{
  int b_numerator;
  if (((numerator < 0) != (denominator < 0)) && (numerator % denominator != 0))
  {
    b_numerator = -1;
  } else {
    b_numerator = 0;
  }

  return numerator / denominator + b_numerator;
}

/*
 * Select the correct coin to give back
 * Arguments    : unsigned short amount
 * Return Type  : void
 */
static void give_back_coin(unsigned short amount)
{
  unsigned char a;
  unsigned char b_a;
  unsigned char c_a;
  unsigned char d_a;
  unsigned char register_value;
  unsigned char b_register_value;
  unsigned char c_register_value;
  unsigned char d_register_value;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function give_back_coin() */
  /*  Goal  : Return coins change to the user based on computed amount of money */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount: integer value corresponding to a specific coin */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  switch (amount) {
   case 10:
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    a = read_register(40963);

    /*  Set the selected bit to '1' and write the new value to the register */
    register_value = (unsigned char)(a | 1);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, register_value);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, (unsigned char)(register_value ^ 1));

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    break;

   case 20:
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    b_a = read_register(40963);

    /*  Set the selected bit to '1' and write the new value to the register */
    b_register_value = (unsigned char)(b_a | 2);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, b_register_value);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, (unsigned char)(b_register_value ^ 2));

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    break;

   case 50:
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    c_a = read_register(40963);

    /*  Set the selected bit to '1' and write the new value to the register */
    c_register_value = (unsigned char)(c_a | 4);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, c_register_value);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, (unsigned char)(c_register_value ^ 4));

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    break;

   case 100:
    /*  Read the current value stored in the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function generate_peripherals_pulse() */
    /*  Goal  : Every time an action is applied to the peripherals, the */
    /*          corresponding bit in the peripherals register is set or reset */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - bit_mask: mask of the specific bit to modify in the register */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    d_a = read_register(40963);

    /*  Set the selected bit to '1' and write the new value to the register */
    d_register_value = (unsigned char)(d_a | 8);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, d_register_value);

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    /*  Reset the selected bit only and write the new value to the register */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, (unsigned char)(d_register_value ^ 8));

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(100);

    /*  Sleep asks milliseconds as input */
    break;

   default:
    printf("Incorrect coin\'s value provided to the parking meter change module!\n");
    fflush(stdout);
    break;
  }
}

/*
 * Arguments    : unsigned short desired_amount
 * Return Type  : void
 */
static void return_coins(unsigned short desired_amount)
{
  unsigned short remaining_amount;
  bool exitg1;
  unsigned char register_value;
  unsigned short b_remaining_amount;
  unsigned char b_register_value;
  unsigned char c_register_value;
  unsigned char d_register_value;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function return_coins() */
  /*  Goal  : give back the desired amount of coins to the user */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - desired_amount: integer representing the money to give back */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Return as much as possible higher coin's values at first */
  remaining_amount = desired_amount;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function return_coin_value() */
  /*  Goal  : give back the remaining amount of coins to return */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount_to_return: integer representing the money to give back */
  /*          - coin_value : integer representing the value of the current coin */
  /*  IN/OUT: - */
  /*  OUT   : -  integer representing the remaining amount of coins to return */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Try to return as much coins as possible */
  exitg1 = false;
  while ((!exitg1) && (remaining_amount >= 100)) {
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function is_this_coin_available() */
    /*  Goal  : check if a specific coin's value is still available in the cash box */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - integer representing the coin's value */
    /*  IN/OUT: - */
    /*  OUT   : - boolean stating if this coin's value is still available or not */
    /*            '0' => coin's value not available anymore */
    /*            '1' => coin's value still available */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Get the current register's status of the available coins in the cash box */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    register_value = read_register(40978);

    /*  Select the specific coin's quantity to check */
    if ((register_value & 8) != 0) {
      give_back_coin(100U);
      remaining_amount = (unsigned short)(remaining_amount - 100);
    } else {
      exitg1 = true;
    }
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function return_coin_value() */
  /*  Goal  : give back the remaining amount of coins to return */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount_to_return: integer representing the money to give back */
  /*          - coin_value : integer representing the value of the current coin */
  /*  IN/OUT: - */
  /*  OUT   : -  integer representing the remaining amount of coins to return */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Try to return as much coins as possible */
  exitg1 = false;
  while ((!exitg1) && (remaining_amount >= 50)) {
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function is_this_coin_available() */
    /*  Goal  : check if a specific coin's value is still available in the cash box */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - integer representing the coin's value */
    /*  IN/OUT: - */
    /*  OUT   : - boolean stating if this coin's value is still available or not */
    /*            '0' => coin's value not available anymore */
    /*            '1' => coin's value still available */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Get the current register's status of the available coins in the cash box */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    b_register_value = read_register(40978);

    /*  Select the specific coin's quantity to check */
    if ((b_register_value & 4) != 0) {
      give_back_coin(50U);
      remaining_amount = (unsigned short)(remaining_amount - 50);
    } else {
      exitg1 = true;
    }
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function return_coin_value() */
  /*  Goal  : give back the remaining amount of coins to return */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount_to_return: integer representing the money to give back */
  /*          - coin_value : integer representing the value of the current coin */
  /*  IN/OUT: - */
  /*  OUT   : -  integer representing the remaining amount of coins to return */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Try to return as much coins as possible */
  exitg1 = false;
  while ((!exitg1) && (remaining_amount >= 20)) {
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function is_this_coin_available() */
    /*  Goal  : check if a specific coin's value is still available in the cash box */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - integer representing the coin's value */
    /*  IN/OUT: - */
    /*  OUT   : - boolean stating if this coin's value is still available or not */
    /*            '0' => coin's value not available anymore */
    /*            '1' => coin's value still available */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Get the current register's status of the available coins in the cash box */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    c_register_value = read_register(40978);

    /*  Select the specific coin's quantity to check */
    if ((c_register_value & 2) != 0) {
      give_back_coin(20U);
      remaining_amount = (unsigned short)(remaining_amount - 20);
    } else {
      exitg1 = true;
    }
  }

  b_remaining_amount = remaining_amount;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function return_coin_value() */
  /*  Goal  : give back the remaining amount of coins to return */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount_to_return: integer representing the money to give back */
  /*          - coin_value : integer representing the value of the current coin */
  /*  IN/OUT: - */
  /*  OUT   : -  integer representing the remaining amount of coins to return */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Try to return as much coins as possible */
  exitg1 = false;
  while ((!exitg1) && (b_remaining_amount >= 10)) {
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function is_this_coin_available() */
    /*  Goal  : check if a specific coin's value is still available in the cash box */
    /*  IN    : - const_obj: constants object used in the entire application */
    /*          - integer representing the coin's value */
    /*  IN/OUT: - */
    /*  OUT   : - boolean stating if this coin's value is still available or not */
    /*            '0' => coin's value not available anymore */
    /*            '1' => coin's value still available */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Get the current register's status of the available coins in the cash box */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function read_interface() */
    /*  Goal  : Define the interface layer reading data from external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*  IN/OUT: - */
    /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    d_register_value = read_register(40978);

    /*  Select the specific coin's quantity to check */
    if ((d_register_value & 1) != 0) {
      give_back_coin(10U);
      b_remaining_amount = (unsigned short)(b_remaining_amount - 10);
    } else {
      exitg1 = true;
    }
  }
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
 * Arguments    : void
 * Return Type  : void
 */
static void standard_operation_mode(void)
{
  bool red_button_pressed;
  bool master_switch_off;
  StateMachineParameters val_SFX_122_tmp;
  int i;
  int i1;
  Scheduler chart;
  static const char c_tSfInternalObj_SFX_175_chartL[15] = { 'R', 'E', 'F', 'R',
    'E', 'S', 'H', 'I', 'N', 'G', '_', 'T', 'I', 'C', 'K' };

  int i2;
  int i3;
  static const signed char c_tSfInternalObj_SFX_175_ctorUs[7] = { 1, 1, 1, 0, 1,
    1, 0 };

  int i4;
  int i5;
  static const char c_tSfInternalObj_SFX_175_chartA[21] = { 'I', 'N', 'T', '_',
    'M', 'A', 'S', 'K', '_', 'P', 'R', 'I', 'N', 'T', '_', 'T', 'I', 'C', 'K',
    'E', 'T' };

  int i6;
  static const char d_tSfInternalObj_SFX_175_chartA[16] = { 'S', 'E', 'G', 'M',
    'E', 'N', 'T', 'S', '_', 'D', 'I', 'G', 'I', 'T', '_', 'M' };

  int i7;
  static const char e_tSfInternalObj_SFX_175_chartA[10] = { 'T', 'I', 'C', 'K',
    'E', 'T', '_', 'F', 'E', 'E' };

  int i8;
  static const signed char f_tSfInternalObj_SFX_175_chartA[5] = { 83, 100, 79,
    88, 90 };

  int i9;
  int i10;
  int exitg1;
  bool y;
  int k;
  bool exitg2;
  int i11;
  int idx;
  bool x[7];
  int ii;
  int ii_size_idx_1;
  signed char ii_data[7];
  signed char isr_idx_data[7];
  int b_k;
  bool guard1 = false;
  unsigned char a;
  unsigned short u;
  unsigned short digit_value;
  unsigned short b_remainder;
  unsigned char register_value;
  unsigned char b_a;
  unsigned char new_reg_value;
  unsigned short b_x;
  unsigned char c_a;
  int b_chart;
  unsigned char b_register_value;
  unsigned char c_register_value;
  unsigned char d_a;
  unsigned char d_register_value;
  unsigned char e_a;
  unsigned char e_register_value;
  unsigned char f_register_value;
  unsigned char f_a;
  unsigned char g_register_value;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function standard_operation_mode() */
  /*  Goal  : Entry point of the standard mode of operation of the parking meter */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  red_button_pressed = false;
  master_switch_off = false;

  /*  Instanciation of the Stateflow Chart Object */
  val_SFX_122_tmp.sampling_time = 0.001;
  val_SFX_122_tmp.refreshing_time = 0.015;
  val_SFX_122_tmp.master_switch = true;
  val_SFX_122_tmp.green_pressed = false;
  val_SFX_122_tmp.red_pressed = false;
  val_SFX_122_tmp.coins_reg_value = 0U;
  val_SFX_122_tmp.inserted_amount = 0U;
  val_SFX_122_tmp.amount_to_return = 0U;
  val_SFX_122_tmp.flap_open = false;
  val_SFX_122_tmp.register_value = 0U;
  val_SFX_122_tmp.display_value = 0U;
  for (i = 0; i < 7; i++) {
    val_SFX_122_tmp.ISR[i] = false;
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Class StateMachineParameters */
  /*  Goal  : This class contains all the inputs and outputs of the interface to the */
  /*          state machine object. */
  /*  */
  /*  Author: Sebastien Dupertuis */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  TS */
  /*  Buttons trigger signals */
  /*  Coins related signals */
  /*  Scheduler's output signals */
  /*  Interrupts trigger vectors */
  for (i1 = 0; i1 < 15; i1++) {
    chart.sfInternalObj.chartLocalData.f1[i1] =
      c_tSfInternalObj_SFX_175_chartL[i1];
  }

  chart.sfInternalObj.chartLocalData.f2[0] = 'o';
  chart.sfInternalObj.chartLocalData.f2[1] = 'b';
  chart.sfInternalObj.chartLocalData.f2[2] = 'j';
  for (i2 = 0; i2 < 7; i2++) {
    chart.sfInternalObj.ctorUserChoices[i2] = c_tSfInternalObj_SFX_175_ctorUs[i2];
  }

  for (i3 = 0; i3 < 15; i3++) {
    chart.sfInternalObj.chartAllData.f1[i3] = c_tSfInternalObj_SFX_175_chartL[i3];
  }

  chart.sfInternalObj.chartAllData.f2[0] = 'o';
  chart.sfInternalObj.chartAllData.f2[1] = 'b';
  chart.sfInternalObj.chartAllData.f2[2] = 'j';
  for (i4 = 0; i4 < 21; i4++) {
    chart.sfInternalObj.chartAllData.f3[i4] = c_tSfInternalObj_SFX_175_chartA[i4];
  }

  for (i5 = 0; i5 < 16; i5++) {
    chart.sfInternalObj.chartAllData.f4[i5] = d_tSfInternalObj_SFX_175_chartA[i5];
  }

  for (i6 = 0; i6 < 10; i6++) {
    chart.sfInternalObj.chartAllData.f5[i6] = e_tSfInternalObj_SFX_175_chartA[i6];
  }

  for (i7 = 0; i7 < 5; i7++) {
    chart.sfInternalObj.chartAllDataSSID[i7] =
      f_tSfInternalObj_SFX_175_chartA[i7];
  }

  for (i8 = 0; i8 < 21; i8++) {
    chart.sfInternalObj.chartConstantData.f1[i8] =
      c_tSfInternalObj_SFX_175_chartA[i8];
  }

  for (i9 = 0; i9 < 16; i9++) {
    chart.sfInternalObj.chartConstantData.f2[i9] =
      d_tSfInternalObj_SFX_175_chartA[i9];
  }

  for (i10 = 0; i10 < 10; i10++) {
    chart.sfInternalObj.chartConstantData.f3[i10] =
      e_tSfInternalObj_SFX_175_chartA[i10];
  }

  chart.sfInternalObj.stepCount = 0.0;
  chart.sfInternalObj.enableDataLogging = false;
  chart.sfInternalObj.clockSpeedUp = 1.0;
  chart.sfInternalObj.enableAnimation = true;
  chart.sfInternalObj.animationDelay = 0.01;
  chart.sfInternalObj.externalClock = false;
  chart.sfInternalObj.executionTimeForTimers = true;
  chart.sfInternalObj.useMATLABTimerForSFTemporals = true;
  chart.sfInternalObj.executeAtInitialization = false;
  chart.c_PURCHASE_TICKET_activeChild_S = 0.0;
  chart.Counter_UPDATE_AMOUNT_SFX_176 = 0.0;
  chart.obj = val_SFX_122_tmp;
  chart.Scheduler_isActive_SFX_105 = true;
  chart.REFRESHING_TICK = 15.0;

  /* #__SFDEBUGSTART__#50#0#1#56#0#3#__SFDEBUGEND__ */
  chart.Scheduler_activeChild_SFX_16 = 3.0;

  /* State INITIALIZATION becomes active */
  /*  Reset of the parking meter status */
  chart.obj.display_value = 45U;

  /* #__SFDEBUGSTART__#3#0#58#111#0#4#__SFDEBUGEND__ */
  chart.obj.flap_open = false;

  /* #__SFDEBUGSTART__#3#0#113#135#0#4#__SFDEBUGEND__ */
  chart.obj.ISR[0] = true;

  /*  Initial state of the 7 segments displays%#__SFDEBUGSTART__#3#0#137#198#0#4#__SFDEBUGEND__ */
  chart.obj.ISR[1] = true;

  /*  Close the coin's flap%#__SFDEBUGSTART__#3#0#200#242#0#4#__SFDEBUGEND__ */
  /*  Infinite loop */
  do {
    /*  Run the scheduler in Stateflow */
    if (!chart.Scheduler_isActive_SFX_105) {
      chart.Scheduler_isActive_SFX_105 = true;
      chart.REFRESHING_TICK = chart.obj.refreshing_time /
        chart.obj.sampling_time;

      /* #__SFDEBUGSTART__#50#0#1#56#0#3#__SFDEBUGEND__ */
      chart.Scheduler_activeChild_SFX_16 = 3.0;

      /* State INITIALIZATION becomes active */
      /*  Reset of the parking meter status */
      chart.obj.display_value = 45U;

      /* #__SFDEBUGSTART__#3#0#58#111#0#4#__SFDEBUGEND__ */
      chart.obj.flap_open = false;

      /* #__SFDEBUGSTART__#3#0#113#135#0#4#__SFDEBUGEND__ */
      chart.obj.ISR[0] = true;

      /*  Initial state of the 7 segments displays%#__SFDEBUGSTART__#3#0#137#198#0#4#__SFDEBUGEND__ */
      chart.obj.ISR[1] = true;

      /*  Close the coin's flap%#__SFDEBUGSTART__#3#0#200#242#0#4#__SFDEBUGEND__ */
    } else {
      c_Scheduler_Scheduler_during_SF(&chart);
    }

    /*  Process ISRs when raised */
    do {
      exitg1 = 0;
      y = false;
      k = 0;
      exitg2 = false;
      while ((!exitg2) && (k < 7)) {
        if (chart.obj.ISR[k]) {
          y = true;
          exitg2 = true;
        } else {
          k++;
        }
      }

      if (y) {
        /*  Identified raised ISRs */
        for (i11 = 0; i11 < 7; i11++) {
          x[i11] = chart.obj.ISR[i11];
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

        if (1 > idx) {
          ii_size_idx_1 = 0;
        } else {
          ii_size_idx_1 = idx;
        }

        if (0 <= ii_size_idx_1 - 1) {
          memcpy(&isr_idx_data[0], &ii_data[0], ii_size_idx_1 * sizeof(signed
                  char));
        }

        b_k = 0;
        exitg2 = false;
        while ((!exitg2) && (b_k <= ii_size_idx_1 - 1)) {
          guard1 = false;
          switch (isr_idx_data[b_k]) {
           case 1:
            /*  Update the values of the 7 segment displays */
            /*  Initialization value of the parking meter display */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function display_cents_value() */
            /*  Goal  : Update the new parking meter cents value */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - cents_value: base 10 value to display on all 7 segments displays */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            if (chart.obj.display_value == 45) {
              display_digit(1U, 45U, 0.0);
              display_digit(2U, 45U, 0.0);
              display_digit(3U, 45U, 0.0);

              /*  Compute the right value to display on the parking meter */
            } else if (chart.obj.display_value <= 999) {
              /*  Compute the cent */
              digit_value = (unsigned short)((unsigned int)
                chart.obj.display_value - (int)(chart.obj.display_value / 10U) *
                10);
              display_digit(1U, digit_value, 0.0);

              /*  Compute the tens of cents */
              b_remainder = (unsigned short)rt_roundd((double)(unsigned short)
                ((unsigned int)chart.obj.display_value - digit_value) / 10.0);
              digit_value = (unsigned short)((unsigned int)b_remainder - (int)
                (b_remainder / 10U) * 10);
              display_digit(2U, digit_value, 0.0);

              /*  Compute the hundreds of cents */
              b_x = (unsigned short)rt_roundd((double)(unsigned short)((unsigned
                int)b_remainder - digit_value) / 10.0);
              display_digit(3U, (unsigned short)((unsigned int)b_x - (int)(b_x /
                10U) * 10), 1.0);
            } else {
              printf("Incorrect cents value provided to the parking meter display!\n");
              fflush(stdout);
            }

            guard1 = true;
            break;

           case 2:
            /*  Update the coins flap status */
            /*  Get the current peripherals register status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function set_coin_flap_position() */
            /*  Goal  : Open or close the coin's flap */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - flap_open: '1' => coin flap to open */
            /*                       '0' => coin flap to close */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            register_value = read_register(40963);

            /*  Set the corresponding bit of the register depending on flap_open */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function write_interface() */
            /*  Goal  : Define the interface layer writing data to external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*          - new_value: value to store in the register as an unsigned 8 bit */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            if (chart.obj.flap_open) {
              b_chart = register_value | 128;
            } else {
              b_chart = register_value & 127;
            }

            write_register(40963, (unsigned char)b_chart);
            guard1 = true;
            break;

           case 3:
            /*  Check if the parking meter can give money back if needed */
            /*  Check if any coin's value is empty */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_able_to_give_back_any_coins() */
            /*  Goal  : check if a specific coin's value is still available in the cash box */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in the cash box */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Get the current register's status of the available coins in the cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            b_register_value = read_register(40978);

            /*  Select the specific coin's quantity to check */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in the cash box */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Get the current register's status of the available coins in the cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            d_register_value = read_register(40978);

            /*  Select the specific coin's quantity to check */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in the cash box */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Get the current register's status of the available coins in the cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            e_register_value = read_register(40978);

            /*  Select the specific coin's quantity to check */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_this_coin_available() */
            /*  Goal  : check if a specific coin's value is still available in the cash box */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - integer representing the coin's value */
            /*  IN/OUT: - */
            /*  OUT   : - boolean stating if this coin's value is still available or not */
            /*            '0' => coin's value not available anymore */
            /*            '1' => coin's value still available */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Get the current register's status of the available coins in the cash box */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            f_register_value = read_register(40978);

            /*  Select the specific coin's quantity to check */
            /*  Get the current peripherals register status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function switch_leds_on() */
            /*  Goal  : Open or close the coin's flap */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - can_give_coins_back: '1' => yes, it can give coins back */
            /*                                 '0' => no, because the cash box is empty */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            f_a = read_register(40963);
            g_register_value = (unsigned char)(f_a & 159);

            /*  Set the corresponding bit of the register depending on can_give_coins_back */
            if (((b_register_value & 1) != 0) && ((d_register_value & 2) != 0) &&
                ((e_register_value & 4) != 0) && ((f_register_value & 8) != 0))
            {
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW registers */
              /*  IN    : - register_address: address of the register in unsigned 16 bit */
              /*          - new_value: value to store in the register as an unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              write_register(40963, (unsigned char)(g_register_value | 32));
            } else {
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW registers */
              /*  IN    : - register_address: address of the register in unsigned 16 bit */
              /*          - new_value: value to store in the register as an unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              write_register(40963, (unsigned char)(g_register_value | 64));
            }

            guard1 = true;
            break;

           case 4:
            if (!chart.obj.red_pressed) {
              /*  Print the parking ticket */
              /*  Trigger the printing of the parking receipt */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function print_receipt() */
              /*  Goal  : Command the parking meter to print the corresponding receipt */
              /*  IN    : - const_obj: constants object used in the entire application */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Read the current value stored in the register */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function generate_peripherals_pulse() */
              /*  Goal  : Every time an action is applied to the peripherals, the */
              /*          corresponding bit in the peripherals register is set or reset */
              /*  IN    : - const_obj: constants object used in the entire application */
              /*          - bit_mask: mask of the specific bit to modify in the register */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function read_interface() */
              /*  Goal  : Define the interface layer reading data from external HW registers */
              /*  IN    : - register_address: address of the register in unsigned 16 bit */
              /*  IN/OUT: - */
              /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              c_a = read_register(40963);

              /*  Set the selected bit to '1' and write the new value to the register */
              c_register_value = (unsigned char)(c_a | 16);

              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW registers */
              /*  IN    : - register_address: address of the register in unsigned 16 bit */
              /*          - new_value: value to store in the register as an unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              write_register(40963, c_register_value);

              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function sleep_interface() */
              /*  Goal  : Define the interface layer to pause the system for an amount of time */
              /*  IN    : - duration: time duration in seconds */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              Sleep(100);

              /*  Sleep asks milliseconds as input */
              /*  Reset the selected bit only and write the new value to the register */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function write_interface() */
              /*  Goal  : Define the interface layer writing data to external HW registers */
              /*  IN    : - register_address: address of the register in unsigned 16 bit */
              /*          - new_value: value to store in the register as an unsigned 8 bit */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              write_register(40963, (unsigned char)(c_register_value ^ 16));

              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              /*  Function sleep_interface() */
              /*  Goal  : Define the interface layer to pause the system for an amount of time */
              /*  IN    : - duration: time duration in seconds */
              /*  IN/OUT: - */
              /*  OUT   : - */
              /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
              Sleep(100);

              /*  Sleep asks milliseconds as input */
            }

            /*  Give back coin's change */
            return_coins(chart.obj.amount_to_return);
            chart.obj.amount_to_return = 0U;
            guard1 = true;
            break;

           case 5:
            /*  Check if the buttons have changed their states */
            /*  Bit mask to extract green button status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_green_button_pressed() */
            /*  Goal  : Poll the button register continuously to see if the green button has */
            /*          been pressed */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean: '0' => green button not pressed */
            /*                     '1' => green button pressed */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            b_a = read_register(40976);
            chart.obj.green_pressed = ((b_a & 1) != 0);

            /*  Bit mask to extract red button status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_red_button_pressed() */
            /*  Goal  : Poll the button register when needed to see if the red button has been */
            /*          pressed to cancel the ticket purchase process */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean: '0' => red button not pressed */
            /*                     '1' => red button pressed */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            d_a = read_register(40976);
            chart.obj.red_pressed = ((d_a & 2) != 0);

            /*  Bit mask to extract master switch status */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function is_master_switch_on() */
            /*  Goal  : Check the button register to see if the master switch has been */
            /*          switched off */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*  IN/OUT: - */
            /*  OUT   : - boolean: '0' => master switch is OFF */
            /*                     '1' => master switch is ON */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            e_a = read_register(40976);
            chart.obj.master_switch = ((e_a & 4) != 0);

            /*  Ticket's purchase process canceled */
            if (chart.obj.red_pressed) {
              return_coins(chart.obj.amount_to_return);
              red_button_pressed = true;
              exitg2 = true;
            } else {
              guard1 = true;
            }
            break;

           case 6:
            /*  Update the amount of money to pay if a coin has been inserted */
            a = chart.obj.register_value;

            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function amount_inserted_coins() */
            /*  Goal  : get the amount of the inserted coins */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - integer representing the current amount of inserted coins */
            /*  IN/OUT: - */
            /*  OUT   : - integer representing the updated amount of inserted coins */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            u = 0U;

            /*  Get the very last amount of coins that have already been inserted */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function read_interface() */
            /*  Goal  : Define the interface layer reading data from external HW registers */
            /*  IN    : - register_address: address of the register in unsigned 16 bit */
            /*  IN/OUT: - */
            /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            new_reg_value = read_register(40977);

            /*  A new coin has been inserted into the parking meter */
            if (new_reg_value != chart.obj.register_value) {
              /*  Update the amount of coins already inserted */
              if (((new_reg_value & 1) != 0) && ((chart.obj.register_value & 1) ==
                   0)) {
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
              } else {
                if (((new_reg_value & 16) != 0) && ((chart.obj.register_value &
                      16) == 0)) {
                  u = 200U;
                }
              }

              /*  Record of the current register value */
              a = new_reg_value;
            }

            chart.obj.temp_amount = u;
            chart.obj.register_value = a;
            chart.obj.inserted_amount = (unsigned short)((unsigned int)
              chart.obj.inserted_amount + u);
            guard1 = true;
            break;

           default:
            /*  Terminate the execution of the application */
            master_switch_off = true;
            exitg2 = true;
            break;
          }

          if (guard1) {
            /*  Reset the ISR once it has been served */
            chart.obj.ISR[isr_idx_data[b_k] - 1] = false;
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
 * Text constant declaration
 * Arguments    : void
 * Return Type  : void
 */
static void test_mode(void)
{
  int choice;
  int exitg1;
  int exitg2;
  char terminator;
  char * format;
  int nb_input_types;
  bool guard1 = false;
  bool b_bool;
  char * CLEAR_STDIN;
  unsigned char a;
  unsigned char register_value;
  int state;
  int data;
  int b;
  char b_terminator;
  char c_terminator;
  char d_terminator;
  char * b_format;
  char * c_format;
  int b_nb_input_types;
  int c_nb_input_types;
  char * d_format;
  int d_nb_input_types;
  bool c_bool;
  bool d_bool;
  bool e_bool;
  char * b_CLEAR_STDIN;
  char * c_CLEAR_STDIN;
  int i;
  int b_i;
  char * d_CLEAR_STDIN;
  unsigned char validatedHoleFilling_idx_0;
  unsigned char b_a;
  unsigned char b_register_value;
  unsigned char c_register_value;
  int b_data;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function test_mode() */
  /*  Goal  : Entry point of the test mode of the parking meter */
  /*  IN    : - test_obj: object having all needed properties and methods for the */
  /*                      testing mode of operation */
  /*          - f_api   : functions handler struct listing functions to access */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Variables declaration */
  choice = 1;

  /*  Split sections */
  printf("%s\n",
         "-------------------------------------------------------------------------------");
  fflush(stdout);

  /*  Loop over the menu entries */
  do {
    exitg1 = 0;
    if (choice != 0) {
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
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Class TestMode */
      /*  Goal  : This subclass contains all the global constants needed for the test */
      /*          mode of the Parking Meter Low Level program. */
      /*          Once an object has been created out of the superclass, it must then be */
      /*          passed has an input argument to all the functions of the application. */
      /*  */
      /*  Author: Sebastien Dupertuis */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  The following constants will be added to the superclass "Constants" */
      /*  Char separator to split sections */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Function check_get_data() */
      /*  Goal  : Test the write access function to any shared memory register */
      /*  IN    : - promp_text: pointer to a chain char to display in the console */
      /*          - min_data  : minimum value that is allowed in the range of data */
      /*          - max_data  : maximum value that is allowed in the range of data */
      /*  IN/OUT: - */
      /*  OUT   : - integer value to get from the console interface */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Variables declaration */
      choice = 0;

      /*  Get and check the data from the console */
      do {
        exitg2 = 0;

        /*  Get input data using the Windows C API */
        terminator = ' ';
        printf("%s",
               "Enter the menu entry of the operation to do on the parking meter [0 - 8]: ");
        fflush(stdout);

        /*  Force the string format definition in the generated C code for scanf_s */
        format = "%d%c";
        nb_input_types = scanf_s(format, &choice, &terminator, 1);

        /*  Check if the provided data is an integer number */
        guard1 = false;
        if (nb_input_types == 2) {
          b_bool = !(terminator != '\x0a');
          if (b_bool) {
            /*  Check if the value is within the allowed range */
            if ((choice >= 0) && (choice <= 8)) {
              exitg2 = 1;
            } else {
              printf("The value provided must be between %d and %d!\n", 0, 8);
              fflush(stdout);
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          printf("The value provided is not of the right data type!\n");
          fflush(stdout);

          /*  Force the string regular expression in the generated C code for scanf_s */
          CLEAR_STDIN = "%*[^\n]%*1[\n]";

          /*  Clear the input buffer */
          scanf_s(CLEAR_STDIN);
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

       case 2:
        TestMode_display_value();
        break;

       case 3:
        /*  Text constants declaration  */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function leds_return_money() */
        /*  Goal  : Test the LEDs showing if coins can be given back or not */
        /*  IN    : - const_obj: object containing all needed constants */
        /*          - f_api    : functions handler struct listing functions to access */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Variables declaration  */
        /*  Split sections  */
        printf("%s\n",
               "-------------------------------------------------------------------------------");
        fflush(stdout);

        /*  Get the data to write in the register  */
        /*  Function that is not translated into C code */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Class TestMode */
        /*  Goal  : This subclass contains all the global constants needed for the test */
        /*          mode of the Parking Meter Low Level program. */
        /*          Once an object has been created out of the superclass, it must then be */
        /*          passed has an input argument to all the functions of the application. */
        /*  */
        /*  Author: Sebastien Dupertuis */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  The following constants will be added to the superclass "Constants" */
        /*  Char separator to split sections */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function check_get_data() */
        /*  Goal  : Test the write access function to any shared memory register */
        /*  IN    : - promp_text: pointer to a chain char to display in the console */
        /*          - min_data  : minimum value that is allowed in the range of data */
        /*          - max_data  : maximum value that is allowed in the range of data */
        /*  IN/OUT: - */
        /*  OUT   : - integer value to get from the console interface */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Variables declaration */
        state = 0;

        /*  Get and check the data from the console */
        do {
          exitg2 = 0;

          /*  Get input data using the Windows C API */
          b_terminator = ' ';
          printf("%s", "State value of the give back cash LEDs [0-1]: ");
          fflush(stdout);

          /*  Force the string format definition in the generated C code for scanf_s */
          b_format = "%d%c";
          b_nb_input_types = scanf_s(b_format, &state, &b_terminator, 1);

          /*  Check if the provided data is an integer number */
          guard1 = false;
          if (b_nb_input_types == 2) {
            c_bool = !(b_terminator != '\x0a');
            if (c_bool) {
              /*  Check if the value is within the allowed range */
              if ((state >= 0) && (state <= 1)) {
                exitg2 = 1;
              } else {
                printf("The value provided must be between %d and %d!\n", 0, 1);
                fflush(stdout);
              }
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            printf("The value provided is not of the right data type!\n");
            fflush(stdout);

            /*  Force the string regular expression in the generated C code for scanf_s */
            b_CLEAR_STDIN = "%*[^\n]%*1[\n]";

            /*  Clear the input buffer */
            scanf_s(b_CLEAR_STDIN);
          }
        } while (exitg2 == 0);

        /*  Write the user's data to the 7 segments displays  */
        /*  Get the current peripherals register status */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function switch_leds_on() */
        /*  Goal  : Open or close the coin's flap */
        /*  IN    : - const_obj: constants object used in the entire application */
        /*          - can_give_coins_back: '1' => yes, it can give coins back */
        /*                                 '0' => no, because the cash box is empty */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function read_interface() */
        /*  Goal  : Define the interface layer reading data from external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*  IN/OUT: - */
        /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        b_a = read_register(40963);
        c_register_value = (unsigned char)(b_a & 159);

        /*  Set the corresponding bit of the register depending on can_give_coins_back */
        if (state == 1) {
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function write_interface() */
          /*  Goal  : Define the interface layer writing data to external HW registers */
          /*  IN    : - register_address: address of the register in unsigned 16 bit */
          /*          - new_value: value to store in the register as an unsigned 8 bit */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          write_register(40963, (unsigned char)(c_register_value | 32));
        } else {
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function write_interface() */
          /*  Goal  : Define the interface layer writing data to external HW registers */
          /*  IN    : - register_address: address of the register in unsigned 16 bit */
          /*          - new_value: value to store in the register as an unsigned 8 bit */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          write_register(40963, (unsigned char)(c_register_value | 64));
        }

        printf("%s\n\n",
               "The desired value has been successfullywritten to the give back cash LEDs.");
        fflush(stdout);
        printf("%s\n",
               "-------------------------------------------------------------------------------");
        fflush(stdout);
        break;

       case 4:
        TestMode_give_back_coin();
        break;

       case 5:
        /*  Trigger the printing of the parking receipt */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function print_receipt() */
        /*  Goal  : Command the parking meter to print the corresponding receipt */
        /*  IN    : - const_obj: constants object used in the entire application */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Read the current value stored in the register */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function generate_peripherals_pulse() */
        /*  Goal  : Every time an action is applied to the peripherals, the */
        /*          corresponding bit in the peripherals register is set or reset */
        /*  IN    : - const_obj: constants object used in the entire application */
        /*          - bit_mask: mask of the specific bit to modify in the register */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function read_interface() */
        /*  Goal  : Define the interface layer reading data from external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*  IN/OUT: - */
        /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        a = read_register(40963);

        /*  Set the selected bit to '1' and write the new value to the register */
        register_value = (unsigned char)(a | 16);

        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function write_interface() */
        /*  Goal  : Define the interface layer writing data to external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*          - new_value: value to store in the register as an unsigned 8 bit */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        write_register(40963, register_value);

        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function sleep_interface() */
        /*  Goal  : Define the interface layer to pause the system for an amount of time */
        /*  IN    : - duration: time duration in seconds */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        Sleep(100);

        /*  Sleep asks milliseconds as input */
        /*  Reset the selected bit only and write the new value to the register */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function write_interface() */
        /*  Goal  : Define the interface layer writing data to external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*          - new_value: value to store in the register as an unsigned 8 bit */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        write_register(40963, (unsigned char)(register_value ^ 16));

        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function sleep_interface() */
        /*  Goal  : Define the interface layer to pause the system for an amount of time */
        /*  IN    : - duration: time duration in seconds */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        Sleep(100);

        /*  Sleep asks milliseconds as input */
        printf("%s\n\n",
               "-------------------------------------------------------------------------------");
        fflush(stdout);
        break;

       case 6:
        /*  Text constants declaration  */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function coin_flap_position() */
        /*  Goal  : Test if the coin's flap can be opened and closed */
        /*  IN    : - const_obj: object containing all needed constants */
        /*          - f_api    : functions handler struct listing functions to access */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Variables declaration  */
        /*  Split sections  */
        printf("%s\n",
               "-------------------------------------------------------------------------------");
        fflush(stdout);

        /*  Get and check the flap position provided at the console interface  */
        /*  Function that is not translated into C code */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Class TestMode */
        /*  Goal  : This subclass contains all the global constants needed for the test */
        /*          mode of the Parking Meter Low Level program. */
        /*          Once an object has been created out of the superclass, it must then be */
        /*          passed has an input argument to all the functions of the application. */
        /*  */
        /*  Author: Sebastien Dupertuis */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  The following constants will be added to the superclass "Constants" */
        /*  Char separator to split sections */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function check_get_data() */
        /*  Goal  : Test the write access function to any shared memory register */
        /*  IN    : - promp_text: pointer to a chain char to display in the console */
        /*          - min_data  : minimum value that is allowed in the range of data */
        /*          - max_data  : maximum value that is allowed in the range of data */
        /*  IN/OUT: - */
        /*  OUT   : - integer value to get from the console interface */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Variables declaration */
        data = 0;

        /*  Get and check the data from the console */
        do {
          exitg2 = 0;

          /*  Get input data using the Windows C API */
          c_terminator = ' ';
          printf("%s",
                 "Set the position of the coin\'s flap [open => \'1\', close => \'0\']: ");
          fflush(stdout);

          /*  Force the string format definition in the generated C code for scanf_s */
          c_format = "%d%c";
          c_nb_input_types = scanf_s(c_format, &data, &c_terminator, 1);

          /*  Check if the provided data is an integer number */
          guard1 = false;
          if (c_nb_input_types == 2) {
            d_bool = !(c_terminator != '\x0a');
            if (d_bool) {
              /*  Check if the value is within the allowed range */
              if ((data >= 0) && (data <= 1)) {
                exitg2 = 1;
              } else {
                printf("The value provided must be between %d and %d!\n", 0, 1);
                fflush(stdout);
              }
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            printf("The value provided is not of the right data type!\n");
            fflush(stdout);

            /*  Force the string regular expression in the generated C code for scanf_s */
            c_CLEAR_STDIN = "%*[^\n]%*1[\n]";

            /*  Clear the input buffer */
            scanf_s(c_CLEAR_STDIN);
          }
        } while (exitg2 == 0);

        /*  Update the position of the flap  */
        /*  Get the current peripherals register status */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function set_coin_flap_position() */
        /*  Goal  : Open or close the coin's flap */
        /*  IN    : - const_obj: constants object used in the entire application */
        /*          - flap_open: '1' => coin flap to open */
        /*                       '0' => coin flap to close */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function read_interface() */
        /*  Goal  : Define the interface layer reading data from external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*  IN/OUT: - */
        /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        b_register_value = read_register(40963);

        /*  Set the corresponding bit of the register depending on flap_open */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function write_interface() */
        /*  Goal  : Define the interface layer writing data to external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*          - new_value: value to store in the register as an unsigned 8 bit */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        if (data != 0) {
          b_data = b_register_value | 128;
        } else {
          b_data = b_register_value & 127;
        }

        write_register(40963, (unsigned char)b_data);
        break;

       case 7:
        /*  Include the header file containing the needed functions declarations */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function input_registers() */
        /*  Goal  : Read for a desired time the current status of the input registers */
        /*  IN    : - const_obj: object containing all needed constants */
        /*          - f_api    : functions handler struct listing functions to access */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Text constants declaration  */
        /*  Split sections  */
        printf("%s\n",
               "-------------------------------------------------------------------------------");
        fflush(stdout);

        /*  Get and check the time limit provided at the console interface  */
        /*  Function that is not translated into C code */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Class TestMode */
        /*  Goal  : This subclass contains all the global constants needed for the test */
        /*          mode of the Parking Meter Low Level program. */
        /*          Once an object has been created out of the superclass, it must then be */
        /*          passed has an input argument to all the functions of the application. */
        /*  */
        /*  Author: Sebastien Dupertuis */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  The following constants will be added to the superclass "Constants" */
        /*  Char separator to split sections */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function check_get_data() */
        /*  Goal  : Test the write access function to any shared memory register */
        /*  IN    : - promp_text: pointer to a chain char to display in the console */
        /*          - min_data  : minimum value that is allowed in the range of data */
        /*          - max_data  : maximum value that is allowed in the range of data */
        /*  IN/OUT: - */
        /*  OUT   : - integer value to get from the console interface */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Variables declaration */
        b = 0;

        /*  Get and check the data from the console */
        do {
          exitg2 = 0;

          /*  Get input data using the Windows C API */
          d_terminator = ' ';
          printf("%s",
                 "Enter the desired time to read the inputregisters in seconds [\'1\'-\'100\']: ");
          fflush(stdout);

          /*  Force the string format definition in the generated C code for scanf_s */
          d_format = "%d%c";
          d_nb_input_types = scanf_s(d_format, &b, &d_terminator, 1);

          /*  Check if the provided data is an integer number */
          guard1 = false;
          if (d_nb_input_types == 2) {
            e_bool = !(d_terminator != '\x0a');
            if (e_bool) {
              /*  Check if the value is within the allowed range */
              if ((b >= 1) && (b <= 100)) {
                exitg2 = 1;
              } else {
                printf("The value provided must be between %d and %d!\n", 1, 100);
                fflush(stdout);
              }
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            printf("The value provided is not of the right data type!\n");
            fflush(stdout);

            /*  Force the string regular expression in the generated C code for scanf_s */
            d_CLEAR_STDIN = "%*[^\n]%*1[\n]";

            /*  Clear the input buffer */
            scanf_s(d_CLEAR_STDIN);
          }
        } while (exitg2 == 0);

        /*  Read the input registers continuously  */
        i = 10 * b;
        for (b_i = 0; b_i <= i; b_i++) {
          printf("%s\n",
                 "-------------------------------------------------------------------------------");
          fflush(stdout);

          /*  Split measurements  */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function read_interface() */
          /*  Goal  : Define the interface layer reading data from external HW registers */
          /*  IN    : - register_address: address of the register in unsigned 16 bit */
          /*  IN/OUT: - */
          /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          validatedHoleFilling_idx_0 = read_register(40978);
          printf("Available coins: %x\n", validatedHoleFilling_idx_0);
          fflush(stdout);

          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function read_interface() */
          /*  Goal  : Define the interface layer reading data from external HW registers */
          /*  IN    : - register_address: address of the register in unsigned 16 bit */
          /*  IN/OUT: - */
          /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          validatedHoleFilling_idx_0 = read_register(40977);
          printf("Inserted coins : %x\n", validatedHoleFilling_idx_0);
          fflush(stdout);

          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function read_interface() */
          /*  Goal  : Define the interface layer reading data from external HW registers */
          /*  IN    : - register_address: address of the register in unsigned 16 bit */
          /*  IN/OUT: - */
          /*  OUT   : - register_value: value stored in the register as an unsigned 8 bit */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          validatedHoleFilling_idx_0 = read_register(40976);
          printf("Pushed buttons : %x\n", validatedHoleFilling_idx_0);
          fflush(stdout);
          printf("Elapsed time   : %3.1f\n", (float)rt_roundd((double)((b_i + 1)
                   * 100) / 1000.0));
          fflush(stdout);

          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Sleep(100);

          /*  Sleep asks milliseconds as input */
        }

        /*  Split sections  */
        printf("%s\n\n",
               "-------------------------------------------------------------------------------");
        fflush(stdout);
        break;

       case 8:
        printf("%s\n",
               "The normal mode of operation of the parking meter has been activated.");
        fflush(stdout);
        standard_operation_mode();
        break;

       default:
        printf("Incorrect menu choice.\n");
        fflush(stdout);
        break;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void parkingMeterLowLevel(void)
{
  if (isInitialized_parkingMeterLowLevel == false) {
    parkingMeterLowLevel_initialize();
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function parkingMeterLowLevel() */
  /*  Goal  : Main entry point of the parking meter application */
  /*  IN    : - */
  /*  IN/OUT: - */
  /*  OUT   : - error_flag: error code */
  /*  */
  /*  Copyright 2019 The MathWorks, Inc. */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Initialization */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Interface layer definition for target dependent HW */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function initialization_interface() */
  /*  Goal  : Define the interface layer to initialize the main function */
  /*  IN    : - */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Set Coder settings to add the needed headers and sources paths */
  /*  Include the header file containing the needed functions declarations */
  if (TEST_MODE == 0) {
    /*  Instantiate all constants for the normal application */
    printf("The normal mode of operation of the parking meter has been activated.\n");
    fflush(stdout);
    printf("Feel free to purchase tickets.\n");
    fflush(stdout);
    standard_operation_mode();
    printf("The Master Switch of the Parking Meter Interface is switched off.\n");
    fflush(stdout);
    printf("Press \'ENTER\' to close the console window...\n");
    fflush(stdout);
    getchar();
  } else {
    /*  TEST_MODE == 1 */
    /*  Function handler API to access functions of the test mode */
    /*  Instantiate all properties and methods for the test mode */
    /*  Entry point of the test mode */
    test_mode();
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
  /* (no terminate code required) */
  isInitialized_parkingMeterLowLevel = false;
}

/*
 * File trailer for parkingMeterLowLevel.c
 *
 * [EOF]
 */
