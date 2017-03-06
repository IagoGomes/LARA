#ifndef SENSORES_H
#define SENSORES_H

#include "../NewPing/NewPing.h"
#include "../Compass/Compass.h"
#include "../SensorCor/SensorCor.h"
#include "../Cor/Cores.h"
#include "../Constantes.h"

class NewPing;
class Sensores{
	private:
		#define  SAMPLE 10
		NewPing *sonar;
		Compass *compass;
	public: 
		Sensores();
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
int leituraSensorLuz(int index);

/**
** Método que retorna a leitura do sensor de ultrassom
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
int distancia(int index, int un=CM);

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
void getLeiturasSensorDeLuz(int *ldrDireita, int *ldrEsquerda, int * ldrCentro);

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
float getAnguloReferencia();

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

		int getMinDistancia();
int getMaxDistancia();
		void getLeituraSensorCor(int *corDireita, int *corCentro, int *corEsquerda);
		int leituraSensorCor(int index);
};

#endif
