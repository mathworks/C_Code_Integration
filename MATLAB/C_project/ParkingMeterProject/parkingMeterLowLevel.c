/*
 * File: parkingMeterLowLevel.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 15-Feb-2021 19:03:03
 */

/* Include Files */
#include "parkingMeterLowLevel.h"
#include "ParkingMeterMemory.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>

/* Variable Definitions */
int TEST_MODE;
static unsigned char pauseState;
static bool isInitialized_parkingMeterLowLevel = false;

/* Function Declarations */
static void TestMode_display_value(void);
static void TestMode_give_back_coin(void);
static void TestMode_write_register(void);
static void b_display_digit(unsigned char display_ID, int digit_value, double
  dot_segment);
static void cpause_init(void);
static void display_cents_value(unsigned short cents_value);
static void display_digit(unsigned char display_ID, unsigned short digit_value,
  double dot_segment);
static int div_nde_s32_floor(int numerator, int denominator);
static void give_back_coin(unsigned short amount);
static unsigned short return_coin_value(unsigned short amount_to_return,
  unsigned short coin_value);
static double rt_roundd(double u);
static void standard_operation_mode(void);

/* Function Definitions */
/*
 * Text constants declaration
 * Arguments    : void
 * Return Type  : void
 */
static void TestMode_display_value(void)
{
  int b_remainder;
  int data;
  int digit_value;
  int exitg1;
  int nb_input_types;
  int x;
  char terminator;
  bool b_bool;
  bool guard1 = false;

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
    nb_input_types = scanf_s("%d%c", &data, &terminator, 1);

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
      /*  Clear the input buffer */
      scanf_s("%*[^\n]%*1[\n]");
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
  int nb_input_types;
  char terminator;
  bool b_bool;
  bool guard1 = false;

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
        nb_input_types = scanf_s("%d%c", &coin_choice, &terminator, 1);

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
          /*  Clear the input buffer */
          scanf_s("%*[^\n]%*1[\n]");
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
  static const unsigned short uv[7] = { 40960U, 40961U, 40962U, 40963U, 40976U,
    40977U, 40978U };

  int data;
  int exitg1;
  int i;
  int nb_input_types;
  int register_text;
  char terminator;
  bool b_bool;
  bool exitg2;
  bool guard1 = false;
  bool is_right_value;

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
    scanf_s("%x", &register_text);

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
      /*  Clear the input buffer */
      scanf_s("%*[^\n]%*1[\n]");
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
    nb_input_types = scanf_s("%d%c", &data, &terminator, 1);

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
      /*  Clear the input buffer */
      scanf_s("%*[^\n]%*1[\n]");
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

   case 3:
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
 * Arguments    : void
 * Return Type  : void
 */
static void cpause_init(void)
{
  pauseState = 0U;
}

/*
 * Initialization value of the parking meter display
 * Arguments    : unsigned short cents_value
 * Return Type  : void
 */
static void display_cents_value(unsigned short cents_value)
{
  unsigned short b_remainder;
  unsigned short digit_value;
  unsigned short x;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function display_cents_value() */
  /*  Goal  : Update the new parking meter cents value */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - cents_value: base 10 value to display on all 7 segments displays */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  if (cents_value == 45) {
    display_digit(1U, 45U, 0.0);
    display_digit(2U, 45U, 0.0);
    display_digit(3U, 45U, 0.0);

    /*  Compute the right value to display on the parking meter */
  } else if (cents_value <= 999) {
    /*  Compute the cent */
    digit_value = (unsigned short)((unsigned int)cents_value - (int)(cents_value
      / 10U) * 10);
    display_digit(1U, digit_value, 0.0);

    /*  Compute the tens of cents */
    b_remainder = (unsigned short)rt_roundd((double)(unsigned short)((unsigned
      int)cents_value - digit_value) / 10.0);
    digit_value = (unsigned short)((unsigned int)b_remainder - (int)(b_remainder
      / 10U) * 10);
    display_digit(2U, digit_value, 0.0);

    /*  Compute the hundreds of cents */
    x = (unsigned short)rt_roundd((double)(unsigned short)((unsigned int)
      b_remainder - digit_value) / 10.0);
    display_digit(3U, (unsigned short)((unsigned int)x - (int)(x / 10U) * 10),
                  1.0);
  } else {
    printf("Incorrect cents value provided to the parking meter display!\n");
    fflush(stdout);
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

   case 3:
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
  unsigned char b_register_value;
  unsigned char c_a;
  unsigned char c_register_value;
  unsigned char d_a;
  unsigned char d_register_value;
  unsigned char register_value;

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

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
    /*  Interface layer definition for target dependent HW */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function sleep_interface() */
    /*  Goal  : Define the interface layer to pause the system for an amount of time */
    /*  IN    : - duration: time duration in seconds */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Sleep(250);

    /*  Sleep asks milliseconds as input */
    break;

   default:
    printf("Incorrect coin\'s value provided to the parking meter change module!\n");
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
  unsigned char register_value;
  bool available;
  bool exitg1;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function return_coin_value() */
  /*  Goal  : give back the remaining amount of coins to return */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*          - amount_to_return: integer representing the money to give back */
  /*          - coin_value : integer representing the value of the current coin */
  /*  IN/OUT: - */
  /*  OUT   : -  integer representing the remaining amount of coins to return */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  remaining_amount = amount_to_return;

  /*  Try to return as much coins as possible */
  exitg1 = false;
  while ((!exitg1) && (remaining_amount >= coin_value)) {
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
    available = false;

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
    switch (coin_value) {
     case 10:
      available = ((register_value & 1) != 0);
      break;

     case 20:
      available = ((register_value & 2) != 0);
      break;

     case 50:
      available = ((register_value & 4) != 0);
      break;

     case 100:
      available = ((register_value & 8) != 0);
      break;

     default:
      printf("Incorrect coin\'s value provided to the parking meter cash box module!\n");
      fflush(stdout);
      break;
    }

    if (available) {
      give_back_coin(coin_value);
      remaining_amount = (unsigned short)((unsigned int)remaining_amount -
        coin_value);
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
 * Arguments    : void
 * Return Type  : void
 */
static void standard_operation_mode(void)
{
  int exitg1;
  int exitg2;
  int exitg3;
  unsigned short b_remaining_amount;
  unsigned short inserted_amount;
  unsigned short remaining_amount;
  unsigned short temp_amount;
  unsigned char a;
  unsigned char b_a;
  unsigned char b_register_value;
  unsigned char c_a;
  unsigned char c_register_value;
  unsigned char d_a;
  unsigned char d_register_value;
  unsigned char e_a;
  unsigned char f_a;
  unsigned char g_a;
  unsigned char h_a;
  unsigned char i_a;
  unsigned char j_a;
  unsigned char k_a;
  unsigned char new_reg_value;
  unsigned char register_value;
  bool master_switch_off;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function standard_operation_mode() */
  /*  Goal  : Entry point of the standard mode of operation of the parking meter */
  /*  IN    : - const_obj: constants object used in the entire application */
  /*  IN/OUT: - */
  /*  OUT   : - */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  master_switch_off = false;
  do {
    exitg2 = 0;

    /*  Initialization */
    display_cents_value(45U);

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
    a = read_register(40963);

    /*  Set the corresponding bit of the register depending on flap_open */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40963, (unsigned char)(a & 127));

    /*  Waiting on user inputs */
    do {
      exitg3 = 0;

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
      b_a = read_register(40978);

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
      c_a = read_register(40978);

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
      d_a = read_register(40978);

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
      e_a = read_register(40978);

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
      register_value = (unsigned char)(f_a & 159);

      /*  Set the corresponding bit of the register depending on can_give_coins_back */
      if (((b_a & 1) != 0) && ((c_a & 2) != 0) && ((d_a & 4) != 0) && ((e_a & 8)
           != 0)) {
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function write_interface() */
        /*  Goal  : Define the interface layer writing data to external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*          - new_value: value to store in the register as an unsigned 8 bit */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        write_register(40963, (unsigned char)(register_value | 32));
      } else {
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        /*  Function write_interface() */
        /*  Goal  : Define the interface layer writing data to external HW registers */
        /*  IN    : - register_address: address of the register in unsigned 16 bit */
        /*          - new_value: value to store in the register as an unsigned 8 bit */
        /*  IN/OUT: - */
        /*  OUT   : - */
        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        write_register(40963, (unsigned char)(register_value | 64));
      }

      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Interface layer definition for target dependent HW */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Function sleep_interface() */
      /*  Goal  : Define the interface layer to pause the system for an amount of time */
      /*  IN    : - duration: time duration in seconds */
      /*  IN/OUT: - */
      /*  OUT   : - */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      Sleep(10);

      /*  Sleep asks milliseconds as input */
      /*  Pause the process */
      /*  Check if the master switch is switched off */
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
      g_a = read_register(40976);
      if ((g_a & 4) == 0) {
        master_switch_off = true;
        exitg3 = 1;
      } else {
        /*  The process of a ticket purchase has been initiated */
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
        h_a = read_register(40976);
        if ((h_a & 1) != 0) {
          exitg3 = 1;
        }
      }
    } while (exitg3 == 0);

    /*  Exit the program properly if the master switch is off */
    if (master_switch_off) {
      exitg2 = 1;
    } else {
      /*  Open the coin's flap to let the user inserting coins */
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
      i_a = read_register(40963);

      /*  Set the corresponding bit of the register depending on flap_open */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Function write_interface() */
      /*  Goal  : Define the interface layer writing data to external HW registers */
      /*  IN    : - register_address: address of the register in unsigned 16 bit */
      /*          - new_value: value to store in the register as an unsigned 8 bit */
      /*  IN/OUT: - */
      /*  OUT   : - */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      write_register(40963, (unsigned char)(i_a | 128));

      /*  Go through the entire ticket purchase process */
      /*  Local variable declarations */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      /*  Function handle_ticket_purchase() */
      /*  Goal  : higher abstraction level of the ticket purchase process */
      /*  IN    : - const_obj: constants object used in the entire application */
      /*  IN/OUT: - */
      /*  OUT   : - */
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      inserted_amount = 0U;
      b_register_value = 0U;

      /*  Waiting for the full payment of the ticket or cancellation of the purchase */
      do {
        exitg1 = 0;
        if (inserted_amount < 120) {
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Interface layer definition for target dependent HW */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Sleep(10);

          /*  Sleep asks milliseconds as input */
          /*  Pause the process */
          /*  Update the display with the current amount of money to insert */
          display_cents_value((unsigned short)(120 - inserted_amount));

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
          k_a = read_register(40976);
          if ((k_a & 2) != 0) {
            /*  Ticket's purchase process canceled */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function return_coins() */
            /*  Goal  : give back the desired amount of coins to the user */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - desired_amount: integer representing the money to give back */
            /*  IN/OUT: - */
            /*  OUT   : - */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Return as much as possible higher coin's values at first */
            remaining_amount = return_coin_value(inserted_amount, 100U);
            remaining_amount = return_coin_value(remaining_amount, 50U);
            remaining_amount = return_coin_value(remaining_amount, 20U);
            return_coin_value(remaining_amount, 10U);
            exitg1 = 1;
          } else {
            /*  Update the amount of money to pay if a coin has been inserted */
            d_register_value = b_register_value;

            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Function amount_inserted_coins() */
            /*  Goal  : get the amount of the inserted coins */
            /*  IN    : - const_obj: constants object used in the entire application */
            /*          - integer representing the current amount of inserted coins */
            /*  IN/OUT: - */
            /*  OUT   : - integer representing the updated amount of inserted coins */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            temp_amount = 0U;

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
            if (new_reg_value != b_register_value) {
              /*  Update the amount of coins already inserted */
              if (((new_reg_value & 1) != 0) && ((b_register_value & 1) == 0)) {
                temp_amount = 10U;
              } else if (((new_reg_value & 2) != 0) && ((b_register_value & 2) ==
                          0)) {
                temp_amount = 20U;
              } else if (((new_reg_value & 4) != 0) && ((b_register_value & 4) ==
                          0)) {
                temp_amount = 50U;
              } else if (((new_reg_value & 8) != 0) && ((b_register_value & 8) ==
                          0)) {
                temp_amount = 100U;
              } else {
                if (((new_reg_value & 16) != 0) && ((b_register_value & 16) == 0))
                {
                  temp_amount = 200U;
                }
              }

              /*  Record of the current register value */
              d_register_value = new_reg_value;
            }

            b_register_value = d_register_value;
            inserted_amount += temp_amount;
          }
        } else {
          /*  Printing of the parking ticket */
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
          j_a = read_register(40963);

          /*  Set the selected bit to '1' and write the new value to the register */
          c_register_value = (unsigned char)(j_a | 16);

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
          /*  Interface layer definition for target dependent HW */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Sleep(250);

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
          /*  Interface layer definition for target dependent HW */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Sleep(250);

          /*  Sleep asks milliseconds as input */
          /*  Give back coin's change */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function return_coins() */
          /*  Goal  : give back the desired amount of coins to the user */
          /*  IN    : - const_obj: constants object used in the entire application */
          /*          - desired_amount: integer representing the money to give back */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Return as much as possible higher coin's values at first */
          b_remaining_amount = return_coin_value((unsigned short)
            (inserted_amount - 120), 100U);
          b_remaining_amount = return_coin_value(b_remaining_amount, 50U);
          b_remaining_amount = return_coin_value(b_remaining_amount, 20U);
          return_coin_value(b_remaining_amount, 10U);
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  } while (exitg2 == 0);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void parkingMeterLowLevel(void)
{
  int b;
  int b_data;
  int b_i;
  int b_nb_input_types;
  int c_nb_input_types;
  int choice;
  int d_nb_input_types;
  int data;
  int exitg1;
  int exitg2;
  int i;
  int nb_input_types;
  int state;
  unsigned char a;
  unsigned char b_a;
  unsigned char b_register_value;
  char b_terminator;
  unsigned char c_register_value;
  char c_terminator;
  char d_terminator;
  unsigned char register_value;
  char terminator;
  unsigned char validatedHoleFilling_idx_0;
  bool b_bool;
  bool c_bool;
  bool d_bool;
  bool e_bool;
  bool guard1 = false;
  if (!isInitialized_parkingMeterLowLevel) {
    parkingMeterLowLevel_initialize();
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Function parkingMeterLowLevel() */
  /*  Goal  : Main entry point of the parking meter application */
  /*  IN    : - */
  /*  IN/OUT: - */
  /*  OUT   : - error_flag: error code */
  /*  */
  /*  Author: Sebastien Dupertuis */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Interface layer initialization */
  /*  Include the needed headers and sources files */
  if (TEST_MODE == 0) {
    /*  Instantiate all constants for the normal application */
    /*  Force the master switch register value to 'on' to avoid direct shutdown */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Function write_interface() */
    /*  Goal  : Define the interface layer writing data to external HW registers */
    /*  IN    : - register_address: address of the register in unsigned 16 bit */
    /*          - new_value: value to store in the register as an unsigned 8 bit */
    /*  IN/OUT: - */
    /*  OUT   : - */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    write_register(40976, 4);
    printf("The normal mode of operation of the parking meter has been activated.\n");
    fflush(stdout);
    printf("Feel free to purchase tickets.\n");
    fflush(stdout);
    standard_operation_mode();
    printf("The Master Switch of the Parking Meter Interface is switched off.\n");
    fflush(stdout);
    printf("Press \'ENTER\' to close the console window...\n");
    fflush(stdout);
    if (pauseState == 0) {
      getchar();
    }
  } else {
    /*  TEST_MODE == 1 */
    /*  Function handler API to access functions of the test mode */
    /*  Instantiate all properties and methods for the test mode */
    /*  Entry point of the test mode */
    /*  Text constant declaration */
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
          nb_input_types = scanf_s("%d%c", &choice, &terminator, 1);

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
            /*  Clear the input buffer */
            scanf_s("%*[^\n]%*1[\n]");
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
            b_nb_input_types = scanf_s("%d%c", &state, &b_terminator, 1);

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
              /*  Clear the input buffer */
              scanf_s("%*[^\n]%*1[\n]");
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
          /*  Interface layer definition for target dependent HW */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Sleep(250);

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
          /*  Interface layer definition for target dependent HW */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          /*  Function sleep_interface() */
          /*  Goal  : Define the interface layer to pause the system for an amount of time */
          /*  IN    : - duration: time duration in seconds */
          /*  IN/OUT: - */
          /*  OUT   : - */
          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Sleep(250);

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
            c_nb_input_types = scanf_s("%d%c", &data, &c_terminator, 1);

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
              /*  Clear the input buffer */
              scanf_s("%*[^\n]%*1[\n]");
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
            d_nb_input_types = scanf_s("%d%c", &b, &d_terminator, 1);

            /*  Check if the provided data is an integer number */
            guard1 = false;
            if (d_nb_input_types == 2) {
              e_bool = !(d_terminator != '\x0a');
              if (e_bool) {
                /*  Check if the value is within the allowed range */
                if ((b >= 1) && (b <= 100)) {
                  exitg2 = 1;
                } else {
                  printf("The value provided must be between %d and %d!\n", 1,
                         100);
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
              /*  Clear the input buffer */
              scanf_s("%*[^\n]%*1[\n]");
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
            printf("Elapsed time   : %3.1f\n", (float)rt_roundd((double)((b_i +
                      1) * 100) / 1000.0));
            fflush(stdout);

            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            /*  Interface layer definition for target dependent HW */
            /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
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
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void parkingMeterLowLevel_initialize(void)
{
  TEST_MODE = 0;
  cpause_init();
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
