/*******************************************************************************
* Shared memory access file
* Goal     : Simulation of the parking meter hardware registers access.
*            The access in read and writes modes is done via a dynamically
*            allocated shared memory that allows the graphical App to
*            communicate with the C console program.
*            The header file must be included in the C console program to have
*            the full system working properly: #include "ParkingMeterMemory.h"
* MEX Build: Run this command to build the MEX:
* >> mex '..\MEX_functions\write_register.c' -outdir '..\MEX_functions'
*
* Copyright 2023 The MathWorks, Inc.
*******************************************************************************/

/* Packages to include */
#include "ParkingMeterMemory.h"
#include "mex.h"

/* Constants definition */
TCHAR SHARED_MEMORY_NAME[] = TEXT("ParkingMeter.SharedMemory");

/*******************************************************************************
* Function write_register()
* Goal  : Write the current value to the desire HW register address
* IN    : - value to store in the register as an unsigned 8 bit
* IN/OUT: - address of the register in unsigned 16 bit
* OUT   : -
*******************************************************************************/
void write_register(unsigned short address, unsigned char value)
{
  /* Access the shared memory area */
  if (open_shared_memory() == 0)
  {
    /* Set the new value in the desired register */
    *(sharedMemoryAddress + address) = value;
  }
  else
  {
    getchar();
    exit(EXIT_FAILURE);
  }
}

/*******************************************************************************
* Function open_shared_memory()
* Goal  : Creation of a memory-mapped file to share data between 2 processes
* IN    : -
* IN/OUT: -
* OUT   : - Error status in integer coded as following:
*          > 0 => No error occurred and the shared memory has been created
*          > 1 => The process could not create the memory-mapped file object
*          > 2 => The process could not return a pointer to the file view
*******************************************************************************/
int open_shared_memory()
{
  /* Definition of the handle to the memory-mapped file object */
  HANDLE hMappingFile;

  /* Create a new shared memory area if it does not exist yet */
  if (sharedMemoryAddress == NULL)
  {
    /* Creation of the file mapping object */
    hMappingFile = CreateFileMapping(
      INVALID_HANDLE_VALUE, // use paging file
      NULL,                 // default security
      PAGE_READWRITE,       // read/write access
      0,                    // maximum object size (high-order DWORD)
      BUFFER_SIZE,          // maximum object size (low-order DWORD)
      SHARED_MEMORY_NAME);  // name of the mapping object
    /* Exception handling */
    if (hMappingFile == NULL)
    {
      /* The file mapping object could not have been created */
      _tprintf(TEXT("Could not create the shared memory called: %s\n"), SHARED_MEMORY_NAME);
      return 1;
    }
    /* Create a view of the file in the process address space */
    sharedMemoryAddress = MapViewOfFile(hMappingFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    /* Exception handling */
    if (sharedMemoryAddress == NULL)
    {
      /* No pointer to the file view could have been returned */
      _tprintf(TEXT("Could not map the shared memory called: %s\n"), SHARED_MEMORY_NAME);
      /* The process no longer needs access to the file mapping object */
      CloseHandle(hMappingFile);
      return 2;
    }
  }
  /* No error occurred */
  return 0;
}

/*******************************************************************************
* Function mexFunction()
* Goal  : The gateway routine called mexFunction is the entry point to the MEX
*         file. It is through this routine that MATLAB accesses the rest of the
*         routines in the MEX files. It takes the place of the main function in
*         the source code.
* IN    : - nlhs: Number of left-side arguments, or the size of the plhs array
*         - plhs: Array of left-side output arguments
*         - nrhs: Number of right-side arguments, or the size of the prhs array
*         - prhs: Array of right-side input arguments
* IN/OUT: -
* OUT   : -
*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Declaration of local variables */
  unsigned short *register_address;
  unsigned char  *register_value;
  mwSignedIndex dims[2];

  /* Read input data */
  register_address = mxGetPr(prhs[0]);
  register_value   = mxGetPr(prhs[1]);

  /* Call of the C computational routine */
  write_register(*register_address, *register_value);
  return;
}
