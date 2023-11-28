/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'ParkingMeterSystem'.
 *
 * Model version                  : 1.505
 * Simulink Coder version         : 9.1 (R2019a) 06-Feb-2019
 * C/C++ source code generated on : Tue Jun 19 16:46:24 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                   /* This ert_main.c example uses printf/fflush */
#include "ParkingMeterSystem.h"      /* Model's header file */
#include "rtwtypes.h"
#include <time.h>

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(ParkingMeterSystem_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  ReadAccessToButtonsRegister_D1();
  ReadAccessToInsertedCoinsRegister_D1();
  WriteAccesToPeripheralsPulseGeneration_D1();
  WriteAccesToDisplaysRegisters_D1();
  WriteAccesToPeripheralsFlap_D1();
  WriteAccesToAvailableCoinsRegister_D1();
  TerminateExecution_D1();
  SchedulerToAccessTheSharedMemory_D1();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  /* CPU time */
  clock_t start_t;

  /* Initialize model */
  ParkingMeterSystem_initialize();
  printf("The entire system project has been built and is running forever...\n");
  fflush((NULL));

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.001 seconds (the model's base sample time) here
   */
  while (1) {
    start_t = clock();
    while((clock() - start_t) < 1) {}
	/* Run the Simulink model for one step */
	rt_OneStep();
  }

  /* Disable rt_OneStep() here */
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
