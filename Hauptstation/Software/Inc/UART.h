//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Hauptstation
//	File		: UART.h
//	Function: 
//
//

#ifndef _UART_H_
#define _UART_H_

//*******************************************************//
//
//	Includes
//
#include "stm32f1xx_hal.h"

//*******************************************************//
//
//	Defines
//

/*User defines 
	1 = selected uart is active
	0 = selected uart is inactive
*/ 
#define UART1 0
#define UART2 0
#define UART3 1

/*Fixed defines*/
#define PROTOCOL_SIZE 12
#define UART_BUFFER_SIZE 20

#define TRANSMIT_ERROR	((uint8_t)0x01)
#define RECEIVE_ERROR		((uint8_t)0x02)
#define SIZE_ERROR			((uint8_t)0x03)
#define CS_ERROR				((uint8_t)0x04)

#define _TX2_HIGH() (GPIOA->BSRR = GPIO_PIN_2)
#define _TX2_LOW() 	(GPIOA->BRR = GPIO_PIN_2)
#define _RX2_HIGH() (GPIOA->BSRR = GPIO_PIN_3)
#define _RX2_LOW()	(GPIOA->BRR = GPIO_PIN_3)
//*******************************************************//
//
//	typedef enums and structs
//
typedef enum
{ 
	SensorData,
	DataUpTime,
}TargetModule;

typedef enum
{
	Teleskop1 = '%',			//0x25
	Teleskop2	= 'ç',			//0x80
	Teleskop3	= '*',			//0x2A
	Motherboard = '+',		//0x2B
	PC = '@'							//0x40
}UARTDevice;

typedef struct
{
	uint8_t 			Size;
	UARTDevice 	Device;
	TargetModule 	Module;
	uint8_t 			Data[UART_BUFFER_SIZE];
	uint16_t 			CS;
}UART_Protocol;

typedef struct
{
	UART_HandleTypeDef *InitStruct;
	UART_Protocol 			TxProtocol;
	UART_Protocol 			RxProtocol;
	uint8_t 						uartRXBuf[UART_BUFFER_SIZE];
	uint8_t							newDataReceived;
	uint8_t 						uartTXBuf[UART_BUFFER_SIZE];
} volatile myUART_Handler;

//*******************************************************//
//
//	Functions
//
void myUART_Write(myUART_Handler *uart);
void myUART_Read(myUART_Handler *uart);
void UART_ERROR(uint8_t Error);

#endif /*_UART_H_*/
