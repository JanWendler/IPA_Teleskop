//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Messstation
//	File		: Init.c
//	Function: 
//
//

#include "Init.h"

//*******************************************************//
//
// Function	: Error Function
// Param		: non
// RetVal		: non
//
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    INIT_ERROR();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    INIT_ERROR();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    INIT_ERROR();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_ADC_Init(ADC_HandleTypeDef *hadc1)
{
	

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1->Instance = ADC1;
  hadc1->Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1->Init.Resolution = ADC_RESOLUTION_12B;
  hadc1->Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1->Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc1->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1->Init.LowPowerAutoWait = DISABLE;
  hadc1->Init.LowPowerAutoPowerOff = DISABLE;
  hadc1->Init.ContinuousConvMode = DISABLE;
  hadc1->Init.DiscontinuousConvMode = DISABLE;
  hadc1->Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1->Init.DMAContinuousRequests = DISABLE;
  hadc1->Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(hadc1) != HAL_OK)
  {
    INIT_ERROR();
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(hadc1, &sConfig) != HAL_OK)
  {
    INIT_ERROR();
  }

}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_I2C1_Init(I2C_HandleTypeDef *hi2c1)
{
  hi2c1->Instance = I2C1;
  hi2c1->Init.Timing = 0x2000090E;
  hi2c1->Init.OwnAddress1 = 0;
  hi2c1->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1->Init.OwnAddress2 = 0;
  hi2c1->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if(HAL_I2C_Init(hi2c1) != HAL_OK)
  {
		INIT_ERROR();
  }
	/**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    INIT_ERROR();
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(hi2c1, 0) != HAL_OK)
  {
    INIT_ERROR();
  }
}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_USART1_Init(UART_HandleTypeDef *huart1)
{
	
  huart1->Instance = USART1;
  huart1->Init.BaudRate = 115200;
  huart1->Init.WordLength = UART_WORDLENGTH_8B;
  huart1->Init.StopBits = UART_STOPBITS_1;
  huart1->Init.Parity = UART_PARITY_NONE;
  huart1->Init.Mode = UART_MODE_TX_RX;
  huart1->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1->Init.OverSampling = UART_OVERSAMPLING_16;
  huart1->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//  huart1->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXINVERT_INIT;
//	huart1->AdvancedInit.RxPinLevelInvert = UART_ADVFEATURE_RXINV_ENABLE;
  if (HAL_UART_Init(huart1) != HAL_OK)
  {
    INIT_ERROR();
  }
	HAL_NVIC_SetPriority(USART1_IRQn,0,0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RF_Config_GPIO_Port, RF_Config_Pin, GPIO_PIN_SET);
  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	
  /*Configure GPIO pin : PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_TIM3_Init(TIM_HandleTypeDef *htim3)
{
	__TIM3_CLK_ENABLE();
	
  htim3->Instance = TIM3;
  htim3->Init.Prescaler = 8000000;
  htim3->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3->Init.Period = 60;
  htim3->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(htim3);
	
	HAL_NVIC_SetPriority(TIM3_IRQn,0,0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

//*******************************************************//
//
// Function	: Error Function
// Param		: non
// RetVal		: non
//
void INIT_ERROR(void)
{
	while(1);
}
