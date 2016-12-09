#ifndef __LEDS_H__
#define __LEDS_H__

#define LEDR0_PORT     GPIOA
#define LEDR0_PINn     7
#define LEDR1_PORT     GPIOB
#define LEDR1_PINn     1
#define LEDR2_PORT     GPIOA
#define LEDR2_PINn     1
#define LEDR3_PORT     GPIOF
#define LEDR3_PINn     1

#define LEDC0_PORT     GPIOA
#define LEDC0_PINn     5
#define LEDC1_PORT     GPIOF
#define LEDC1_PINn     0
#define LEDC2_PORT     GPIOA
#define LEDC2_PINn     0
#define LEDC3_PORT     GPIOA
#define LEDC3_PINn     4


#define LEDR0_PIN		((uint16_t)(1U<<LEDR0_PINn))
#define LEDR1_PIN		((uint16_t)(1U<<LEDR1_PINn))
#define LEDR2_PIN		((uint16_t)(1U<<LEDR2_PINn))
#define LEDR3_PIN		((uint16_t)(1U<<LEDR3_PINn))

#define LEDC0_PIN		((uint16_t)(1U<<LEDC0_PINn))
#define LEDC1_PIN		((uint16_t)(1U<<LEDC1_PINn))
#define LEDC2_PIN		((uint16_t)(1U<<LEDC2_PINn))
#define LEDC3_PIN		((uint16_t)(1U<<LEDC3_PINn))


void LEDS_Init(void);

#endif


