//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Messstation
//	File		: I2C.c
//	Function: 
//
//

#include "I2C.h"

uint8_t i2c1RXBuf[6] = {0};
uint8_t i2c1TXBuf[6] = {0};


//*******************************************************//
//
// Function	: Write to i2c Device
// Param		: myI2C_Handler *i2c		-->		This Struct contains all Information needed for the transmision.
// RetVal		: non
//
void myI2C_Write(myI2C_Handler *i2c)
{
	//Check Data Size
	uint8_t ALLDATA[DATABUFFERSIZE]={0};
	if(i2c->TXInfo.Size > DATABUFFERSIZE)
	{
		I2C_ERROR(SIZE_ERROR);
	}
	ALLDATA[0] = i2c->TXInfo.Register;
	
	for(int i = 1; i<=i2c->TXInfo.Size; i++)
	{
		ALLDATA[i] = i2c->TXInfo.Data[i-1];
	}
	//Transmit register and data
	if(HAL_I2C_Master_Transmit(i2c->InitStruct, i2c->TXInfo.Device, ALLDATA, i2c->TXInfo.Size + 1,10) == HAL_ERROR)
	{
		I2C_ERROR(TRANSMIT_ERROR);
	}
}

//*******************************************************//
//
// Function	: Read a Register from a i2c device
// Param		: non
// RetVal		: non
//
void myI2C_Read(myI2C_Handler *i2c)
{
	//Check Data Size
	if(i2c->RXInfo.Size > DATABUFFERSIZE)
	{
		I2C_ERROR(SIZE_ERROR);
	}
	if(HAL_I2C_Master_Receive(i2c->InitStruct, i2c->RXInfo.Device,(uint8_t *) i2c->RXInfo.Data, i2c->RXInfo.Size,10) == HAL_ERROR)
	{
		I2C_ERROR(RECEIVE_ERROR);
	}
}

//*******************************************************//
//
// Function	: Error Function
// Param		: non
// RetVal		: non
//
void I2C_ERROR(uint8_t Error)
{
	while(1);
}
