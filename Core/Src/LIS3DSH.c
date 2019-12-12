/*
 * LIS3DSH.c
 *
 *  Created on: Dec 10, 2019
 *      Author: janus
 */

#include "LIS3DSH.h"

void LIS3DSH_init()
{
	spiDriverInit();
    uint8_t tmpreg;
    uint16_t temp;
    temp = (uint16_t) (LIS3DSH_DATARATE_100 | LIS3DSH_XYZ_ENABLE);
	temp |= (uint16_t) (LIS3DSH_SERINTER_4WIRE | LIS3DSH_SELFTEST_NORMAL);
	temp |= (uint16_t) (LIS3DSH_FULLSCALE_4);
	temp |= (uint16_t)(LIS3DSH_FILTER_BW_800 << 8);

	tmpreg = (uint8_t)(temp);
	spiWriteReg(LIS3DSH_CTRL_REG4, &tmpreg, 1);
	tmpreg = (uint8_t)(temp>>8);
	spiWriteReg(LIS3DSH_CTRL_REG5, &tmpreg, 1);
//	uint8_t t1 = LIS3DSH_CTRL_REG5;
//	uint8_t t2 = 0x04;
////	spiWriteReg(t, 1);
////	spiWriteReg(&t1, 1);
////	spiWriteReg(&t2, 1);

//	spiWrite(t1, &t2, 1); //this function finally works. togling cs caused problem when writing data
//	HAL_Delay(100);
//	uint8_t data = 0;
//	spiReadReg(LIS3DSH_CTRL_REG5, &data, 1);
//	uint8_t e = 0;

}

bool LIS3DSH_check_sensor()
{
	uint8_t data = 0;
	spiReadReg(LIS3DSH_WHO_I_AM, &data, 1);
	return data == LIS3DSH_ID;
}

void LIS3DSH_READ_DATA(DATA_FROM_AXES_LIS3DSH_t *DATA_FROM_AXCES_STRUCT) {
   uint8_t buffer[6] = {0};
   spiReadReg(LIS3DSH_OUT_X_L, &buffer[0], 1);
   spiReadReg(LIS3DSH_OUT_X_H, &buffer[1], 1);
   spiReadReg(LIS3DSH_OUT_Y_L, &buffer[2], 1);
   spiReadReg(LIS3DSH_OUT_Y_H, &buffer[3], 1);
   spiReadReg(LIS3DSH_OUT_Z_L, &buffer[4], 1);
   spiReadReg(LIS3DSH_OUT_Z_H, &buffer[5], 1);

   DATA_FROM_AXCES_STRUCT->X = (int16_t)((buffer[1] << 8) + buffer[0]) * LIS3DSH_SENSI_0_12G;
   DATA_FROM_AXCES_STRUCT->Y = (int16_t)((buffer[3] << 8) + buffer[2]) * LIS3DSH_SENSI_0_12G;
   DATA_FROM_AXCES_STRUCT->Z = (int16_t)((buffer[5] << 8) + buffer[4]) * LIS3DSH_SENSI_0_12G;
}

