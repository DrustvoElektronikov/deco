#include "stm32f0xx.h"                  // Device header
#include "leds.h"

#define LED_PORT_INIT(PORT, PIN) \
					(PORT)->MODER   &= ~(3ul << 2*(PIN)); \
					(PORT)->MODER   |=  (1ul << 2*(PIN)); \
					(PORT)->OTYPER  &= ~(1ul <<   (PIN)); \
					(PORT)->OSPEEDR &= ~(3ul << 2*(PIN)); \
					(PORT)->OSPEEDR |=  (1ul << 2*(PIN)); \
					(PORT)->PUPDR   &= ~(3ul << 2*(PIN)); 



void LEDS_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  /* Enable GPIOA clock         */
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;  /* Enable GPIOB clock         */
  RCC->AHBENR |= RCC_AHBENR_GPIOFEN;  /* Enable GPIOF clock         */

		/* All pins push-pull, no pullup */

	LED_PORT_INIT (LEDR0_PORT, LEDR0_PINn);
	LED_PORT_INIT (LEDR1_PORT, LEDR1_PINn);
	LED_PORT_INIT (LEDR2_PORT, LEDR2_PINn);
	LED_PORT_INIT (LEDR3_PORT, LEDR3_PINn);
	LED_PORT_INIT (LEDC0_PORT, LEDC0_PINn);
	LED_PORT_INIT (LEDC1_PORT, LEDC1_PINn);
	LED_PORT_INIT (LEDC2_PORT, LEDC2_PINn);
	LED_PORT_INIT (LEDC3_PORT, LEDC3_PINn);
	
}

void LEDS_SetRow(uint8_t dat)
{
	LEDR3_PORT->BSRR = LEDR3_PIN<<((dat & 0x08) ? 0 : 16);
	LEDR2_PORT->BSRR = LEDR2_PIN<<((dat & 0x04) ? 0 : 16);
	LEDR1_PORT->BSRR = LEDR1_PIN<<((dat & 0x02) ? 0 : 16);
	LEDR0_PORT->BSRR = LEDR0_PIN<<((dat & 0x01) ? 0 : 16);
}

void LEDS_SetCol(uint8_t dat)
{
	LEDC3_PORT->BSRR = LEDC3_PIN<<((dat & 0x08) ? 0 : 16); 
	LEDC2_PORT->BSRR = LEDC2_PIN<<((dat & 0x04) ? 0 : 16);
	LEDC1_PORT->BSRR = LEDC1_PIN<<((dat & 0x02) ? 0 : 16);
	LEDC0_PORT->BSRR = LEDC0_PIN<<((dat & 0x01) ? 0 : 16);
}


void LEDS_Test(uint8_t r, uint8_t c)
{
	LEDS_SetRow(r);
	LEDS_SetCol(c);
}

