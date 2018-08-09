//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Hauptstation
//	File		: UART.c
//	Function: 
//
//

#include "UART.h"

/*declare the UART Handlers for the active UART modules*/
#if UART1
#define UART1_ACTIVE
extern myUART_Handler UART1Struct;
#else
#define UART1_INACTIVE
#endif

#if UART2
#define UART2_ACTIVE
extern myUART_Handler UART2Struct;
#else
#define UART2_INACTIVE
#endif

#if UART3
#define UART3_ACTIVE
extern myUART_Handler UART3Struct;
#else
#define UART3_INACTIVE
#endif

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void myUART_Write(myUART_Handler *uart)
{
	/*Init Protokol Variables*/
	uint8_t STARTCHAR[1] = {0x23}; //#
	uint8_t ENDCHAR[2] = {0x0D, 0x0A}; // /n/r
	uint8_t cs_h = 0, cs_l = 0;
	uint8_t TXBuffer[UART_BUFFER_SIZE];
	
	/*Reset Check Sum*/
	uart->TxProtocol.CS = 0;
	
	/*Start Protocol*/
	TXBuffer[0] = STARTCHAR[0];
	/*Select Device for protocol*/
	TXBuffer[1] = uart->TxProtocol.Device;
	/*Select Module for protocol*/
	TXBuffer[2] = uart->TxProtocol.Module;
	/*Select Size for protocol*/
	TXBuffer[3] = uart->TxProtocol.Size;
	/*Select Data for protocol*/
	for(int i = 0; i < uart->TxProtocol.Size; i++)
	{
		TXBuffer[i+4] = uart->TxProtocol.Data[i];
	}
	/*Add up the Data for the Check Sum*/
	for(uint16_t i = 0; i < uart->TxProtocol.Size; i++)
	{
		uart->TxProtocol.CS += uart->TxProtocol.Data[i]; 
	}
	/*Add size and module to check sum*/
	uart->TxProtocol.CS += uart->TxProtocol.Size;
	uart->TxProtocol.CS += uart->TxProtocol.Device;
	uart->TxProtocol.CS += uart->TxProtocol.Module;
	
	/*16 bit variable -> 2x 8bit Array*/
	cs_h = ((uart->TxProtocol.CS & 0xFF00)>>8); // high nibble
	cs_l = (uart->TxProtocol.CS & 0x00FF);			// low nibble
	TXBuffer[4+uart->TxProtocol.Size]=cs_h;
	TXBuffer[4+uart->TxProtocol.Size + 1]=cs_l;
	
	/*set end bit in protocol*/
	TXBuffer[4+uart->TxProtocol.Size + 2] = ENDCHAR[0];
	TXBuffer[4+uart->TxProtocol.Size + 3] = ENDCHAR[1];
	
	/*Transmit protocol*/
	HAL_UART_Transmit(uart->InitStruct, TXBuffer, (4+uart->TxProtocol.Size + 4),10);
}

