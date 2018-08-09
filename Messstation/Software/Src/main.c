//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	16.04.2018
//	wDate		:	16.04.2018
//	Projekt	: IPA Messstation
//	File		: main.c
//	Function: 
//
//

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "Init.h"
#include "SHT31.h"
#include "RC1740HP.h"

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c1;
myI2C_Handler I2C1Struct;

UART_HandleTypeDef huart1;
myUART_Handler UART1Struct;

TIM_HandleTypeDef htim3;

uint32_t volatile TemperaturBuffer;
uint16_t volatile LuftfeuchtigkeitsBuffer;

/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);


int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_Init(&huart1);
  MX_I2C1_Init(&hi2c1);
  MX_ADC_Init(&hadc);
	MX_TIM3_Init(&htim3);
	
	/*Init Uart Struct*/
	UART1Struct.InitStruct = &huart1;
		
	/*Init I2C Struct*/
	I2C1Struct.InitStruct = &hi2c1;
	
	myRC1740HP_read_start(&UART1Struct);
//	myRC1740HP_config(&UART1Struct);
	
	HAL_TIM_Base_Start_IT(&htim3);
	
	HAL_I2C_IsDeviceReady(&hi2c1,0x88,1,1);
	mySHT31_Status_Read(&I2C1Struct);

//	HAL_ADC_Start(&hadc);
  /* Infinite loop */
  while (1)
  {
//		TemperaturBuffer = HAL_ADC_GetValue(&hadc);
  }

}

//*******************************************************//
//
// Function	: Timer Interrupt Handler for Update Interrupt. Interrupt get called every minute.¦
// Param		: TIM_HandleTypeDef *htim		-> the timer who started the interrupt
// RetVal		: non
//
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/*check if Timer 3 was the interrupt source*/
	if(htim->Instance == TIM3)
	{
		/*Get Humidity value from SHT31 Sensor*/
		mySHT31_Start(&I2C1Struct, SSM_NS, SSM_NS_HIGH);
	
 		LuftfeuchtigkeitsBuffer = (I2C1Struct.RXInfo.Data[4] | (I2C1Struct.RXInfo.Data[3] << 8));
		TemperaturBuffer = (I2C1Struct.RXInfo.Data[1] | (I2C1Struct.RXInfo.Data[0] << 8));
		
		/*Mask out Sensor buffers*/
  	UART1Struct.TxProtocol.Data[0] = (TemperaturBuffer & 0x00FF);
		UART1Struct.TxProtocol.Data[1] = (TemperaturBuffer & 0xFF00)>>8;		
		UART1Struct.TxProtocol.Data[2] = (LuftfeuchtigkeitsBuffer & 0x00FF);
		UART1Struct.TxProtocol.Data[3] = (LuftfeuchtigkeitsBuffer & 0xFF00) >> 8;
		UART1Struct.TxProtocol.Device = Teleskop1;
		UART1Struct.TxProtocol.Module = SensorData;
		UART1Struct.TxProtocol.Size = 4;
		
		/*send sensor values*/
		myRC1740HP_write(&UART1Struct);
	}
 }

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif
