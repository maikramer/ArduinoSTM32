//============================================================================
// Projeto : ArduinoSTM32F10x
// Autor : Maikeu Locatelli
// Copyright : Locatelli Engenharia
// Criado em: 15 de ago de 2016
// Descrição :
//============================================================================

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
	//Primordial para o funcionamento das funções de tempo (ex:Delay(), millis())
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
