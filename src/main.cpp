//=================================================================================//
//	Arquivo : main.cpp
//	Projeto : ArduinoSTM32
//	Autor : Maikeu Locatelli
//	Copyright : Locatelli Engenharia
//
//	Descricão: Programa utilizado para teste e exemplo da bilblioteca ArduinoSTM32
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
#include <main.h>
#include <arduino.h>

#ifdef DEBUG
#include <diag/Trace.h>
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	//Primordial para o funcionamento das fun��es de tempo (ex:Delay(), millis())
#ifdef DEBUG
	trace_printf("Iniciando Programa\n");
#endif
	configArduino();
	pinMode(LED, OUTPUT);
	while (1)
	{
		digitalWrite(LED, HIGH);
		delay(1000);
		digitalWrite(LED,LOW);
		delay(1000);
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
