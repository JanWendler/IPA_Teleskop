//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Hauptstation
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
#include "stm32f1xx_hal.h"

//*******************************************************//
//
//	Define
//
/*select active Modules*/
#define myUSART1	0
#define myUSART2	0
#define myUSART3	1
#define myI2C1		0
#define myI2C2		0
#define mySPI1		0
#define mySPI2		0
#define myCAN			0
#define myADC1		0
#define myADC2		0
#define myRTC			0
#define myTIM1		0
#define myTIM2		0
#define myTIM3		1
#define myTIM4		0


//*******************************************************//
//
//	Functions
//
#if myADC1
void MX_ADC1_Init(ADC_HandleTypeDef *hadc1);
#endif
#if myADC2
void MX_ADC1_Init(ADC_HandleTypeDef *hadc1);
#endif
#if myCAN
void MX_CAN_Init(CAN_HandleTypeDef *hcan);
#endif
#if myI2C1
void MX_I2C1_Init(I2C_HandleTypeDef *hi2c1);
#endif
#if myI2C2
void MX_I2C2_Init(I2C_HandleTypeDef *hi2c2);
#endif
#if myRTC
void MX_RTC_Init(RTC_HandleTypeDef *hrtc);
#endif
#if mySPI1
void MX_SPI1_Init(SPI_HandleTypeDef *hspi1);
#endif
#if mySPI2
void MX_SPI2_Init(SPI_HandleTypeDef *hspi2);
#endif
#if myUSART1
void MX_USART1_Init(UART_HandleTypeDef *huart1);
#endif
#if myUSART2
void MX_USART2_Init(UART_HandleTypeDef *huart2);
#endif
#if myUSART3
void MX_USART3_Init(UART_HandleTypeDef *huart3);
#endif
#if myADC1
void MX_ADC_Init(ADC_HandleTypeDef *hadc1);
#endif
#if myADC2
void MX_ADC_Init(ADC_HandleTypeDef *hadc2);
#endif
#if myTIM1
void MX_TIM1_Init(TIM_HandleTypeDef *htim1);
#endif
#if myTIM2
void MX_TIM2_Init(TIM_HandleTypeDef *htim2);
#endif
#if myTIM3
void MX_TIM3_Init(TIM_HandleTypeDef *htim3);
#endif
#if myTIM4
void MX_TIM4_Init(TIM_HandleTypeDef *htim4);
#endif



void SystemClock_Config(void);
void MX_GPIO_Init(void);
void INIT_ERROR(void);

#endif /*_INIT_H_*/
