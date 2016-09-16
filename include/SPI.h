//=================================================================================//
//	Arquivo : SPI.h
//	Projeto : ArduinoSTM32
//	Autor : Maikeu Locatelli
//	Copyright : Locatelli Engenharia
//
//	Descricão: Arquivo header para o SPI
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
#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_

#include <stdint.h>

typedef enum SPIFrequency {
    SPI_21_0MHZ      = 0, /**< 21 MHz */
    SPI_10_5MHZ      = 1, /**< 10.5 MHz */
    SPI_5_25MHZ      = 2, /**< 5.25 MHz */
    SPI_2_625MHZ     = 3, /**< 2.625 MHz */
    SPI_1_3125MHZ    = 4, /**< 1.3125 MHz */
    SPI_656_25KHZ    = 5, /**< 656.25 KHz */
    SPI_328_125KHZ   = 6, /**< 328.125 KHz */
} SPIFrequency;

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

class SPI
{
public:
    SPI(uint32_t spiPortNumber); // Atualmente somente SPI1
    void begin(SPIFrequency frequency, uint32_t bitOrder, uint32_t mode);
    void end(void);
    uint8_t transfer(uint8_t data);

private:
    uint32_t _spiPortNumber;
};

#endif /*INCLUDE_SPI_H*/
