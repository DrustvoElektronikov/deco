

/**
  sequencer.c - plays music, blink leds
	
	*/
	
#include "stm32f0xx.h"                  // Device header
	
	
extern TIM_HandleTypeDef htim14;

	
void Sequencer_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim14);
}


/**
   * @brief This function initializes and start the sequence processor 
   * @param None
   * @param None
   * @retval None
   */
void Sequencer_start(void)
{


}


/**
   * @brief Stop Sequence generator 
   * @param None
   * @param None
   * @retval None
   */
void Sequencer_stop(void)
{
}




void Sequencer(void)
{
	
	
}

