
/**-------------------------------------------------------------------------------------------------------------------------------
--------@@@@-----------------------@@@@@@@@@------------@@@@@@@@@@@@-----------------@@@@@@@@@------------------------------------
--------@@@@----------------------@@@@@@@@@@@-----------@@@@@@@@@@@@@---------------@@@@@@@@@@@-----------------------------------
--------@@@@---------------------@@@@-----@@@@----------@@@@------@@@@-------------@@@@-----@@@@----------------------------------
--------@@@@--------------------@@@@-------@@@@---------@@@@-------@@@@-----------@@@@-------@@@@---------------------------------
--------@@@@-------------------@@@@@@@@@@@@@@@@@--------@@@@-------@@@@----------@@@@@@@@@@@@@@@@@--------------------------------
--------@@@@------------------@@@@@@@@@@@@@@@@@@@-------@@@@@@@@@@@@@@@---------@@@@@@@@@@@@@@@@@@@-------------------------------
--------@@@@-----------------@@@@-------------@@@@------@@@@@@@@@@@@@@---------@@@@-------------@@@@------------------------------
--------@@@@----------------@@@@---------------@@@@-----@@@@-------@@@@-------@@@@---------------@@@@-----------------------------
--------@@@@@@@@@@@@@@@----@@@@-----------------@@@@----@@@@--------@@@@-----@@@@-----------------@@@@----------------------------
--------@@@@@@@@@@@@@@@---@@@@-------------------@@@@---@@@@---------@@@@---@@@@-------------------@@@@---------------------------
----------------------------------------------------------------------------------------------------------------------------------
--------------------------000----------000000--000000000--------00000000----------------------------------------------------------
--------------------------000---------0000000--00000000000-----0000000000---------------------------------------------------------
--------------------------000--------000--000--000------000----00----000----------------------------------------------------------
--------------------------000-------000---000--0000000000000-------000------------------------------------------------------------
--------------------------000-------------000--000000000000------000--------------------------------------------------------------
--------------------------00000000--------000--000-------000----0000000000--------------------------------------------------------
--------------------------00000000--------000--000--------000---0000000000--------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
Título: Biblioteca LARA
Comentário: Biblioteca de operação do robô (L1R2) do LARA
Projeto: Laboratório Remoto em Ambiente Virtual de Aprendizagem
Autores: Iago Pachêco, Vinicius Brito, Thómas Jérfersson e Raphael Cristian
Data da Última Versão: 23 de Agosto de 2015
Versão: 2.0
--------------------------------------------------------------------------------------------------------------------------------**/

#ifndef LARA_h
#define LARA_h


/**-----------Importação de Bibliotecas Auxiliares------------------**/
//biblioteca com as funções do arduino
#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif


#include "Carro/Carro.h"//biblioteca para o controle do carro (L1R2)
#include "Constantes.h"
#include "Farol/Farol.h"
#include "Sensores/Sensores.h"

class Carro;
class Sensores;
class Farol;

/*****************Definição da Classe LARA***************************/

