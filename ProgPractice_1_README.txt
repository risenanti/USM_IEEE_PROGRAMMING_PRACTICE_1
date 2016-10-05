VIDEO DEMONSTRATION: https://www.youtube.com/watch?v=OI9fx5Rv2mc

ASSIGNMENT 1 Beginner:

	TASK 1:
	
	Beginner Use HAL_Delay to
	
	1			Setup a GPIO PORT to blink the Blue LED Connected to Pin D 15
				
	2			Setup a pins and created a function to Blink all 4 USER LEDS at once. 
							Use the User Manual to find the Pinout. Included in the root of the repo
							
	3			Setup a function to iterate through a pattern of blinking each light 
							once then finally blinking all 4 lights at once.
							
	
	Intermediate: Do the same as the Above but use a timer. 
	
	
	
	TASK 2: Do the same as the abovbe but use the USER Push Button connected to Pin A 0 on the board instead. 
	
	Beginner use 
	
	GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
					DEFINED IN stm32f4xx_hal_gpio.c under HAL_Driver
	
	Intermediate: Setup The USER Push Button to an external interrupt line.
	
	/*PROGRAM STRUCTURE*/
	
#include "stm32f4xx.h"				/*MUST BE INCLUDED CONTAINS DRIVER*/
#include "stm32f411e_discovery.h"	/*MUST BE INCLUDED CONTAINS MEMORY MAP*/
#include "Tools.h"					/*CONTAINS SYSTEM CLOCK CONFIG*/

int main(void)
{
	HAL_Init();						/*INITIALIZES HAL_Libraries and systick which allows HAL_delay to work*/
	SystemClock_Config();			/*SETS PLL to allow the MCU to run at 100MHZ. */
									/*IS DEFINED IN Tools.h Just call it. I don't understand it completely myself*/
									/*CAN Be generated from the CubeMX and will need to change for things like USB applications.*/
}

						USEFUL FUNCTIONS
HAL_GPIO_TogglePin()
HAL_GPIO_WritePin()
HAL_GPIO_ReadPin()
HAL_Delay()

HOW TO SETUP A GPIO PIN

	  static GPIO_InitTypeDef  GPIO_InitStruct;			/*FIRST DECLARE A GPIO INITIALIZATION STRUCT*/
	  __HAL_RCC_GPIOD_CLK_ENABLE();						/*ENABLE THE GPIO PORT CLOCK IN THIS CASE PORT D*/

	  //BLUE
	  GPIO_InitStruct.Pin = GPIO_PIN_15;				/*SETS UP PIN*/
	  
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		/*SETS UP PIN AS OUTPUT USE 
	  													       GPIO_MODE_INPUT    FOR INPUT*/
	  													       
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);			/*function to pass struct to registers 
	  														AKA ACTUALLY SETS UP PIN*/
	  
PIN BASICS
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);			    /*TOGGLES PIN VALUE*/
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET);			/*SET = 1 or HIGH    RESET = 0 or LOW*/
	HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15)				/*READS VOLTAGE LEVEL OF PIN IF IT IS AN INPUT 
															RETURNS 0 for LOW or 1 for HIGH*/
	
HAL_Delay(100)												/*DELAYS PROGRAM EXECUTION FOR 100 ms*/


						TIMERS
THE Idea of a timer is that it is a HARDWARE counter to keep track of time. The Following uses 
								TIM3 which is a 16 Bit timer. TIMx can be TIM1 to TIM8
		A TIMER Interupt works by setting up a timer and then when the timer counts to a certain 
			value the program execution will halt and a certain function will execute. 
		
		A common application is to have a processor in a low power mode and to wake it up at set intervals to
			process data. Or in ths case Blink an LED every second or half second. 


TO SETUP A TIMER

CREATE A TIM_HandleTypeDef    struct
			EX: TIM_HandleTypeDef    TimHandle;
CALL HAL_RCC_GetHCLKFreq(); to UPDATE THE SystemCoreClock which is a variable that keeps track of the clock
								speed. This will be used to compute the TIMER prescaler later.
																
		HAL_RCC_GetHCLKFreq();			/*UPDATES SystemCoreClock to reflect the processors speed*/

	    uint32_t uwPrescalerValue = (uint32_t) ((SystemCoreClock / 10000) - 1);

THIS SELECTS THE TIMER BEING USED

	  /* Set TIMx instance */
	  TimHandle.Instance = TIM3;

	  /* Initialize TIM3 peripheral as follow:
	       + Period = 10000 - 1
	       + Prescaler = ((SystemCoreClock/2)/10000) - 1
	       + ClockDivision = 0
	       + Counter direction = Up
	  */
	  
	  
	  TimHandle.Init.Period = 5000 - 1; 	/*THE PERIOD IS THE VALUE THAT THE CLOCK COUNTS UP TO 
	  											in order TO TRIGGER AN INTERRUPT*/
	  
	  TimHandle.Init.Prescaler = uwPrescalerValue;	/*THIS IS THE INITIAL CLOCK DIVER MAX VALUE is 2^16*/
	  
	  TimHandle.Init.ClockDivision = 0;
	  
	  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	  
	  __HAL_RCC_TIM3_CLK_ENABLE();			/*ENABLE TIMER CLOCK*/

	  /*##-2- Configure the NVIC for TIM3 ########################################*/
	  /* Set the TIM3 priority INTERUPT PRIORITY WILL BE DISCUSSED LATER*/
	  HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);

	  /* Enable the TIM3 global Interrupt */
	  HAL_NVIC_EnableIRQ(TIM3_IRQn);

	  HAL_TIM_Base_Init(&TimHandle);
	  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
	  /* Start Channel1 */
	  HAL_TIM_Base_Start_IT(&TimHandle);
}

/*MUST BE INCLUDED IN MAIN DO NOT CHANGE THE NAME 
		IT IS BOUND TO THE TIM3 TIMER THROUHG NVIC, Nested Vector Interrupt Table*/
void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}

/*ALL TIMERS SHARE THE SAME CALLBACK FUNCTION*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance==TIM3) /*TEST IF THE INTERUPT WAS TRIGGERED BY TIM3*/
   {
    	//LED_TOGGLE();			/*IF TIM3 THEN EXECUTE FUNCTION*/
   }
}

				EXTERNAL INTERUPTS
The idea of an external interrupt is that if a voltage change is detected on a pin then the procssor will halt
		and execute a function. Which is the exact same as the timers from above, but this allows the processor
		to react to it's environment.

The same as Timers and GPIO set up an init structor. Fill the parameters. Enable the port clock.
			call an initialization function then set the priority.
			
			IN THE GPIO INIT STRCUTURE
			
			GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING; /*SETS UP THE INTERRUPT TO TRIGGER ON THE FALLING EDGE*/
																		Meaning if the PIN is HIGH and changes to LOW
																		The interrupt will trigger but not LOW to HIGH

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

/*Same Two concepts as timers. Fights theres an IRQ handler and then a callbacj function*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_0)
  {
	  LED_Toggle();
  }
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}