//*******************************************************//
//
// Function	:
// Param		: 
// RetVal		:
//
void myUART_Read(myUART_Handler *uart)
{
	/*Init temp var*/
	uint16_t ProtocolCS = 0;
	uint16_t i;
	uint8_t RXBuffer[UART_BUFFER_SIZE];
	
	/*Receive protocol*/
	if(HAL_UART_Receive(uart->InitStruct, RXBuffer, UART_BUFFER_SIZE,10) == HAL_ERROR)
	{
		UART_ERROR(RECEIVE_ERROR);
	}
	/*check for startbit*/
	if(RXBuffer[0] == '#')
	{
		/*Decode Protocol and assigne it to the right place*/
		uart->RxProtocol.CS = 0;
		uart->TxProtocol.Device = ((UARTDevice)RXBuffer[1]);
		uart->RxProtocol.Module = ((TargetModule)RXBuffer[2]);
		uart->RxProtocol.Size = RXBuffer[3];
		
		/*Read data*/
		for(uint16_t i = 0; i < uart->RxProtocol.Size; i++)
		{
			uart->RxProtocol.Data[i] = RXBuffer[4+i];
		}
		
		/*make check sum*/
		for(i = 0; i < uart->RxProtocol.Size; i++)
		{
			uart->RxProtocol.CS += uart->RxProtocol.Data[i]; 
		}
		uart->RxProtocol.CS += uart->RxProtocol.Size;
		uart->RxProtocol.CS += uart->RxProtocol.Device;
		uart->RxProtocol.CS += uart->RxProtocol.Module;
		
		ProtocolCS = ((RXBuffer[(4+uart->RxProtocol.Size)]<<8) | (RXBuffer[(4+uart->RxProtocol.Size+1)]));
		/*test check sum*/
		if(uart->RxProtocol.CS != ProtocolCS)
		{
			UART_ERROR(CS_ERROR);
		}
	}
}
//*******************************************************//
//
// Function	:	the RX Callback function gets called when new Data has been sent by one of the 
//						connected modules. This function decodes the message and safes it in to the corresponding UARTStruct. @ref myUART_Handler
// Param		: UART_HandleTypeDef *huart
// RetVal		: non
//
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/*init Variables*/
	static int Protocol_start = 0;
	static int current_case = 0;
	static int step_count = 0;
	int i = 0;
	static myUART_Handler *UARTStruct;
	uint16_t ProtocolCS = 0;
	
	/*select the uart source the engaged the interrupt and use the corresponding Struct*/
	#ifdef UART1_ACTIVE
	if(huart->Instance == USART1) UARTStruct = UART1Struct; 
	#endif
	
	#ifdef UART2_ACTIVE
	if(huart->Instance == USART2) UARTStruct = UART2Struct;
	#endif
	
	#ifdef UART3_ACTIVE
	if(huart->Instance == USART3) UARTStruct = &UART3Struct;
	#endif
	
	/*check for startbit*/
	if(UARTStruct->uartRXBuf[0] == '#')
	{
		Protocol_start = 1;
		current_case = 0;
	}
	if(UARTStruct->uartRXBuf[0] == '>')
	{
		UARTStruct->newDataReceived = 0;
	}
	if(Protocol_start)
	{
		/*Decode Protocol and assigne it to the right place*/
		switch(current_case)
		{
			case 0: //start
				current_case++;
				break;
			case 1: //Device
				UARTStruct->RxProtocol.Device = ((UARTDevice)UARTStruct->uartRXBuf[0]);
				current_case++;
				break;
			case 2: //Module
				UARTStruct->RxProtocol.Module = ((TargetModule) UARTStruct->uartRXBuf[0]);
				current_case++;
				break;
			case 3: //Size
				UARTStruct->RxProtocol.Size = UARTStruct->uartRXBuf[0];
				current_case++;
				break;
			case 4: //Data
				UARTStruct->RxProtocol.Data[step_count] = UARTStruct->uartRXBuf[0];
				if(step_count >= (UARTStruct->RxProtocol.Size-1))
				{
					step_count = 0;
					current_case++;
				}
				else
				{
					step_count++;
				}
				break;
			case 5:
				UARTStruct->RxProtocol.CS = 0;
				/*make check sum*/
				for(i = 0; i < UARTStruct->RxProtocol.Size; i++)
				{
					UARTStruct->RxProtocol.CS += UARTStruct->RxProtocol.Data[i]; 
				}
				UARTStruct->RxProtocol.CS += UARTStruct->RxProtocol.Size;
				UARTStruct->RxProtocol.CS += UARTStruct->RxProtocol.Device;
				UARTStruct->RxProtocol.CS += UARTStruct->RxProtocol.Module;
				
				ProtocolCS = ((UARTStruct->uartRXBuf[(3+UARTStruct->RxProtocol.Size)]<<8) | (UARTStruct->uartRXBuf[(3+UARTStruct->RxProtocol.Size+1)]));
				/*test check sum*/
				if(UARTStruct->RxProtocol.CS != ProtocolCS)
				{
					__nop();
				}
				else
				{
					UARTStruct->newDataReceived = 1;
					current_case = 0;
					Protocol_start = 0;
				}
				break;
			default:
					break;
		}
	}
	/*initiate the next receice interrupt*/
	HAL_UART_Receive_IT(UARTStruct->InitStruct, (uint8_t*)UARTStruct->uartRXBuf, 1);
}

//*******************************************************//
//
// Function	: Error Function
// Param		: non
// RetVal		: non
//
void UART_ERROR(uint8_t Error)
{
	while(1);
}
