#include "stm32f4xx.h"
#include "stm32f411e_discovery.h"
#include "Tools.h"

static GPIO_InitTypeDef  GPIO_InitStruct;

static void LED_SETUP(void);
static void LED_TOGGLE(void);
static void LED_SET_ALL(uint8_t x);


int main(void)
{
	HAL_Init();
	SystemClock_Config();

	for(;;)
	{
		/*BEGIN DELAY_TOGGLE*/
		//LED_TOGGLE();
	    //HAL_Delay(200);
	    /*END DELAY_TOGGLE*/
	}
}
