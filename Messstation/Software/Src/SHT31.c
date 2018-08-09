//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Messstation
//	File		: SHT31.c
//	Function: 
//
//
#include "SHT31.h"


//*******************************************************//
//
// Function	:	Start the heater on the SHT31 sensor
// Param		: myI2C_Handler *i2c 	->	includes the I2Cbus on which the data should be send
// RetVal		: non
//
void mySHT31_Heater_ON(myI2C_Handler *i2c)
{
	i2c->TXInfo.Device = SHT31_A;
	i2c->TXInfo.Register = HEATER;
	i2c->TXInfo.Data[0] = HEATER_ON;
	i2c->TXInfo.Size = 1;
	
	myI2C_Write(i2c);
}


//*******************************************************//
//
// Function	:	Stop the heater on the SHT31 sensor
// Param		: myI2C_Handler *i2c 	->	includes the I2Cbus on which the data should be send
// RetVal		:	non
//
void mySHT31_Heater_OFF(myI2C_Handler *i2c)
{
	i2c->TXInfo.Device = SHT31_A;
	i2c->TXInfo.Register = HEATER;
	i2c->TXInfo.Data[0] = HEATER_OFF;
	i2c->TXInfo.Size = 1;
	
	myI2C_Write(i2c);
}

//*******************************************************//
//
// Function	:	Read the status register of the SHT31 sensor
// Param		: myI2C_Handler *i2c 	->	includes the I2Cbus on which the data should be send
// RetVal		:	non
//
void mySHT31_Status_Read(myI2C_Handler *i2c)
{
	i2c->TXInfo.Device = SHT31_A;
	i2c->TXInfo.Register = (STATUS_READ & 0xFF00)>>8;
	i2c->TXInfo.Data[0] = (STATUS_READ & 0x00FF);
	i2c->TXInfo.Data[1] = (i2c->TXInfo.Register + i2c->TXInfo.Data[0]);
	i2c->TXInfo.Size = 2;
	
	/*request Data*/
	myI2C_Write(i2c);

	/*read the requested Data*/
	i2c->RXInfo.Device = SHT31_A;
	i2c->RXInfo.Size = 3;
	myI2C_Read(i2c);
}

//*******************************************************//
//
// Function	:	Clear the status register of the STH31 sensor
// Param		: myI2C_Handler *i2c 	->	includes the I2Cbus on which the data should be send
// RetVal		:	non
//
void mySHT31_Status_Clear(myI2C_Handler *i2c)
{
	i2c->TXInfo.Device = SHT31_A;
	i2c->TXInfo.Register = (STATUS_CLEAR & 0xFF00)>>8;
	i2c->TXInfo.Data[0] = (STATUS_CLEAR & 0x00FF);
	i2c->TXInfo.Size = 1;
	
	myI2C_Write(i2c);
}

//*******************************************************//
//
// Function	:	start the measurment with the chosen mode
// Param		: myI2C_Handler *i2c 			->	includes the I2Cbus on which the data should be send
//						uint8_t mode						->	the mode which the Sensor should operate with. @ref SHT31_MODES
//						uint8_t repeatability		->	sets the measurement duration or the repeatability @ref SHT31_REPEATABILITY
// RetVal		:	non
//
void mySHT31_Start(myI2C_Handler *i2c, uint8_t mode, uint8_t repeatability)
{
	i2c->TXInfo.Device = SHT31_A;
	i2c->TXInfo.Register = mode;
	i2c->TXInfo.Data[0] = repeatability;
	i2c->TXInfo.Size = 1;
	
	
	/*request Data*/
	myI2C_Write(i2c);
	
	/*read the requested Data if single shot measurement is selected*/
	if(mode == SSM_S || mode == SSM_NS)
	{
		i2c->RXInfo.Device = SHT31_A;
		i2c->RXInfo.Register = mode;
		i2c->RXInfo.Size = 6;
		myI2C_Read(i2c);
	}
}

//*******************************************************//
//
// Function	: 
// Param		: myI2C_Handler *i2c 	->	includes the I2Cbus on which the data should be send
// RetVal		:	non
//
void mySHT31_Stop(myI2C_Handler *i2c)
{
	i2c->TXInfo.Device = SHT31_A;
	i2c->TXInfo.Register = (SHT31_STOP & 0xFF00)>>8;
	i2c->TXInfo.Data[0] = (SHT31_STOP & 0x00FF);
	i2c->TXInfo.Size = 1;
	
	myI2C_Write(i2c);
}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void SHT31_ERROR()
{
	while(1);
}
