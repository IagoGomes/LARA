#ifndef COR_H
#define COR_H

#include "Cores.h"

struct _cor{
 	char r_min; 
	char r_max; 
	char g_min; 
	char g_max;
	char b_min;
	char b_max;
};
typedef struct _cor Cor;

static Cor cores[10] ={{0,0,0,0,0,0}, //PRETO
			{0,0,0,0,0,0},//VERMELHO
			{0,0,0,0,0,0},//AZUL
			{0,0,0,0,0,0},//AMARELO
			{0,0,0,0,0,0},//VERDE
			{0,0,0,0,0,0},//MARROM
			{0,0,0,0,0,0},//BRANCO
			{0,0,0,0,0,0},//LARANJA
			{0,0,0,0,0,0},//ROSA
			{0,0,0,0,0,0} //ROXO
			};



/**
*  Método que verifica se determinado conjunto r,g,b pertence ao intervalo de uma cor, para o sensor de cor
*@param cor:int  index da cor comparada
*@param r:int    
*@param g:int
*@param b:int
*/
bool isColor(int cor, int r, int g, int b){
	return (r>=cores[cor].r_min && r<=cores[cor].r_max) && (g>=cores[cor].g_min && g<=cores[cor].g_max)
		 && (b>=cores[cor].b_min && b<=cores[cor].b_max);
}//fim isColor
			


#endif
