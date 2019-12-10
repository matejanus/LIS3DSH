/*
 * spiDriver.h
 *
 *  Created on: Dec 10, 2019
 *      Author: janus
 */

#pragma once
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
void spiDriverInit();

bool spiReadReg(uint8_t spiRegisterAddress, uint8_t data[], uint16_t len);

bool spiWriteReg(uint8_t data[], uint16_t len);

bool spiWriteByte(uint8_t data);

