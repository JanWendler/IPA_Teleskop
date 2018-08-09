//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Messstation
//	File		: Init.h
//	Function: 
//
//


#ifndef _INIT_H_
#define _INIT_H_

//*******************************************************//
//
//	Includes
//
#include "stm32f0xx_hal.h"

//*******************************************************//
//
//	Functions
//
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(I2C_HandleTypeDef *hi2c1);
void MX_USART1_Init(UART_HandleTypeDef *huart1);
void MX_ADC_Init(ADC_HandleTypeDef *hadc1);
void MX_TIM3_Init(TIM_HandleTypeDef *htim3);
void INIT_ERROR(void);

#endif /*_INIT_H_*/
