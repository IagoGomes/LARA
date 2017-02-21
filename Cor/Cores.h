#ifndef CORES_H
#define CORES_H

#include "Cor.h"

#define PRETO 0
#define VERMELHO 1
#define AZUL 2
#define AMARELO 3
#define VERDE 4
#define MARROM 5
#define BRANCO 6
#define LARANJA 7
#define ROSA 8
#define ROXO 9


static  Cor cores[10] ={ Cor(0,0,0),  //PRETO
                         Cor(255,0,0), //VERMELHO
			 Cor(0,0,255), //AZUL 
			 Cor(255,255,0), //AMARELO
			 Cor(0,0,255), //VERDE
			 Cor(139, 90, 43), //MARRON
			 Cor(255, 255, 255), //BRANCO
			 Cor(255, 128, 0), //LARANJA
			 Cor(255, 192, 203), //ROSA
			 Cor(155, 48, 255)}; //ROXO

static int COR_DEFAULT = VERMELHO;

#endif


