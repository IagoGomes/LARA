#ifndef PINOS_LARA_H
#define PINOS_LARA_H

/*---------------Definindo a Pinagem dos Componentes--------------**/						

/* ===================  MOTORES ==================*/
//      MOTOR            PINO       COR_PINO
#define MOTOR_DIREITA_N   4//6       // branco
#define MOTOR_DIREITA_P   5//7       // marron
#define MOTOR_ESQUERDA_N  12//5       // azul
#define MOTOR_ESQUERDA_P  6//4       // laranja
        
/* ===================  ENCODERS ==================*/
//      ENCODER          PINO       COR_PINO
#define ENCODER_D1        2       // azul   
#define ENCODER_D2        3       // branco (roxo)
#define ENCODER_E1        18      // amarelo (rosa)
#define ENCODER_E2        19      // laranja

/* ===================  LDRs ==================*/
//      LDR                 PINO     COR_PINO
#define PIN_LDR_DIREITA      A8   // branco
#define PIN_LDR_ESQUERDA     A6   // branco
#define PIN_LDR_CENTRO       A7   // branco
		 
/* ===================  ULTRASSOM - HCSR04  ==================*/
//      ULTRASSOM                     PINO     COR_PINO
#define PIN_ULT_ECHO_FRENTE           48     // verde
#define PIN_ULT_TRIG_FRENTE           49     // branco
#define PIN_ULT_ECHO_FRENTE_DIREITA   50     // verde
#define PIN_ULT_TRIG_FRENTE_DIREITA   51     // branco
#define PIN_ULT_ECHO_FRENTE_ESQUERDA  46     // verde
#define PIN_ULT_TRIG_FRENTE_ESQUERDA  47     // branco
#define PIN_ULT_ECHO_DIREITA          52     // verde
#define PIN_ULT_TRIG_DIREITA          53     // branco
#define PIN_ULT_ECHO_ESQUERDA         44     // verde
#define PIN_ULT_TRIG_ESQUERDA         45     // branco	 
#define PIN_ULT_ECHO_TRAS             42     // verde
#define PIN_ULT_TRIG_TRAS             43     // branco

/* ===================  LEDs RGB - FARÓIS  ==================*/
//      LED                   PINO       COR_PINO
#define PIN_LED_DIREITA_R      11     // vermelho
#define PIN_LED_DIREITA_G      13     // verde
#define PIN_LED_DIREITA_B      12     // azul
#define PIN_LED_ESQUERDA_R     8      // vermelho
#define PIN_LED_ESQUERDA_G     10     // verde
#define PIN_LED_ESQUERDA_B     9      // azul


/* ==================== MAGNENÔMETRO GY271  ==================*/
//      LED                   PINO       COR_PINO
#define PIN_BUSSOLA_SDA        20     // azul
#define PIN_BUSSOLA_SCL        21     // branco

#endif
