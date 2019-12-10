/*
 * spiDriver.c
 *
 *  Created on: Dec 10, 2019
 *      Author: janus
 */
#include "spiDriver.h"

static SPI_HandleTypeDef hspi;

void spiDriverInit() {
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

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /* USER CODE BEGIN SPI1_MspInit 0 */

	  /* USER CODE END SPI1_MspInit 0 */
	    /* SPI1 clock enable */
	    __HAL_RCC_SPI1_CLK_ENABLE();

	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**SPI1 GPIO Configuration
	    PA5     ------> SPI1_SCK
	    PA6     ------> SPI1_MISO
	    PA7     ------> SPI1_MOSI
	    */
	    GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /* USER CODE BEGIN SPI1_MspInit 1 */

	  /* USER CODE END SPI1_MspInit 1 */
}

bool spiReadReg(uint8_t spiRegisterAddress, uint8_t data[], uint16_t len) {
	uint8_t reg = spiRegisterAddress | 0x80;
	HAL_SPI_Transmit(&hspi, &reg, len, 1000);
	return HAL_SPI_Receive(&hspi, data, len, 1000) == HAL_OK;
}
bool spiWriteReg(uint8_t data[], uint16_t len) {
	return HAL_SPI_Transmit(&hspi, data, len, 1000) == HAL_OK;
}
bool spiWriteByte(uint8_t data) {
	uint8_t val = data;
	return spiWriteReg(&val, 1);
}
