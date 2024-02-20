/*******************************************************************************
* Shared memory access file
* Goal   : Simulation of the parking meter hardware registers access.
*          The access in read and writes modes is done via a dynamically
*          allocated shared memory that allows the graphical App to communicate
*          with the C console program.
*          The header file must be included in the C console program to have the
*          full system working properly: #include "ParkingMeterMemory.h"
*
* Copyright 2024 The MathWorks, Inc.
*******************************************************************************/

/* Packages to include */
#include "ParkingMeterMemory.h"

/* Constants definition */
TCHAR SHARED_MEMORY_NAME_WRITE[] = TEXT("ParkingMeter.SharedMemory");

/*******************************************************************************
* Function write_register()
* Goal  : Write the current value to the desire HW register address
* IN    : - value to store in the register as an unsigned 8 bit
*         - address of the register in unsigned 16 bit
* IN/OUT: -
* OUT   : -
*******************************************************************************/
void write_register(unsigned short address, unsigned char value)
{
  /* Access the shared memory area */
  if (open_shared_memory_write() == 0)
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
* Function open_shared_memory_write()
* Goal  : Creation of a memory-mapped file to share data between 2 processes
* IN    : -
* IN/OUT: -
* OUT   : - Error status in integer coded as following:
*          > 0 => No error occurred and the shared memory has been created
*          > 1 => The process could not create the memory-mapped file object
*          > 2 => The process could not return a pointer to the file view
*******************************************************************************/
int open_shared_memory_write()
{
  /* Definition of the handle to the memory-mapped file object */
  HANDLE hMappingFile;

  /* Create a new shared memory area if it does not exist yet */
  if (sharedMemoryAddress == NULL)
  {
    /* Creation of the file mapping object */
    hMappingFile = CreateFileMapping(
      INVALID_HANDLE_VALUE,      // use paging file
      NULL,                      // default security
      PAGE_READWRITE,            // read/write access
      0,                         // maximum object size (high-order DWORD)
      BUFFER_SIZE,               // maximum object size (low-order DWORD)
      SHARED_MEMORY_NAME_WRITE); // name of the mapping object
    /* Exception handling */
    if (hMappingFile == NULL)
    {
      /* The file mapping object could not have been created */
      _tprintf(TEXT("Could not create the shared memory called: %s\n"), SHARED_MEMORY_NAME_WRITE);
      return 1;
    }
    /* Create a view of the file in the process address space */
    sharedMemoryAddress = MapViewOfFile(hMappingFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    /* Exception handling */
    if (sharedMemoryAddress == NULL)
    {
      /* No pointer to the file view could have been returned */
      _tprintf(TEXT("Could not map the shared memory called: %s\n"), SHARED_MEMORY_NAME_WRITE);
      /* The process no longer needs access to the file mapping object */
      CloseHandle(hMappingFile);
      return 2;
    }
  }
  /* No error occurred */
  return 0;
}
