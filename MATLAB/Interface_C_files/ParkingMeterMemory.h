/*******************************************************************************
* Shared memory access file
* Goal   : Simulation of the parking meter hardware registers access.
*          The access in read and writes modes is done via a dynamically
*          allocated shared memory that allows the graphical App to communicate
*          with the C console program.
*          This file must be included in the C console program to have the full
*          system working properly: #include "ParkingMeterMemory.h"
*
* Copyright 2023 The MathWorks, Inc.
*******************************************************************************/
#ifndef PARKING_METER_MEMORY_H_ /* Include guard */
#define PARKING_METER_MEMORY_H_

/* Packages to include */
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

/* Constants definition */
#define BUFFER_SIZE 65536

/* Global variables */
static volatile char * sharedMemoryAddress = NULL;

/* Functions declaration */
/*******************************************************************************
* Function read_register()
* Goal  : Get the current value of the desire HW register address that is mapped
*         on top of the offset address of the shared memory location
* IN    : - address of the register in unsigned 16 bit
* IN/OUT: -
* OUT   : - value stored in the register as an unsigned 8 bit
*******************************************************************************/
unsigned char read_register(unsigned short address);

/*******************************************************************************
* Function write_register()
* Goal  : Write the current value to the desire HW register address
* IN    : - value to store in the register as an unsigned 8 bit
* IN/OUT: - address of the register in unsigned 16 bit
* OUT   : -
*******************************************************************************/
void write_register(unsigned short address, unsigned char value);

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
int open_shared_memory_read();
int open_shared_memory_write();

#endif /* PARKING_METER_MEMORY_H_ */
