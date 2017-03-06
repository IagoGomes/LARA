
#ifndef Constantes_H
#define Constantes_H

//#include <Arduino.h>
#include "Pinos.h"
#include "Cor/LED_RGB.h"

#define DIREITA  0
#define ESQUERDA 1
#define CENTRO   2
#define FRENTE   2
#define RE       6
#define TRAS     3
#define FRENTE_DIREITA  4
#define FRENTE_ESQUERDA 5
#define DIREITA_ESQUERDA 7
#define POL 7
#define M 8
#define CM 9

//Tipo de leitura para o sensor de infravermelho
#define DIGITAL   10
#define ANALOGICO  4
//LINHA 
#define DISTANCIA_MAXIMA     300
#define DISTANCIA_DEFAULT_CM  10
#define ANGULACAO_DEFAULT     90

#define TEMPO_DEFAULT 0.5
#define DIST_DEFAULT 10
#define VELOCIDADE_DEFAULT     5
#define ITERACAO_DEFAULT       1
#define RANGE_VELMIN           5
#define RANGE_VELMAX          17
#define RANGE_ANGMIN       -1080
#define RANGE_ANGMAX        1080
#define VEL_TO_PWM(x)       map(x,5,17,120,255) //Escala suposta 5cm/1seg/120PMW  e 17cm/1seg/255PWM
 

//macros para controle dos métodos de piscar dos faróis
#define ITERACAO_FAROL  10 //quantidade de iterações para o farol piscar
#define TEMPO_PISCAR   500  //intervalo de tempo que o farol deve ficar ligados, na ação de piscar 

#endif
