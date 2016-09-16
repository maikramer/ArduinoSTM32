//=================================================================================//
//	Arquivo : arduino.h
//	Projeto : ArduinoSTM32
//	Autor : Maikeu Locatelli
//	Copyright : Locatelli Engenharia
//
//	Descricão: Arquivo header para as funções arduino
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
#ifndef INCLUDE_ARDUINO_H_
#define INCLUDE_ARDUINO_H_

#include <stdint.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

typedef enum GPIOPinMode
{
	OUTPUT, 		//Saida Padr�o
	INPUT,		//Entrada Padr�o
	INPUT_PULLUP,	//Entrada utilizando resistor interno de PULLUP
} GPIOPinMode;

typedef struct
{
	uint32_t portClk;
	GPIO_TypeDef* port;
	uint16_t pin;
	uint16_t init;//16 Bits para alinhar o struct
} GPIOPin;

#define HIGH 0x1
#define LOW  0x0

#define LSBFIRST 0x0
#define MSBFIRST 0x1

#define CHANGE 	1
#define FALLING	2
#define RISING 	3

void configArduino();
void configSysTick();
uint32_t millis();
void delay(uint32_t ms);
void pinMode(uint8_t pin, GPIOPinMode mode);
void digitalWrite(uint8_t pin, uint8_t val);
uint8_t digitalRead(uint8_t pin);

#endif /* INCLUDE_ARDUINO_H_ */
