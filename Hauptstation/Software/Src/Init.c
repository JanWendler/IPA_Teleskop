//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Hauptstation
//	File		: Init.c
//	Function: 
//
//

#include "Init.h"

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    INIT_ERROR();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
#if myI2C1
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_I2C2_Init(I2C_HandleTypeDef *hi2c1)
{

  hi2c1->Instance = I2C1;
  hi2c1->Init.ClockSpeed = 100000;
  hi2c1->Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1->Init.OwnAddress1 = 0;
  hi2c1->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1->Init.OwnAddress2 = 0;
  hi2c1->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(hi2c1) != HAL_OK)
  {
    INIT_ERROR();
  }
}
#endif /*myI2C1*/

#if myI2C2
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_I2C2_Init(I2C_HandleTypeDef *hi2c2)
{

  hi2c2->Instance = I2C2;
  hi2c2->Init.ClockSpeed = 100000;
  hi2c2->Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2->Init.OwnAddress1 = 0;
  hi2c2->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2->Init.OwnAddress2 = 0;
  hi2c2->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(hi2c2) != HAL_OK)
  {
    INIT_ERROR();
  }
}
#endif /*myI2C2*/

#if myUSART3
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_USART3_Init(UART_HandleTypeDef *huart3)
{
  huart3->Instance = USART3;
  huart3->Init.BaudRate = 19200;
  huart3->Init.WordLength = UART_WORDLENGTH_8B;
  huart3->Init.StopBits = UART_STOPBITS_1;
  huart3->Init.Parity = UART_PARITY_NONE;
  huart3->Init.Mode = UART_MODE_TX_RX;
  huart3->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3->Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(huart3) != HAL_OK)
  {
    INIT_ERROR();
  }
}
#endif /*myUSART3*/

#if mySPI2
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_SPI2_Init(SPI_HandleTypeDef *hspi2)
{

  hspi2->Instance = SPI2;
  hspi2->Init.Mode = SPI_MODE_MASTER;
  hspi2->Init.Direction = SPI_DIRECTION_2LINES;
  hspi2->Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2->Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2->Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2->Init.NSS = SPI_NSS_SOFT;
  hspi2->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2->Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2->Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2->Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(hspi2) != HAL_OK)
  {
    INIT_ERROR();
  }
}
#endif /*mySPI2*/

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	/*Configure GPIOA */
  HAL_GPIO_WritePin(GPIOA, 	GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | 
														GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 , GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = 	GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | 
													GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*Configure RF_Config_Pin*/
	HAL_GPIO_WritePin(RF_Config_GPIO_Port, RF_Config_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = RF_Config_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RF_Config_GPIO_Port, &GPIO_InitStruct);
	
	
  /*Configure GPIOB*/
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = 	 GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

#if myTIM1
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_TIM1_Init(TIM_HandleTypeDef *htim1)
{
  htim1->Instance = TIM1;
  htim1->Init.Prescaler = 8000000;
  htim1->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1->Init.Period = 60;
  htim1->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(htim1);
}
#endif /*myTIM1*/

#if myTIM2
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_TIM2_Init(TIM_HandleTypeDef *htim2)
{
	__TIM2_CLK_ENABLE();
  htim2->Instance = TIM2;
  htim2->Init.Prescaler = 320;
  htim2->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2->Init.Period = 40;
  htim2->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(htim2);
	
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
#endif /*myTIM2*/

#if myTIM3
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
  htim3->Init.Prescaler = 319;
  htim3->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3->Init.Period = 39;
  htim3->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(htim3);
	
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 2);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}
#endif /*myTIM3*/

#if myTIM4
//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void MX_TIM1_Init(TIM_HandleTypeDef *htim4)
{
  htim4->Instance = TIM4;
  htim4->Init.Prescaler = 8000000;
  htim4->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4->Init.Period = 60;
  htim4->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(htim4);
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 2);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
}
#endif /*myTIM4*/

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
