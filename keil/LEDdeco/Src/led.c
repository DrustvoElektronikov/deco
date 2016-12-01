/*
 *  LED driver
 *

	
				This is free and unencumbered software released into the public domain.

			Anyone is free to copy, modify, publish, use, compile, sell, or
			distribute this software, either in source code form or as a compiled
			binary, for any purpose, commercial or non-commercial, and by any
			means.

			In jurisdictions that recognize copyright laws, the author or authors
			of this software dedicate any and all copyright interest in the
			software to the public domain. We make this dedication for the benefit
			of the public at large and to the detriment of our heirs and
			successors. We intend this dedication to be an overt act of
			relinquishment in perpetuity of all present and future rights to this
			software under copyright law.

			THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
			EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
			MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
			IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
			OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
			ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
			OTHER DEALINGS IN THE SOFTWARE.

			For more information, please refer to <http://unlicense.org>
			

 *
 */
 
#include "stm32f0xx.h"                  // Device header
#include "led.h"


/****************************************************
LED pinout configuration 
-----------------------------------------------------*/
LED_conf_t LED_conf[8] =
{  {GPIOA, GPIO_PIN_0},
	 {GPIOA, GPIO_PIN_1},
	 {GPIOA, GPIO_PIN_4},
	 {GPIOA, GPIO_PIN_5},
	 {GPIOA, GPIO_PIN_7},
	 {GPIOB, GPIO_PIN_1},
	 {GPIOF, GPIO_PIN_0},
	 {GPIOF, GPIO_PIN_1},
};



/** Configure LED pins as 
        * OD Output, no Pullups
*/
void LED_Init(void)
{
  int i;
  GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_TypeDef *p;


  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	for (i=0; i<8; i++)
	{
		/*Configure GPIO pins */
		GPIO_InitStruct.Pin = LED_conf[i].pin;
		p = LED_conf[i].port;
		HAL_GPIO_Init(p, &GPIO_InitStruct);	
		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(p, GPIO_InitStruct.Pin, GPIO_PIN_SET);		
	}
}

 


void LED_set(uint8_t led)
{
	uint8_t b = 0x01;
	int i;
	
	for (i=0; i<8; i++)
	{
		HAL_GPIO_WritePin(LED_conf[i].port, LED_conf[i].pin, ((led & b) == b) ? GPIO_PIN_RESET : GPIO_PIN_SET);
		b<<=1;
	}
}
 
 
