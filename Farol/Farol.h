#ifndef FAROL_H
#define FAROL_H

#include "../Constantes.h"
#include "../Cor/LED_RGB.h"
#include <Arduino.h>

class Farol {

private:

	int pin_r_1;
	int pin_g_1;
 	int pin_b_1;
 	bool same;
	int pin_r_2;
 	int pin_g_2;
 	int pin_b_2;

public:	

	void ligarFarol(int led=DIREITA_ESQUERDA, int cor = COR_DEFAULT);
	void desligarFarol(int led = DIREITA_ESQUERDA);
	void piscarFarol(unsigned int n = ITERACAO_FAROL, unsigned int tempo = TEMPO_PISCAR , int cor = COR_DEFAULT, int led = DIREITA_ESQUERDA);
	Farol(int pin_r, int pin_g, int pin_b);
	Farol(int pin_r_1, int pin_g_1, int pin_b_1, int pin_r_2, int pin_g_2, int pin_b_2);

};//FimClass

#endif


