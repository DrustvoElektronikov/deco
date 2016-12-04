/**
  ******************************************************************************
  * @file    sequencer.h
  * @brief   Sequencer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 S54MTB</center></h2>
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SEQ_H__
#define __SEQ_H__

#include "stm32f0xx.h"                  // Device header

/** 
         __  __     __  __                       __   __ 
    |   |_  |  \   /   /  \ |\/| |\/|  /\  |\ | |  \ (_  
    |__ |__ |__/   \__ \__/ |  | |  | /--\ | \| |__/ __) 
                                                         
*/

#define MAX_PROGRAM_LEN 128
#define FLASH_STORE_ADR      0x8007800


#define 	CMD_LED  			0x1			// set led
#define 	CMD_SOUND  		0x2			// play sound
#define 	CMD_VOL	  		0x3			// sound volume
#define 	CMD_MPAUSE 		0x4			// pause in ms
#define 	CMD_SPAUSE 		0x5			// pause in 1/10 second unit
#define 	CMD_FADE  		0x6			// set LED fading rate
#define 	CMD_REMOTE 	 	0x7			// send remote command
#define 	CMD_RESTART  	0xf			// end of program, restart


typedef union
{
	struct
	{
		uint16_t	CMD					:4;				/* Command is 4 bits long */
		uint16_t 	PAR					:12;      /* 12 bit parameter */
	} f;
  uint16_t c;
} LED_CMD_t;


void Sequencer(void);
void Sequencer_Init(void);
void Sequencer_start(void);
void Sequencer_stop(void);



/** NOTES */
#define N_C2 {CMD_SOUND, 24}
#define N_CS2 {CMD_SOUND, 25}
#define N_D2 {CMD_SOUND, 26}
#define N_DS2 {CMD_SOUND, 27}
#define N_E2 {CMD_SOUND, 28}
#define N_F2 {CMD_SOUND, 29}
#define N_FS2 {CMD_SOUND, 30}
#define N_G2 {CMD_SOUND, 31}
#define N_GS2 {CMD_SOUND, 32}
#define N_A2 {CMD_SOUND, 33}
#define N_AS2 {CMD_SOUND, 34}
#define N_B2 {CMD_SOUND, 35}
#define N_C3 {CMD_SOUND, 36}
#define N_CS3 {CMD_SOUND, 37}
#define N_D3 {CMD_SOUND, 38}
#define N_DS3 {CMD_SOUND, 39}
#define N_E3 {CMD_SOUND, 40}
#define N_F3 {CMD_SOUND, 41}
#define N_FS3 {CMD_SOUND, 42}
#define N_G3 {CMD_SOUND, 43}
#define N_GS3 {CMD_SOUND, 44}
#define N_A3 {CMD_SOUND, 45}
#define N_AS3 {CMD_SOUND, 46}
#define N_B3 {CMD_SOUND, 47}
#define N_C4 {CMD_SOUND, 48}
#define N_CS4 {CMD_SOUND, 49}
#define N_D4 {CMD_SOUND, 50}
#define N_DS4 {CMD_SOUND, 51}
#define N_E4 {CMD_SOUND, 52}
#define N_F4 {CMD_SOUND, 53}
#define N_FS4 {CMD_SOUND, 54}
#define N_G4 {CMD_SOUND, 55}
#define N_GS4 {CMD_SOUND, 56}
#define N_A4 {CMD_SOUND, 57}
#define N_AS4 {CMD_SOUND, 58}
#define N_B4 {CMD_SOUND, 59}
#define N_C5 {CMD_SOUND, 60}
#define N_CS5 {CMD_SOUND, 61}
#define N_D5 {CMD_SOUND, 62}
#define N_DS5 {CMD_SOUND, 63}
#define N_E5 {CMD_SOUND, 64}
#define N_F5 {CMD_SOUND, 65}
#define N_FS5 {CMD_SOUND, 66}
#define N_G5 {CMD_SOUND, 67}
#define N_GS5 {CMD_SOUND, 68}
#define N_A5 {CMD_SOUND, 69}
#define N_AS5 {CMD_SOUND, 70}
#define N_B5 {CMD_SOUND, 71}
#define N_C6 {CMD_SOUND, 72}
#define N_CS6 {CMD_SOUND, 73}
#define N_D6 {CMD_SOUND, 74}
#define N_DS6 {CMD_SOUND, 75}
#define N_E6 {CMD_SOUND, 76}
#define N_F6 {CMD_SOUND, 77}
#define N_FS6 {CMD_SOUND, 78}
#define N_G6 {CMD_SOUND, 79}
#define N_GS6 {CMD_SOUND, 80}
#define N_A6 {CMD_SOUND, 81}
#define N_AS6 {CMD_SOUND, 82}
#define N_B6 {CMD_SOUND, 83}
#define N_C7 {CMD_SOUND, 84}
#define N_CS7 {CMD_SOUND, 85}
#define N_D7 {CMD_SOUND, 86}
#define N_DS7 {CMD_SOUND, 87}
#define N_E7 {CMD_SOUND, 88}
#define N_F7 {CMD_SOUND, 89}
#define N_FS7 {CMD_SOUND, 90}
#define N_G7 {CMD_SOUND, 91}
#define N_GS7 {CMD_SOUND, 92}
#define N_A7 {CMD_SOUND, 93}
#define N_AS7 {CMD_SOUND, 94}
#define N_B7 {CMD_SOUND, 95}
#define N_C8 {CMD_SOUND, 96}
#define N_CS8 {CMD_SOUND, 97}
#define N_D8 {CMD_SOUND, 98}
#define N_DS8 {CMD_SOUND, 99}
#define N_E8 {CMD_SOUND, 100}
#define N_F8 {CMD_SOUND, 101}
#define N_FS8 {CMD_SOUND, 102}
#define N_G8 {CMD_SOUND, 103}
#define N_GS8 {CMD_SOUND, 104}
#define N_A8 {CMD_SOUND, 105}
#define N_AS8 {CMD_SOUND, 106}
#define N_B8 {CMD_SOUND, 107}
#define N_C9 {CMD_SOUND, 108}
#define N_CS9 {CMD_SOUND, 109}
#define N_D9 {CMD_SOUND, 110}
#define N_DS9 {CMD_SOUND, 111}
#define N_E9 {CMD_SOUND, 112}
#define N_F9 {CMD_SOUND, 113}
#define N_FS9 {CMD_SOUND, 114}
#define N_G9 {CMD_SOUND, 115}
#define N_GS9 {CMD_SOUND, 116}
#define N_A9 {CMD_SOUND, 117}
#define N_AS9 {CMD_SOUND, 118}
#define N_B9 {CMD_SOUND, 119}
#define N_C10 {CMD_SOUND, 120}
#define N_CS10 {CMD_SOUND, 121}
#define N_D10 {CMD_SOUND, 122}
#define N_DS10 {CMD_SOUND, 123}
#define N_E10 {CMD_SOUND, 124}
#define N_F10 {CMD_SOUND, 125}
#define N_FS10 {CMD_SOUND, 126}
#define N_G10 {CMD_SOUND, 127}

#define N_REST {CMD_SOUND, 0}

#endif /* __SEQ_H__ */

/************************ (C) COPYRIGHT S54MTB *****END OF FILE****/



