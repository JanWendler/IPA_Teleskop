//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Messstation
//	File		: SHT31.h
//	Function: 
//
//
#ifndef _SHT31_H_
#define _SHT31_H_

//*******************************************************//
//
//	Includes
//
#include "stm32f0xx_hal.h"
#include "I2C.h"

//*******************************************************//
//
//	Defines
//

/**/
/**/	#define DEVICES
/**/

#define SHT31_A 				((uint8_t)0x88)		/*Device*/
#define SHT31_B					((uint8_t)0x8A)		/*Device*/


/**/
/**/	#define SHT31_MODES
/**/

#define SSM_S						((uint8_t)0x2C)		/*Single Shot Measurement stretching*/
#define SSM_NS					((uint8_t)0x24)		/*Single Shot Measurement no stretching*/
#define PM_05						((uint8_t)0x20)		/*Periodic Measurement 0.5 mps*/
#define PM_1						((uint8_t)0x21)		/*Periodic Measurement 1 mps*/
#define PM_2						((uint8_t)0x22)		/*Periodic Measurement 2 mps*/
#define PM_4						((uint8_t)0x23)		/*Periodic Measurement 4 mps*/
#define PM_10						((uint8_t)0x27)		/*Periodic Measurement 10 mps*/
#define HEATER					((uint8_t)0x30)		/*Heater*/


/**/
/**/	#define SHT31_REPEATABILITY
/**/

#define SSM_S_HIGH 			((uint8_t)0x06)		/*Single Shot Measurement stretching*/
#define SSM_S_MEDIUM		((uint8_t)0x0D)		/*Single Shot Measurement stretching*/
#define SSM_S_LOW				((uint8_t)0x10)		/*Single Shot Measurement stretching*/

#define SSM_NS_HIGH			((uint8_t)0x00)		/*Single Shot Measurement no stretching*/
#define SSM_NS_MEDIUM		((uint8_t)0x0B)		/*Single Shot Measurement no stretching*/
#define SSM_NS_LOW			((uint8_t)0x16)		/*Single Shot Measurement no stretching*/

#define PM_05_HIGH			((uint8_t)0x32)		/*Periodic Measurement 0.5 mps*/
#define PM_05_MEDIUM		((uint8_t)0x24)		/*Periodic Measurement 0.5 mps*/
#define PM_05_LOW				((uint8_t)0x2F)		/*Periodic Measurement 0.5 mps*/

#define PM_1_HIGH				((uint8_t)0x30)		/*Periodic Measurement 1 mps*/
#define PM_1_MEDIUM			((uint8_t)0x26)		/*Periodic Measurement 1 mps*/
#define PM_1_LOW				((uint8_t)0x2D)		/*Periodic Measurement 1 mps*/

#define PM_2_HIGH				((uint8_t)0x36)		/*Periodic Measurement 2 mps*/
#define PM_2_MEDIUM			((uint8_t)0x20)		/*Periodic Measurement 2 mps*/
#define PM_2_LOW				((uint8_t)0x2B)		/*Periodic Measurement 2 mps*/

#define PM_4_HIGH				((uint8_t)0x34)		/*Periodic Measurement 4 mps*/
#define PM_4_MEDIUM			((uint8_t)0x22)		/*Periodic Measurement 4 mps*/
#define PM_4_LOW				((uint8_t)0x29)		/*Periodic Measurement 4 mps*/

#define PM_10_HIGH			((uint8_t)0x39)		/*Periodic Measurement 10 mps*/
#define PM_10_MEDIUM		((uint8_t)0x21)		/*Periodic Measurement 10 mps*/
#define PM_10_LOW				((uint8_t)0x2A)		/*Periodic Measurement 10 mps*/

#define HEATER_ON				((uint8_t)0x6D)		/*Heater*/
#define HEATER_OFF			((uint8_t)0x66)		/*Heater*/


/*break / stop*/
#define SHT31_STOP			((uint16_t)0x3093)	

/*soft reset*/
#define SoftReset				((uint16_t)0x30A2)

/*Status Register*/
#define STATUS_READ			((uint16_t)0xF32D)
#define STATUS_CLEAR		((uint16_t)0x3041)

//*******************************************************//
//
//	Functions
//
void mySHT31_Heater_ON(myI2C_Handler *i2c);
void mySHT31_Heater_OFF(myI2C_Handler *i2c);
void mySHT31_Status_Read(myI2C_Handler *i2c);
void mySHT31_Status_Clear(myI2C_Handler *i2c);
void mySHT31_Start(myI2C_Handler *i2c, uint8_t mode, uint8_t repeatability);
void mySHT31_Stop(myI2C_Handler *i2c);
void SHT31_ERROR(void);

#endif /*_SHT31_H_*/