class LARA{ 	
public:
/*-------------Método de escape para erros ---------------------**/

/**
** Método que interrompe a execução de códigos quando ocorre algum erro semântico
**/
void end();

//------------------------Construtor----------------------------------//
/**
** Método construtor da classe L1R2
--    Inicializa os pinos dos componentes e define o objeto serial para 
--      comunicação com os usuários
**/
LARA(); 	

//-----------------------Métodos para Leitura de sensores -----------//
/**
** Método que retorna a leitura do sensor de infravermelho
--   O Sensor infravermelho é usado no módulo seguidor de linha do robô
**@param indexIR int : indíce do sensor infravemelhor
--		        0 - Direita
--		        1 - Esquerda
--		        2 - Centro
**@param type int : indíce que determina o tipo de leitura do sensor:
--		        3 - Digital
--		        4 - Analogico
**@return leituraIR int : leitura do sensor de Infravermelho
--		          0 ou 1 para leituras digitais
--		          0 a 1023 para leituras analógicas
--			  -1 - ERRO
**/
int leituraIR(int  indexIR , int type = DIGITAL);

/**
** Método que retorna a leitura do sensor de luz (LDR)
--    O sensor LDR é usado para o retorno do robô ao ponto inicial
**@param indexLDR int : indice do sensor LDR
--		          0 - Direita
--		          1 - Esquerda
--		          2 - Centro
--		         
**@return leituraLDR int: leitura analógica do sensor LDR de indíce indexLDR
--		           a leitura possui range de 0 a 1023
--			  -1 - ERRO
--
**/
int leituraSensorLuz(int indexLDR);

/**
** Método que retorna a leitura do sensor de ultrasso
--     O sensor de ultrassom é usado para calcular a distância do robô em relação à 
--       um obstáculo
**@param indexUltrassom int: indíce do sensor ultrassom
--		              5 - frente
--		              0 - direita
--		              1 - esquerda
--		             
**@param type int: unidade de medida da distância          
**@return distanciaUltrassom int : calculo de distância em centímetros do sensor 
--                                    ultrassom
--                                -1 - ERRO
**/
int distancia(int indexUltrassom , int type=CM);


/**
**Método que faz a leitura de todos os sensores de luz 
-- Este procedimento realiza a leitura dos sensores de luz, passando o resultado por referência.
--   Desta forma, as variáveis passadas por parâmetros terão seus valores alterados para o valor
--     das leitura dos sensores.
**@param ldrDireita &int : referência para a leitura do sensor da direita
**@param ldrEsquerda &int : referência para a leitura do sensor da esquerda
**@param ldrCentro &int : referência para a leitura do sensor do centro
**@return void
**/
void getLeiturasSensorDeLuz(int *ldrDireita, int *ldrEsquerda, int *ldrCentro);

/**
**Método que faz a leitura de todos os sensores de infravermelho
-- Este procedimento realiza a leitura dos sensores de infravermelho, passando o resultado por referência.
--   Desta forma, as variáveis passadas por parâmetros terão seus valores alterados para o valor
--     das leitura dos sensores.
**@param irDireita &int : referência para a leitura do sensor da direita
**@param irEsquerda &int : referência para a leitura do sensor da esquerda
**@param irCentro &int : referência para a leitura do sensor do centro
**@param type int : tipo de leitura, se é digital ou analógica
--                  se o interesse for digital, então a constante DIGITAL deve ser passada por
--                   parâmetro. Já se o interesse for na leitura analógica, então a constante
--                  ANALOGICO deve ser passado por parâmetro
** @return void
**/
void getLeiturasIR(int *irDireita, int *irEsquerda, int *irCentro, int type = DIGITAL);

/**
**Método que faz a leitura de todos os sensores de ultrassom, retornando o resultado conforme a unidade de medida passado por parâmetro
-- Este procedimento realiza a leitura dos sensores de ultrasssom, passando o resultado por referência.
--   Desta forma, as variáveis passadas por parâmetros terão seus valores alterados para o valor
--     das leitura dos sensores.
**@param ultDireita &int : referência para a leitura do sensor da direita
**@param ultEsquerda &int : referência para a leitura do sensor da esquerda
**@param ultFrente &int : referência para a leitura do sensor da frente
**@param ultTras &int : referÊncia para a leitura do sensor de tras
**@param ultFrenteDir &int : referência para a leitura do sensor da frente, posicionado à direita
**@param ultFrenteEsq &int : referência para a leitura do sensor da frente, posicionado à esquerda
**@param type int : unidade de medida dos sensores de ultrassom, que pode assumir o valor de 
--                  CM, POL ou M. Por padrão é CM.
** @return void
**/
void getLeiturasUltrassom(int *ultDireita, int *ultEsquerda, int *ultFrente, int *ultTras, int *ultFrenteDir, int *ultFrenteEsq, int type=CM);

/**
** Método que faz a leitura de todos os eixos do sensor de bússola
-- Este procedimento realiza a leitura do sensor magnetômetro (gy-271), passando o resultado dos eixos por referência.
-- 	Desta forma, as variáveis passadas por parâmetros terão seus valores alterados por referência.
**@param xAxis &int : referência para o eixo x da leitura da bússola
**@param yAxis &int : referência para o eixo y da leitura da bússola
**@param zAxis &int : referência para o eixo z da leitura da bússola
**@return void
**/
void getLeiturasBussola(int *xAxis, int *yAxis, int *zAxis);


/** 
** Método que retorna a leitura do angulô do robô em relação ao norte magnético
** @return angulo float : ângulo do robô em relação ao norte magnético
**/
float leituraAnguloNorteMagnetico();

/**
** Método que retorna a leitura do ângulo do robô em relação à um ângulo de referência do robô
**@return angulo float : ângulo do robô em relação ao ângulo de referência (norte do robô)
**/
float leituraAnguloReferencia();

/**
** Método que modifica o ângulo de referência doo robô. 
-- O ângulo de referÊncia do robô pode ser entendido como um "norte", definido para o robô. 
-- O robô será capaz de calcular qual a angulação necessária para se orientar para esse "norte"
-- em qualquer momento de sua operação, independente de sua orientação atual. 
**@param angulo float: ângulo de referÊncia do robô, esse ângulo deverá estar entre o entervalo de 
--                      0º -> 360º
**@return void
**/
void setAnguloReferencia(float angulo);

/**
** Método que retorna o Ângulo de referência atual do robô
** @return angulo float: Ângulo de referÊncia atual do robô
**/
float getAnguloToReferencia();


//------------------Métodos de estratégia do robô ---------------------------//

/**
**Método que retorna o índice do sensor que atualmente está na linha
--   Este método pode ser usado no algoritmo para seguir linha. Ele disponibiliza uma
--     interfacie mais fácil para quem está començando a programar e pretende fazer o 
--     robô seguir a linha.
**@return line int : índice do sensor que está atualmente lendo a linha
--		     DIREITA 0
--		     ESQUERDA 1
--		     CENTRO 2
--		     -1 se nenhum sensor estiver lendo a linha
**/
int getLinha();

/** 
** Método que retorna o índice do sensor que está lendo a menor distância relativa à um
--    obstáculo
--    Este método pode ser usado no algoritmo de desvio de obstáculos. Ele disponibiliza 
--      uma interface mais fácil para manipular no referido algoritmo.
**@return indiceUlt int : índice do sensor de ultrassom que está atualmente lendo a menor 
--                       distância relativa à um obstáculo
--                       DIREITA 0
--                       ESQUERDA 1
--                       FRENTE 5
--                       -1 - ERRO
**/
int getMinDistancia();


/** 
** Método que retorna o índice do sensor que está lendo a maior distância relativa à um
--   obstáculo
--   Este método pode ser usado no algoritmo de desvio de obstáculos. Ele disponibiliza uma 
--     interface mais fácil para manipular no referido algoritmo.
**@return indiceUlt int : índice do sensor de ultrassom que está atualmente lendo a maior
--                          distância relativa à um obstáculo
--		          DIREITA 0
--		          ESQUERDA 1
--		          FRENTE 5
--		          -1 - ERRO
**/
int getMaxDistancia();

/**--------------------------Métodos de Ação do Robô----------------------------------**/
/**
**Método que liga os Faróis do robô
**@param cor Cor : cor do farol- Se não for especificado ele assume a cor padrão(azul)
**@param led int : indicação do farol
--                 DIREITA - farol da direita
--                 ESQUERDA - farol da esquerda
--                 DIREITA_ESQUERDA - ambos os faróis
**@return void
**/
void ligarFarol(int led = DIREITA_ESQUERDA, int cor=COR_DEFAULT);	

/**
** Método que desliga os Faróis do robô
**@param led int : indicação do farol
--                 DIREITA - farol da direita
--                 ESQUERDA - farol da esquerda
--                 DIREITA_ESQUERDA - ambos os faróis
**@return void
**/
void desligarFarol(int led=DIREITA_ESQUERDA);

/**
**Método que faz o farol piscar n vezes
**@param n unsigned int : quantidades de vezes que o farol deve piscar
**@param led int : indicação do farol
--                 DIREITA - farol da direita
--                 ESQUERDA - farol da esquerda
--                 DIREITA_ESQUERDA - ambos os faróis
**@param cor Cor : cor do farol- Se não for especificado ele assume a cor padrão(azul)
**@param tempo int: intervalo de tempo que o farol deve ficar ligado (frequência da ação)
**                  o tempo é definido em milissegundos
**@return void
**/
void piscarFarol(unsigned int n=ITERACAO_FAROL, unsigned int tempo=TEMPO_PISCAR, int cor  = COR_DEFAULT, int led=DIREITA_ESQUERDA);

/************
Métodos de Movimentos
*************/

/**
**Método que faz o robô se locomover para frente 
**@param tempo float  :   tempo que o robô deve seguir em frente
**@param velocidade int : velocidade que o robô deve executar o percurso 
--                        velocidade recebe por default o valor de VELOCIDADE_DEFAULT = 5cm/seg
**@return void
**/
void frente(long &tempo, unsigned int velocidade = VELOCIDADE_DEFAULT);

/**
**Método que faz o robô se locomover para frente 
**@param distancia int  : distancia que o robô deve seguir em frente
--                        distancia recebe por default o valor de DIST_DEFAULT = 10cm
--@param type int       : unidade de medida da distância
**@param velocidade int : velocidade que o robô deve executar o percurso 
--                        velocidade recebe por default o valor de VELOCIDADE_DEFAULT = 5cm/seg
**@return void
**/
void frente(unsigned int distancia=DISTANCIA_DEFAULT_CM, int type=CM, unsigned int velocidade = VELOCIDADE_DEFAULT);


/**
**Método que faz o robô se locomover de marcha à ré 
**@param tempo float  :  tempo que o robô deve seguir de marcha à ré
**@param velocidade int : velocidade que o robô deve executar o percurso 
--                        velocidade recebe por default o valor de VELOCIDADE_CONST = 5cm/seg
**@return void
**/
void re(long &tempo, unsigned int velocidade = VELOCIDADE_DEFAULT);

/**
**Método que faz o robô se locomover de marcha à ré 
**@param distancia int  : distancia que o robô deve seguir de marcha à ré
--                        distancia recebe por default o valor de DIST_CONST = 10cm
**@param type int       : Unidade de medida da distancia
**@param velocidade int : velocidade que o robô deve executar o percurso 
--                        velocidade recebe por default o valor de VELOCIDADE_CONST = 5cm/seg
**@return void
**/
void re(unsigned int distancia=DISTANCIA_DEFAULT_CM, int type=CM, unsigned int velocidade = VELOCIDADE_DEFAULT);

/**
**Método que faz o robô rotacionar sobre seu eixo no sentido da direita por uma angulação 
**@param angulo int : angulação que o robô pode virar. 
--                     angulo compreende o intervalo de 0 - 360º                     
**@return void
**/
void direita(int angulo = ANGULACAO_DEFAULT);

/**
**Método que faz o robô rotacionar sobre seu eixo no sentido da esquerda por uma angulação 
**@param angulo int : angulação que o robô pode virar. 
--                     angulo compreende o intervalo de 0 - 360º                     
**@return void
**/
void esquerda(int angulo = ANGULACAO_DEFAULT);

/**
**Método que para a execução de qualquer movimento do L1R2
**@return void
**/
void parar();

/**
**Método que muda a velocidade do robô
**@param velocidade int : nova velocidade
--                        o valor deve ser positivo
**@return void
**/
void setVelocidade(unsigned int velocidade);	

/**
**Método que retorna a velocidade do robô
**@return velocidade int 
**/
int getVelocidade();
};

#endif
