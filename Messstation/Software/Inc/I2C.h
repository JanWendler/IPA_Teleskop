//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Messstation
//	File		: I2C.h
//	Function: 
//
//

#ifndef _I2C_H_
#define _I2C_H_

#include "stm32f0xx_hal.h"

//*******************************************************//
//
//	Defines
//

#define DATABUFFERSIZE 6

#define TRANSMIT_ERROR	((uint8_t)0x01)
#define RECEIVE_ERROR		((uint8_t)0x02)
#define SIZE_ERROR			((uint8_t)0x03)

//*******************************************************//
//
//	typedef enums and structs
//
typedef struct
{
	uint16_t Device;
	uint8_t Register;
	uint8_t Size;
	uint8_t Data[DATABUFFERSIZE];
}Communication;

typedef struct
{
	I2C_HandleTypeDef *InitStruct;
	Communication TXInfo;
	Communication RXInfo;
}volatile myI2C_Handler;

//*******************************************************//
//
//	Functions
//
void myI2C_Write(myI2C_Handler *i2c);
void myI2C_Read(myI2C_Handler *i2c);
void I2C_ERROR(uint8_t Error);

#endif /*_I2C_H_*/
