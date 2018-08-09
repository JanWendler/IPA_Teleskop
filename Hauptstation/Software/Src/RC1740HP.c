//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.04.2018
//	wDate		:	07.05.2018
//	Projekt	: IPA Hauptstation
//	File		: RC1740HP.c
//	Function: 
//
//

#include "RC1740HP.h"

/*declare the UART Handlers for the active UART modules*/
#if UART1
#define UART1_ACTIVE
extern myUART_Handler UART1Struct;
#endif /*UART1*/

#if UART2
#define UART2_ACTIVE
extern myUART_Handler UART2Struct;
#endif /*UART2*/

#if UART3
#define UART3_ACTIVE
extern myUART_Handler UART3Struct;
#endif /*UART3*/

//*******************************************************//
//
// Function	:	start the read process of the RF modul
// Param		: myUART_Handler *uart
// RetVal		: non
//
void myRC1740HP_read_start(myUART_Handler *uart)
{
	HAL_GPIO_WritePin(RF_Config_GPIO_Port, RF_Config_Pin, GPIO_PIN_SET);
	HAL_UART_Receive_IT(uart->InitStruct, (uint8_t*)uart->uartRXBuf, 1);
}

//*******************************************************//
//
// Function	:	stop the read process of the RF modul
// Param		: myUART_Handler *uart
// RetVal		: non
//
void myRC1740HP_read_stop(myUART_Handler *uart)
{
	__HAL_UART_DISABLE_IT(uart->InitStruct,UART_IT_RXNE);
	
	/*set RF module to sleep modus*/
	HAL_GPIO_WritePin(RF_Config_GPIO_Port, RF_Config_Pin, GPIO_PIN_RESET);
	while(uart->RxProtocol.Data[0] != 1);
	if(uart->RxProtocol.Data[0] == 1)
	{
		uart->uartTXBuf[0] = SLEEP_MODE;
		HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	}
}

//*******************************************************//
//
// Function	:	write to the RF modul
// Param		:	myUART_Handler *uart
// RetVal		: non
//
void myRC1740HP_write(myUART_Handler *uart)
{
	myUART_Write(uart);
}

//*******************************************************//
//
// Function	:	configure the RF modul
// Param		: myUART_Handler *uart
// RetVal		: non
//
void myRC1740HP_config(myUART_Handler* uart)
{	
	HAL_GPIO_WritePin(RF_Config_GPIO_Port, RF_Config_Pin, GPIO_PIN_RESET);
		
	/*Set the destination Adress to 0x66 / Broadcast*/
	while(uart->newDataReceived);
	uart->newDataReceived = 1;
	
	/*de-assert config pin*/
	HAL_GPIO_WritePin(RF_Config_GPIO_Port, RF_Config_Pin, GPIO_PIN_SET);
	
	uart->uartTXBuf[0] = DESTINATION_ADDRESS;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	while(uart->newDataReceived);
	uart->newDataReceived = 1;
	
	uart->uartTXBuf[0] = 0xFF;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*enter the non Volatile memory*/
	while(uart->newDataReceived);
	uart->newDataReceived = 1;
	
	uart->uartTXBuf[0] = MEMORY;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	while(uart->newDataReceived);
	uart->newDataReceived = 1;
	
	/*select the 434MHz channel*/
	uart->uartTXBuf[0] = RF_CHANNEL;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x52;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*select a low power level for lower power consumption*/
	uart->uartTXBuf[0] = RF_POWER;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x02;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set the unique id to 0x65*/
	uart->uartTXBuf[0] = UNIQUE_ID;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x64;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set the system id to 0x10*/
	uart->uartTXBuf[0] = SYSTEM_ID;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x10;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set the broadcast adress to 0xFF*/
	uart->uartTXBuf[0] = BROADCAST_ADDRESS;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0xFF;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*use adressing mode*/
	uart->uartTXBuf[0] = ADDRESS_MODE;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x02;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set the pcket lenght*/
	uart->uartTXBuf[0] = PACKET_LENGHT;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x80;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set the timeout time*/
	uart->uartTXBuf[0] = PACKET_TIMEOUT;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x01;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set endcharacter*/
	uart->uartTXBuf[0] = PACKET_END_CHARACTER;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x0D;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*set endcharacter*/
	uart->uartTXBuf[0] = CRC_MODE;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	uart->uartTXBuf[0] = 0x00;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	/*exti the non volatile memory*/
	uart->uartTXBuf[0] = EXIT;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
//	while(uart->newDataReceived);
//	uart->newDataReceived = 1;
//	uart->uartTXBuf[0] = TEST_MODE_1;
//	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
	
	
	/*exit form the config modus*/
	while(uart->newDataReceived);
	uart->newDataReceived = 1;
	
	uart->uartTXBuf[0] = END;
	HAL_UART_Transmit(uart->InitStruct, (uint8_t*)uart->uartTXBuf,1,1);
}

//*******************************************************//
//
// Function	:	non
// Param		: non
// RetVal		: non
//
void RC1740HP_ERROR(void)
{
	while(1);
}
