//============================================================================
// Projeto : ArduinoSTM32F10x
// Autor : Maikeu Locatelli
// Copyright : Locatelli Engenharia
// Criado em: 15 de ago de 2016 
// Descrição : Header para funções de compatibilidade com Arduino.
//============================================================================ 
#ifndef INCLUDE_ARDUINO_H_
#define INCLUDE_ARDUINO_H_

#include <stdint.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

typedef enum GPIOPinMode
{
	OUTPUT, 		//Saida Padrão
	INPUT,		//Entrada Padrão
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

void configArduino();
void configSysTick();
uint32_t millis();
void delay(uint32_t ms);
void pinMode(uint8_t pin, GPIOPinMode mode);
void digitalWrite(uint8_t pin, uint8_t val);
uint8_t digitalRead(uint8_t pin);

#endif /* INCLUDE_ARDUINO_H_ */
