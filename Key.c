// Key.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 4 keys, but you could have more
// Runs on LM4F120 or TM4C123
// Program written by: Devin Chaky
// Date Created: 1/2/17 
// Last Modified: 2/20/23  
// Lab number: 6
// Hardware connections
// Input switches on PA5-2

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// **************Key_Init*********************
// Initialize piano key inputs on PA5-2 or PE3-0
// Input: none 
// Output: none
void Key_Init(void){ 
  // used in Lab 6 , initialize input pins
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x10;
	delay = SYSCTL_RCGCGPIO_R;
	
	GPIO_PORTE_DIR_R &= ~(0x0F);
	GPIO_PORTE_DEN_R |= 0x0F;
	
}
// **************Key_In*********************
// Input from piano key inputs on PA5-2 or PE3-0
// Input: none 
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
uint32_t Key_In(void){ 
  // write this
	uint32_t input;
	if((GPIO_PORTE_DATA_R & 0x40) == 0x40){
		return 20;
	}
	input = (GPIO_PORTE_DATA_R & 0x0F); // shift two places to make 0-15 value
  return input; // return input key value

  
}



