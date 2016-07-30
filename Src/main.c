/*******************************************************************************
 * Copyright (c) 2016 Benoit Anctil-Robitaille.
 *******************************************************************************/
/*
 _____ _______     __   ____  _    _         _____   _____ ____  _____ _______ ______ _____
 |  __ \_   _\ \   / /  / __ \| |  | |  /\   |  __ \ / ____/ __ \|  __ \__   __|  ____|  __ \
 | |  | || |  \ \_/ /  | |  | | |  | | /  \  | |  | | |   | |  | | |__) | | |  | |__  | |__) |
 | |  | || |   \   /   | |  | | |  | |/ /\ \ | |  | | |   | |  | |  ___/  | |  |  __| |  _  /
 | |__| || |_   | |    | |__| | |__| / ____ \| |__| | |___| |__| | |      | |  | |____| | \ \
 |_____/_____|  |_|     \___\_\\____/_/    \_\_____/ \_____\____/|_|      |_|  |______|_|  \_
 */
/******************************************************************************/
/*                               Includes                                     */
/******************************************************************************/
#include <CommonIncludes.h>
/******************************************************************************/
/*                            Local Constants                                 */
/******************************************************************************/

/******************************************************************************/
/*                           Private Variables                                */
/******************************************************************************/
osThreadId 	telemetryTaskHandle;
osThreadId	telemetryManagerTaskHandle;
osThreadId 	ledTaskHandle;
/******************************************************************************/
/*                      Private Function Prototypes                           */
/******************************************************************************/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void const * argument);
void Create_System_Tasks();
/******************************************************************************/

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  osThreadDef(ledTask, StartDefaultTask, osPriorityNormal, 0, 128);
  ledTaskHandle = osThreadCreate(osThread(ledTask), NULL);

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  while (1)
  {
  }
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD3_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void StartDefaultTask(void const * argument)
{
  for(;;)
  {
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    osDelay(1000);
  }
}

void Create_System_Tasks(){

	if(START_TELEMETRY || START_ALL_TASKS){
		osThreadDef(TELEMETRY_TASK,
				StartDefaultTask,
				TELEMETRY_TASK_PRIORITY,
				0,
				TELEMETRY_TASK_STACK_SIZE);
		telemetryTaskHandle = osThreadCreate(osThread(TELEMETRY_TASK), NULL);
	}

	if(START_TELEMETRY_CONTROLLER || START_ALL_TASKS){
		osThreadDef(TELEMETRY_MANAGER_TASK,
				StartDefaultTask,
				TELEMETRY_MANAGER_TASK_PRIORITY,
				0,
				TELEMETRY_MANAGER_TASK_STACK_SIZE);
		telemetryManagerTaskHandle = osThreadCreate(osThread(TELEMETRY_MANAGER_TASK), NULL);
	}
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while(1)
  {
  }
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
