


#ifndef __LED_H__
#define __LED_H__
#include "stm32f0xx.h"                  // Device header

typedef struct
{
	GPIO_TypeDef 		*port;
	uint16_t				pin;
} LED_conf_t;




void LED_Init(void);
void LED_set(uint8_t led);

#endif

