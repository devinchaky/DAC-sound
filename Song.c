// Song.c
// Lab 6 Extra credit 1) 
// playing your favorite song.
//
// For use with the TM4C123
// ECE319K lab6 extra credit 1)
// Program written by: Devin Chaky
// 2/20/23

#include "Sound.h"
#include "../inc/DAC.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Timer3A_Init(void(*task)(void), uint32_t period, uint32_t priority);
void Timer3A_Stop(void);
void Song_Play(void);

// array of notes - twinkle little star
const uint16_t Star[42] = {
	2389, 2389, 3189, 3189, 2841, 2841, 3189, 
	3579, 3579, 3792, 3792, 4257, 4257, 2389,
	3189, 3189, 3579, 3579, 3792, 3792, 4257,
	3189, 3189, 3579, 3579, 3792, 3792, 4257,
	2389, 2389, 3189, 3189, 2841, 2841, 3189,
	3579, 3579, 3792, 3792, 4257, 4257, 2389
};

// array of notes happy birthday
const uint16_t Bday[25]= {
	4778, 4778, 4257, 4778, 3579, 3792,
	4778, 4778, 4257, 4778, 3189, 3579,
	4778, 4778, 2389, 2841, 3189, 3792, 4257,
	2681, 2681, 2841, 3579, 3189, 3579
};

// array of notes mario cart theme
const uint16_t Mario[183] = {
	948, 948, 948, 1194, 948, 797, 1594, 1194,
	1594, 1896, 1420, 1265, 1341, 1420, 1594, 948, 
	797, 710, 895, 797, 948, 1194, 1064, 1341, 
	1194, 1594, 1896, 1420, 1265, 1341, 1420, 895,  
	797, 948, 1194, 1064, 1265, 797, 845, 895, 
	1064, 948, 1594, 1420, 1194, 1420, 1194, 1064,
	797, 845, 895, 1064, 948, 797, 845, 895, 
	1064, 948, 1594, 1420, 1194, 1420, 1194, 1064,
	1004, 1064, 1194, 1194, 1194, 1194, 1194, 1064, 
	948, 1194, 1420, 1594, 1194, 1194, 1194, 1194, 
	1064, 948, 1194, 1194, 1194, 1194, 1064, 948, 
	1194, 1420, 1594, 948, 948, 948, 1194, 948, 
	797, 1594, 1194, 1594, 1896, 1420, 1265, 1341, 
	1420, 1594, 948, 797, 710, 895, 979, 948, 
	1194, 1064, 1265, 1194, 1594, 1896, 1420, 1265, 
	1341, 1420, 1594, 948, 797, 710, 895, 979, 
	948, 1194, 1064, 1265, 948, 1194, 1594, 1594, 
	1420,895, 895, 1420, 1265, 710, 710, 710, 
	797, 895, 948, 1194, 1420, 1594, 948, 1194, 
	1594, 1594, 1420,895, 895, 1420, 1265, 895, 
	895, 895, 948, 1064, 1194, 1594, 1896, 2389,
	1194, 1594, 1896, 1194, 1594, 1896, 1420, 1265, 
	1420, 1505, 1341, 1505, 1594, 1689, 1594		
};

uint8_t index;	// init index var for movcing through notes

// initialize interrupts for song
// use timer3 as slower intterrupt that
// changes note
void Song_Init(void){
  // extra credit 1)
	index = 0;
	EnableInterrupts();
	Timer3A_Init(Song_Play, 33321450, 2);
}

// Play song, while button pushed or until end
// used to iterate through array of notes
// and play song
void Song_Play(void){
  // extra credit 1)
	Sound_Start(Bday[index]);	// call sound func with period of note from array
	index = (index+1)%25;	// move to next note in array
}

// Stop song
void Song_Stop(void){
 // if needed
	Timer3A_Stop();	
	DisableInterrupts();	// disable interrupts to stop song
}

