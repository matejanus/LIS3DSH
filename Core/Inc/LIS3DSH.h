/*
 * LIS3DSH.h
 *
 *  Created on: Dec 10, 2019
 *      Author: janus
 */

#pragma once
#include "spiDriver.h"

#define LIS3DSH_ID                          0x3F

enum LIS3DSH_registers{
LIS3DSH_TEMPERATURE_REG = 0x0C,
LIS3DSH_WHO_I_AM=0x0F,
LIS3DSH_CTRL_REG4=0x20,
LIS3DSH_CTRL_REG1=0x21,
LIS3DSH_CTRL_REG2=0x22,
LIS3DSH_CTRL_REG3=0x23,
LIS3DSH_CTRL_REG5=0x24,
LIS3DSH_CTRL_REG6=0x25
};


#define LIS3DSH_OUT_X_L                     0x28
#define LIS3DSH_OUT_X_H                     0x29
#define LIS3DSH_OUT_Y_L                     0x2A
#define LIS3DSH_OUT_Y_H                     0x2B
#define LIS3DSH_OUT_Z_L                     0x2C
#define LIS3DSH_OUT_Z_H                     0x2D
#define LIS3DSH_SENSI_0_06G                 0.06
#define LIS3DSH_SENSI_0_12G                 0.12
#define LIS3DSH_SENSI_0_18G                 0.18
#define LIS3DSH_SENSI_0_24G                 0.24
#define LIS3DSH_SENSIY_0_73G                0.73
#define LIS3DSH_DATARATE_100                ((uint8_t)0x60)
#define LIS3DSH_FULLSCALE_2                 ((uint8_t)0x00)
#define LIS3DSH_FULLSCALE_4                 ((uint8_t)0x08)
#define LIS3DSH_FULLSCALE_6                 ((uint8_t)0x10)
#define LIS3DSH_FULLSCALE_8                 ((uint8_t)0x18)
#define LIS3DSH_FULLSCALE_16                ((uint8_t)0x20)
#define LIS3DSH_FULLSCALE_SELECTION         ((uint8_t)0x38)
#define LIS3DSH_FILTER_BW_800               ((uint8_t)0x00)
#define LIS3DSH_FILTER_BW_400               ((uint8_t)0x40)
#define LIS3DSH_FILTER_BW_200               ((uint8_t)0x80)
#define LIS3DSH_FILTER_BW_50                ((uint8_t)(0x80 | 0x40))
#define LIS3DSH_SELFTEST_NORMAL             ((uint8_t)0x00)
#define LIS3DSH_XYZ_ENABLE                  ((uint8_t)0x07)
#define LIS3DSH_SERINTER_4WIRE              ((uint8_t)0x00)
#define LIS3DSH_SM_ENABLE                   ((uint8_t)0x01)
#define LIS3DSH_SM_DISABLE                  ((uint8_t)0x00)

typedef struct {
   int16_t X;
   int16_t Y;
   int16_t Z;
} DATA_FROM_AXES_LIS3DSH_t;

void LIS3DSH_READ_DATA(DATA_FROM_AXES_LIS3DSH_t *DATA_FROM_AXCES_STRUCT);

void LIS3DSH_init();

bool LIS3DSH_check_sensor();

