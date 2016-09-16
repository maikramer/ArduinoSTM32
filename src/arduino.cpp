//=================================================================================//
//	Arquivo : arduino.cpp
//	Projeto : ArduinoSTM32
//	Autor : Maikeu Locatelli
//	Copyright : Locatelli Engenharia
//
//	Descricão: Arquivo principal para as funções arduino
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
#include <cortexm/ExceptionHandlers.h>

#ifdef DEBUG
#include <diag/Trace.h>
#endif

GPIOPin pins[] =
{
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_0, 0 }, // 0 = PA0
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_1, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_2, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_3, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_4, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_5, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_6, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_7, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_8, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_9, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_10, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_11, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_12, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_13, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_14, 0 },
	{ RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_15, 0 }, // 15 = PA15

	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_0, 0 }, // 16 = PB0
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_1, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_2, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_3, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_4, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_5, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_6, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_7, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_8, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_9, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_10, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_12, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_13, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_14, 0 },
	{ RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_15, 0 }, // 31 = PB15

	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_0, 0 }, // 32 = PC0
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_1, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_2, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_3, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_4, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_5, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_6, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_7, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_8, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_9, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_10, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_11, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_12, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_13, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_14, 0 },
	{ RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_15, 0 }, // 47 = PC15
};

#define NUM_PINS (sizeof(pins) / sizeof(GPIOPin))
volatile uint32_t systick_count = 0;

void configArduino()
{
#ifdef DEBUG
	trace_printf("Configurando Timer SysTick\n");
#endif
	configSysTick();
}
void configSysTick()
{
	/* Configura SysTick para 1ms de interrup��o  */
	if (SysTick_Config(SystemCoreClock / 1000))
	{
#ifdef DEBUG
		trace_printf("Falha ao Inicializar o SysTick\n");
#endif
	}

	/* Configura prioridade do SysTick para M�xima */
	NVIC_SetPriority(SysTick_IRQn, 0x0);
}

extern "C"
{
// Called every 1 ms
void SysTick_Handler(void)
{
	systick_count++;
}
}

uint32_t millis()
{
    return (systick_count);
}

void delay(uint32_t ms)
{
    uint32_t start = millis();

    while (millis() - start < ms)
	;
}

void pinMode(uint8_t pin, GPIOPinMode mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//Testa se o pino existe
	if (pin > NUM_PINS)
	{
#ifdef DEBUG
		trace_printf("Pino n�o existe neste Microcontrolador\n");
#endif
		return;
	}

	// Habilita o Clock
	RCC_APB2PeriphClockCmd(pins[pin].portClk, ENABLE);
	//Inicializa o Pino
	GPIO_InitStructure.GPIO_Pin = pins[pin].pin;
	switch (mode)
	{
	case INPUT:{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		break;
	}
	case INPUT_PULLUP:{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		break;
	}
	case OUTPUT:{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		break;
	}
	default:{
#ifdef DEBUG
		trace_printf("Modo para o pino n�o existe");
#endif
		return;
	}
	}

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(pins[pin].port, &GPIO_InitStructure);

	pins[pin].init = true;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
	if (pin > NUM_PINS)
	{
#ifdef DEBUG
		trace_printf("Pino nao existe neste Microcontrolador\n");
#endif
		return;
	}
#ifdef DEBUG
	if (!pins[pin].init)
	{
		trace_printf("Pino %i nao inicializado\n", pin);
	}
#endif
	if (val)
		GPIO_SetBits(pins[pin].port, pins[pin].pin);
	else
		GPIO_ResetBits(pins[pin].port, pins[pin].pin);
}

uint8_t digitalRead(uint8_t pin)
{
	if (pin > NUM_PINS)
	{
#ifdef DEBUG
		trace_printf("Pino n�o existe neste Microcontrolador\n");
#endif
		return (0);
	}
#ifdef DEBUG
	if (!pins[pin].init)
	{
		trace_printf("Pino %i n�o inicializado\n", pin);
	}
#endif
	return (GPIO_ReadInputDataBit(pins[pin].port, pins[pin].pin));
}
