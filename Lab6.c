// Lab6.c
// Runs on TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// EE319K lab6 starter
// Program written by: Devin Chaky
// Date Created: 1/4/23 
// Last Modified: 2/20/23  
// Lab number: 6
// Hardware connections
// Input: Switches on PA5-2 Output: 6-bit DAC with PB5-0
// song swtich on PA6

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Key.h"
#include "Song.h"
#include "../inc/wave.h"
#include "Lab6Grader.h"
// put both EIDs in the next two lines
char EID1[] = "ab77762"; //  ;replace abc123 with your EID
char EID2[] = "dmc4627"; //  ;replace abc123 with your EID

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);
void DAC_Init(void);          // your lab 6 solution
void DAC_Out(uint8_t data);   // your lab 6 solution
uint8_t Testdata;

// array with note frequencies
const uint32_t Notes[9] = {0,4257,3378,0,2841,0,0,0,2531};

// lab video Lab6_voltmeter
// use this if you have a voltmeter
// 1) connect voltmeter to DACOUT 
// 2) add a breakpoint at i+1
// 3) run and record voltage for each input value
const uint32_t Inputs[16]={0,1,7,8,15,16,17,18,31,32,33,47,48,49,62,63};
int voltmetermain(void){ uint32_t i;  
  DisableInterrupts();
  TExaS_Init(SCOPE);    
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  i = 0;
  EnableInterrupts();
  while(1){                
    Testdata = Inputs[i];
    DAC_Out(Testdata); // your lab 6 solution
    i=(i+1)&0x0F;  // <---put a breakpoint here
  }
}
// DelayMs
//  - busy wait n milliseconds
// Input: time to wait in msec
// Outputs: none
void static DelayMs(uint32_t n){
  volatile uint32_t time;
  while(n){
    time = 6665;  // 1msec, tuned at 80 MHz
    while(time){
      time--;
    }
    n--;
  }
}

// Heartbeat Initialization
// - initialize ports for heartbeat debugger
// Input: none 
// Output: none
void Heartbeat_Init(void){
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x20;
	delay = SYSCTL_RCGCGPIO_R;
	
	GPIO_PORTF_DIR_R |= 0x08;
	GPIO_PORTF_DEN_R |= 0x08;
}

// lab video Lab6_static
// use this if you DO NOT have a voltmeter
// you need to implement LaunchPad_Init and LaunchPad_Input
// Connect PD3 to your DACOUT and observe the voltage using TExaSdisplay in scope mode.
int staticmain(void){  
  uint32_t last,now,i;  
  TExaS_Init(SCOPE);    // bus clock at 80 MHz
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  i = 0;
  EnableInterrupts();
  last = LaunchPad_Input();
  while(1){                
    now = LaunchPad_Input();
    if((last != now)&&now){
      Testdata = Inputs[i];
      DAC_Out(Testdata); // your lab 6 solution
      i=(i+1)&0x0F;
    }
    last = now;
    DelayMs(25);   // debounces switch
  }
}

     
int main(void){       
  DisableInterrupts();
  TExaS_Init(REALBOARDGRADER);    // bus clock at 80 MHz
//    SCOPE,
//    LOGICANALYZERA,
//    LOGICANALYZERB,
//    LOGICANALYZERC,
//    LOGICANALYZERE,
//    REALBOARDGRADER,
//    SIMULATIONGRADER,
//    NONE
  Key_Init();
//  LaunchPad_Init(); // if needed
  Sound_Init();
	Heartbeat_Init();
//  Song_Init(); // extra credit 1)
//  Wave_Init(); // extra credit 2)
  uint32_t input;
	uint32_t previous = 0;
	uint32_t count = 0;
  while(1){
		
		input = Key_In();
		// if song key pressed, play song
		if(input == 20){
			Song_Init();
			while(Key_In() == 20){
				WaitForInterrupt();
			}
			Song_Stop();
		}
		
		if(input&&(previous==0)){	// just pressed
			Sound_Start(Notes[input]);	// play note frequency
		}
		if(previous&&(input==0)){	// just released
			Sound_Off();	//stop sound
		}
		previous = input;
		DelayMs(10); // remove swtich bounce
		count++;
		if (count == 100){
			GPIO_PORTF_DATA_R ^= 0x08; // toggle heartbeat LED
			count = 0;
		}
  }             
}


