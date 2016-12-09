#include "stm32f0xx.h"                  // Device header
#include "leds.h"
#include <stdlib.h>


extern void LEDS_Test(uint8_t r, uint8_t c); 



static void Delay(uint32_t us)
{
	us *= 48; 
	
	while (us--) 
		__nop();
	
}


/*******************************************************************************
********************************************************************************


    ##     ##    ###    #### ##    ## 
    ###   ###   ## ##    ##  ###   ## 
    #### ####  ##   ##   ##  ####  ## 
    ## ### ## ##     ##  ##  ## ## ## 
    ##     ## #########  ##  ##  #### 
    ##     ## ##     ##  ##  ##   ### 
    ##     ## ##     ## #### ##    ## 


*/
int main(void)
{
	uint8_t r,c;
	LEDS_Init();

	r=1;
	while (1)
	{
		c = (uint8_t)(rand() % 0x0f);
		LEDS_Test(r,c);
		Delay(10000);
		r <<= 1; if ((r==0) | (r>0xf)) r =1;
	}
	
}

