

#ifndef __FL_STORAGE_H__
#define __FL_STORAGE_H__

#include "stm32f0xx.h"                  // Device header


#define	CMD_LED  0x10		// Set LED
#define	CMD_AUD  0x20   // Set audio
#define	CMD_DLY  0x30		// Delay (do nothing)
#define CMD_TRA  0x40		// Transition mode

#define CMD_LEN								100
#define FLASH_STORE_ADR				0x8007c00



typedef struct 
{
	uint8_t cmd;
	uint8_t arg;
} CMD_t;
	



#endif

