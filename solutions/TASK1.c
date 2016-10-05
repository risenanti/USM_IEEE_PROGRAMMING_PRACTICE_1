#include "stm32f4xx.h"
#include "stm32f411e_discovery.h"
#include "Tools.h"

static GPIO_InitTypeDef  GPIO_InitStruct;

static void LED_SETUP(void);
static void LED_TOGGLE(void);
static void LED_SET_ALL(uint8_t x);
static void playTime(void);

static void TIMER_SETUP(void);
void TIM3_IRQHandler(void);

TIM_HandleTypeDef    TimHandle;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	LED_SETUP();

	TIMER_SETUP();

	for(;;)
	{
		/*BEGIN DELAY_TOGGLE*/
		//LED_TOGGLE();
	    //HAL_Delay(200);
	    /*END DELAY_TOGGLE*/
	}
}

static void LED_SETUP(void)
{
	  __HAL_RCC_GPIOD_CLK_ENABLE();

	  //BLUE
	  GPIO_InitStruct.Pin = GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  //RED
	  GPIO_InitStruct.Pin = GPIO_PIN_14;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  //ORANGE
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  //GREEN
	  GPIO_InitStruct.Pin = GPIO_PIN_12;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void LED_TOGGLE(void)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}

static void LED_SET_ALL(uint8_t x)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, x);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, x);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, x);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, x);
}

static void playTime(void)
{
	static uint8_t counting = 0;
	switch (counting)
	{
		case 0: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET); break;
		case 1: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET); break;

		case 2: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET); break;
		case 3: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET); break;

		case 4: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET); break;
		case 5: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET); break;

		case 6: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET); break;
		case 7: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET); break;

		case 8: LED_SET_ALL(SET); break;
		case 9: LED_SET_ALL(RESET); break;
	}
	counting++;
	if (counting > 9)
	{
		counting = 0;
	}
}

static void TIMER_SETUP(void)
{
	HAL_RCC_GetHCLKFreq();
	uint32_t uwPrescalerValue = (uint32_t) ((SystemCoreClock / 10000) - 1);

	  /* Set TIMx instance */
	  TimHandle.Instance = TIM3;

	  /* Initialize TIM3 peripheral as follow:
	       + Period = 10000 - 1
	       + Prescaler = ((SystemCoreClock/2)/10000) - 1
	       + ClockDivision = 0
	       + Counter direction = Up
	  */
	  TimHandle.Init.Period = 5000 - 1; //Half a second
	  TimHandle.Init.Prescaler = uwPrescalerValue;
	  TimHandle.Init.ClockDivision = 0;
	  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	  __HAL_RCC_TIM3_CLK_ENABLE();

	  /*##-2- Configure the NVIC for TIM3 ########################################*/
	  /* Set the TIM3 priority */
	  HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);

	  /* Enable the TIM3 global Interrupt */
	  HAL_NVIC_EnableIRQ(TIM3_IRQn);

	  HAL_TIM_Base_Init(&TimHandle);
	  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
	  /* Start Channel1 */
	  HAL_TIM_Base_Start_IT(&TimHandle);
}
void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance==TIM3)
   {
    	playTime();
    	//LED_TOGGLE();
   }
}
