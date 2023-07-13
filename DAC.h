// DAC.h
// This software configures DAC output
// Lab 6 requires a minimum of 6 bits for the DAC, but you could have 7 bits
// Runs on TM4C123
// Program written by: Devin Chaky
// Date Created: 1/4/23
// Last Modified: 2/20/23 
// Lab number: 6
// Hardware connections
// DAC output pins on PB5-0

#ifndef DAC_H
#define DAC_H
#include <stdint.h>
// Header files contain the prototypes for public functions
// this file explains what the module does

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void);


// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Input=n is converted to n*3.3V/63
// Output: none
void DAC_Out(uint8_t data);

#endif
