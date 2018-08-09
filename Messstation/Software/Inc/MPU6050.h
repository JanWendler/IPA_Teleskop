//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.01.2018
//	wDate		:	23.01.2018
//	Projekt		: VR_RC_SIMULATION
//	File		: MPU6050.h
//	Function: 
//
//

#define GYRO_SCALE_FACTOR		32.8
#define ACCEL_SCALE_FACTOR 	4096

/*Address of Device*/
#define MPU_6050 							((uint16_t) 0x00D0)

/*Gyro Register*/
#define GYRO_DATA							((uint8_t)0x43)
#define GYRO_X_H 							((uint8_t)0x43)
#define GYRO_X_L 							((uint8_t)0x44)
#define GYRO_Y_H 							((uint8_t)0x45)
#define GYRO_Y_L 							((uint8_t)0x46)
#define GYRO_Z_H 							((uint8_t)0x47)
#define GYRO_Z_L 							((uint8_t)0x48)
#define GYRO_CONFIG 					((uint8_t)0x1B)

/*Gyro Config Register Values*/
#define GYRO_SCALE_250				((uint8_t)0x00)
#define GYRO_SCALE_500				((uint8_t)0x08)
#define GYRO_SCALE_1000				((uint8_t)0x10)
#define GYRO_SCALE_2000				((uint8_t)0x18)

/*Accel Registers*/
#define ACCEL_DATA 						((uint8_t)0x3B)
#define ACCEL_X_H 						((uint8_t)0x3B)
#define ACCEL_X_L 						((uint8_t)0x3C)
#define ACCEL_Z_H 						((uint8_t)0x3D)
#define ACCEL_Z_L 						((uint8_t)0x3E)
#define ACCEL_Y_H 						((uint8_t)0x3F)
#define ACCEL_Y_L 						((uint8_t)0x40)
#define ACCEL_CONFIG 					((uint8_t)0x1C)

/*Accel Config Register Values*/
#define ACCEL_SCALE_2					((uint8_t)0x00)
#define ACCEL_SCALE_4					((uint8_t)0x08)
#define ACCEL_SCALE_8					((uint8_t)0x10)
#define ACCEL_SCALE_16				((uint8_t)0x18)

/*Power Management Register*/
#define POWER_MANAGEMENT			((uint8_t)0x6B)

/*Power Management Register Values*/
#define SLEEP_ENALBE					((uint8_t)0x40)
#define SLEEP_DISABLE					((uint8_t)0x00)
#define CLOCK_8MHz						((uint8_t)0x00)
#define CLOCK_PLL_X						((uint8_t)0x01)
#define CLOCK_PLL_Y						((uint8_t)0x02)
#define CLOCK_PLL_Z						((uint8_t)0x03)
#define CLOCK_EXT_32_768kHz		((uint8_t)0x04)
#define CLOCK_EXT_19_2MHz			((uint8_t)0x05)

/*Sample Divider Register*/
#define SMPLRT_DIV						((uint8_t)0x19)

/*MPU Config Register*/
#define MPU_CONFIG						((uint8_t)0x1A)

/*MPU Config Register Values*/
#define MPU_BW_260HZ					((uint8_t)0x00)
#define MPU_BW_184HZ					((uint8_t)0x01)
#define MPU_BW_94HZ						((uint8_t)0x02)
#define MPU_BW_44HZ						((uint8_t)0x03)
#define MPU_BW_21HZ						((uint8_t)0x04)
#define MPU_BW_10HZ						((uint8_t)0x05)
#define MPU_BW_5HZ						((uint8_t)0x06)

/*MPU Interrupt Enable Register*/
#define INT_ENABLE						((uint8_t)0x38)

/*MPU Interrupt Enable Register Values*/
#define DATA_RDY_EN						((uint8_t)0x01)
#define I2C_MST_INT_EN				((uint8_t)0x08)
#define FIFO_OFLOW_EN					((uint8_t)0x10)

/*MPU Interrupt Pin Config Register*/
#define INT_PIN_CFG						((uint8_t)0x37)

/*MPU Interrupt Pin Config Register Values*/
#define INT_LEVEL							((uint8_t)0x80)
#define INT_OPEN							((uint8_t)0x40)
#define LATCH_INT_EN					((uint8_t)0x20)
#define INT_RD_CLEAR					((uint8_t)0x10)
#define FSYNC_INT_LEVEL				((uint8_t)0x08)
#define FSYNC_INT_EN					((uint8_t)0x04)
#define I2C_BYPASS_EN					((uint8_t)0x02)

/*Who_am_I Register*/
#define WHO_AM_I							((uint8_t)0x75)