#ifndef _rgbES_H
#define _rgbES_H

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

struct _rgb_data {
        int r;
        int g;
        int b;
}; 
typedef struct _rgb_data rgb;

static rgb _rgb[10]={{0,0,0},       //PRETO
                     {255,0,0},     //VERMELHO
                     {0,0,255},     //AZUL
                     {128,128,0},   //AMARELO
		     {0,255,0},     //VERDE
                     {200,90,90},   //MARROM
                     {255,255,255}, //BRANCO
                     {255,128,0},   //LARANJA
		     {255,192,203}, //ROSA
		     {180,48,255},  //ROXO
                    }; 

static Cor cores[10];

static int COR_DEFAULT = VERMELHO;

#endif


