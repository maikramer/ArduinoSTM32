//=================================================================================//
//	Arquivo : arduinoSPI.cpp
//	Projeto : ArduinoSTM32
//	Autor : Maikeu Locatelli
//	Copyright : Locatelli Engenharia
//
//	Descricão: Arquivo fonte para utilizar SPI
//=================================================================================//
//	This file is part of ArduinoSTM32
//	ArduinoSTM32 is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//==================================================================================//
//	Includes
//==================================================================================//
#include <arduino.h>
#include <SPI.h>
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"

// Definições para os SPI1

#define SPIx						SPI1
#define SPIx_CLK					RCC_APB2Periph_SPI1
#define SPIx_CLK_INIT				RCC_APB2PeriphClockCmd
#define SPIx_IRQn					SPI1_IRQn
#define SPIx_IRQHANDLER				SPI1_IRQHandler
#define SPIx_GPIO					GPIOA
#define SPIx_GPIO_CLK				RCC_APB2Periph_GPIOA
#define SPIx_PIN_SCK				GPIO_Pin_5
#define SPIx_PIN_MISO				GPIO_Pin_6
#define SPIx_PIN_MOSI				GPIO_Pin_7

SPI::SPI(uint32_t spiPortNumber) :
		_spiPortNumber(spiPortNumber) {
}

void SPI::begin(SPIFrequency frequency, uint32_t bitOrder,
		uint32_t mode) {
	GPIO_InitTypeDef GPIO_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	/* Configure RCC */
	RCC_PCLK2Config(RCC_HCLK_Div2);

	/* Enable GPIO clock for SPIx */
	RCC_APB2PeriphClockCmd(SPIx_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

	/* Enable SPIx Periph clock */
	RCC_APB2PeriphClockCmd(SPIx_CLK, ENABLE);

	/* Configure SPIx pins: SCK, MISO and MOSI ---------------------------------*/
	GPIO_InitStructure.GPIO_Pin = SPIx_PIN_SCK | SPIx_PIN_MOSI;
	/* Configure SCK and MOSI pins as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPIx_PIN_MISO;
	/* Configure MISO pin as Input Floating  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);

	/* SPI configuration -------------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	if (mode == SPI_MODE0) {
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	} else if (mode == SPI_MODE1) {
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	} else if (mode == SPI_MODE2) {
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	} else if (mode == SPI_MODE3) {
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	}

	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	// Prescaler is divided into PCLK2 (84MHz) to get SPI baud rate/clock speed
	// 256 => 328.125kHz
	// 128 => 656.25kHz
	// 64 => 1.3125MHz
	// 32 => 2.625MHz
	// 16 => 5.25MHz
	// 8  => 10.5MHz
	// 4  => 21.0MHz
	switch (frequency) {
	case SPI_21_0MHZ:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
		break;
	case SPI_10_5MHZ:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
		break;
	case SPI_5_25MHZ:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
		break;
	case SPI_2_625MHZ:
	default:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
		break;
	case SPI_1_3125MHZ:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
		break;
	case SPI_656_25KHZ:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
		break;
	case SPI_328_125KHZ:
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
		break;

	}

	if (bitOrder == LSBFIRST)
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	else
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

	/* Initializes the SPI communication */
	SPI_Init(SPIx, &SPI_InitStructure);
	/* Enable SPI1  */
	SPI_Cmd(SPIx, ENABLE);
}

void SPI::end(void) {
	SPI_I2S_DeInit(SPIx);
}

uint8_t SPI::transfer(uint8_t data) {
	// Wait for TX empty
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_I2S_SendData(SPIx, data);
	// Wait for RX not empty
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
		;
	return SPI_I2S_ReceiveData(SPIx);
}
