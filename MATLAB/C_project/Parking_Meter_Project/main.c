/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 26-Oct-2018 10:53:24
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "ParkingMeterLowLevel.h"
#include "main.h"

/* Function Declarations */
static void main_ParkingMeterLowLevel(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_ParkingMeterLowLevel(void)
{
  /* Call the entry-point 'ParkingMeterLowLevel'. */
  ParkingMeterLowLevel();
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  ParkingMeterLowLevel_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_ParkingMeterLowLevel();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
