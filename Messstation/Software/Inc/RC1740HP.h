//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Hauptstation
//	File		: RC1740HP.h
//	Function: 
//
//

#ifndef _RC1740HP_H_
#define _RC1740HP_H_

//*******************************************************//
//
//	Includes
//
#include "stm32f0xx_hal.h"
#include "UART.h"

//*******************************************************//
//
//	Defines
//

#define CHANNEL										((uint8_t)'C') 	//0x43
#define OUTPUT_POWER							((uint8_t)'P')	//0x50
#define DESTINATION_ADDRESS				((uint8_t)'T')	//0x54
#define MEMORY										((uint8_t)'M')	//0x4D
#define END												((uint8_t)'X')	//0x58
#define SLEEP_MODE								((uint8_t)'Z')	//0x5A

#define RF_CHANNEL								((uint8_t)0x00)
#define	RF_POWER									((uint8_t)0x01)
#define RF_DATA_RATE							((uint8_t)0x02)
#define RSSI_MODE									((uint8_t)0x05)
#define PREAMBLE_LENGHT						((uint8_t)0x0A)
#define PACKET_LENGHT							((uint8_t)0x0F)
#define PACKET_TIMEOUT						((uint8_t)0x10)
#define PACKET_END_CHARACTER			((uint8_t)0x11)
#define MAC_MODE									((uint8_t)0x13)
#define ADDRESS_MODE							((uint8_t)0x14)
#define CRC_MODE									((uint8_t)0x15)
#define UNIQUE_ID									((uint8_t)0x19)
#define SYSTEM_ID									((uint8_t)0x1A)
#define DESTINATION_ID						((uint8_t)0x21)
#define BROADCAST_ADDRESS					((uint8_t)0x28)
#define UART_BAUD_RATE						((uint8_t)0x30)
#define UART_FLOW_CTRL						((uint8_t)0x35)
#define DATA_INTERFACE						((uint8_t)0x36)
#define EXIT											((uint8_t)0xFF)
//*******************************************************//
//
//	Functions
//
void myRC1740HP_read_start(myUART_Handler *uart);
void myRC1740HP_read_stop(myUART_Handler *uart);
void myRC1740HP_write(myUART_Handler *uart);
void myRC1740HP_config(myUART_Handler *uart);
void RC1740HP_ERROR(void);

#endif /*_RC1740HP_H_*/

