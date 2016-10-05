/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f411e_discovery.h"
#include "Tools.h"

static void LED_SETUP(void);
static void LED_TOGGLE(void);
static void LED_SET_ALL(uint8_t x);
static void playTime(void);

void   EXTI0_IRQHandler(void);
static void EXTILine0_Config(void);



int main(void)
{
	HAL_Init();
	SystemClock_Config();
	LED_SETUP();
	EXTILine0_Config();

	for(;;);
}

/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_0)
  {
	  playTime();
  }
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

static void LED_SETUP(void)
{
	static GPIO_InitTypeDef  GPIO_InitStruct;

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
