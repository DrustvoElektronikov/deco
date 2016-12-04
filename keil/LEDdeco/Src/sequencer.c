

/**
  sequencer.c - plays music, blink leds
	
	*/
	
#include "stm32f0xx.h"                  // Device header
#include "sequencer.h"
#include "led.h"
#include "audio.h" 


extern TIM_HandleTypeDef htim14;


const LED_CMD_t Program[] //__attribute__((at(FLASH_STORE_ADR)))   
={ 
#include "LED_prg.h"	
} ;

#define PROG_LEN (sizeof (Program) / sizeof (Program [0]))


static uint16_t 	ProgramCounter = 0;			// Program counter
static int16_t    pauser = 0; // pausing counter

	
void Sequencer_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim14);
	ProgramCounter = 0;

}


/**
   * @brief This function initializes and start the sequence processor 
   * @param None
   * @param None
   * @retval None
   */
void Sequencer_start(void)
{
  ProgramCounter = 0;

}


/**
   * @brief Stop Sequence generator 
   * @param None
   * @param None
   * @retval None
   */
void Sequencer_stop(void)
{
	ProgramCounter = 0xffff;
}




void Sequencer(void)
{
	if (ProgramCounter < PROG_LEN)
	{
		switch (Program[ProgramCounter].f.CMD)
		{
			case CMD_LED : 
				LED_set(Program[ProgramCounter].f.PAR); 
			  ProgramCounter++;
			break;
			
			case CMD_SOUND : 
				Audio_PlayMidiNote(Program[ProgramCounter].f.PAR);
			  ProgramCounter++;
			break;
			
			case CMD_MPAUSE :
			case CMD_SPAUSE :
				if (pauser == -1)  // not setup yet
				{
					if (Program[ProgramCounter].f.CMD == CMD_MPAUSE) 
						pauser = Program[ProgramCounter].f.PAR; // milliseconds
					else
						pauser = 100 * Program[ProgramCounter].f.PAR; // 1/10 s
				}
				else
				{
					if (pauser > 0) // not 0 yet, just decrement
					{
						pauser--;
					}
					else // reached 0
					{
						pauser = -1;
						ProgramCounter++;
					}
				}
				
			break;
			
			case CMD_FADE :
				LED_SetFader(Program[ProgramCounter].f.PAR);
			  ProgramCounter++;
			break;
			
			case CMD_VOL : 
				Audio_Volume(Program[ProgramCounter].f.PAR);
			  ProgramCounter++;
			break;
			
			case CMD_REMOTE :
				ProgramCounter++;  // not implemented yet
			break;
			
			case CMD_RESTART :
				ProgramCounter = 0;
			break;
			
		}
	}
	
}

