/*
 * spiDriver.c
 *
 *  Created on: Dec 10, 2019
 *      Author: janus
 */
#include "spiDriver.h"

static SPI_HandleTypeDef hspi;

void spiDriverInit() {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* SPI1 clock enable */
	__HAL_RCC_SPI1_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**SPI1 GPIO Configuration
	 PA5     ------> SPI1_SCK
	 PA6     ------> SPI1_MISO
	 PA7     ------> SPI1_MOSI
	 */
	GPIO_InitStruct.Pin = SPI1_SCK_Pin | SPI1_MISO_Pin | SPI1_MOSI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	hspi.Instance = SPI1;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi) != HAL_OK) {
		Error_Handler();
	}

}

bool spiReadReg(uint8_t spiRegisterAddress, uint8_t data[], uint16_t len) {
	uint8_t reg = spiRegisterAddress | 0x80;
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi, &reg, len, 1000);
	uint8_t tmp = HAL_SPI_Receive(&hspi, data, len, 1000);
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);
	return tmp == HAL_OK;
}

bool spiWriteReg(uint8_t spiRegisterAddress, uint8_t* data, uint16_t len) {
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);
	uint8_t adddress = spiRegisterAddress;
	HAL_SPI_Transmit(&hspi, &adddress, 1, 1000);

	bool ret = HAL_SPI_Transmit(&hspi, data, 1, 1000);

	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);
	return ret == HAL_OK;
}
bool spiWriteByte(uint8_t spiRegisterAddress, uint8_t data) {
	uint8_t val = data;
	return spiWriteReg(spiRegisterAddress, &val, 1);
}
