
#include "LARA.h"
#include "Farol/Farol.h"
#include "Carro/Carro.h"
#include "Sensores/Sensores.h"

/*--------------Criando o objeto para controle do carro---------**/
Carro *carro;  
/*--------------Criando o objeto para controle dos sensores---------**/
Sensores *sensor;
/*--------------Criando o objeto para controle dos faróis---------**/
Farol *farol;

/*****************************************************
               FUNÇÕES PÚBLICAS
*****************************************************/
//void end();
//int distancia(int indexUltrassom , int type=CM);

/**
** Método Construtor da Classe
-- 	Seta a pinagem do robô
**/
 LARA::LARA(){   
	
}//fim Construtor

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MÉTODOS DE ACESSO AOS SENSORES >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
    //----------------Implementação de Métodos para Leitura de sensores------------------------------//

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
int LARA::leituraIR(int  indexIR , int type){
	return -1;
}//fim leituraIR

/**
 ** Método que retorna a leitura do sensor de luz (LDR)
 --    O sensor LDR é usado para o retorno do robô ao ponto inicial
 **@param indexLDR int : indice do sensor LDR
 --		          0 - Direita
 --		          1 - Esquerda
 -- 	          2 - Centro
 --		         
 **@return leituraLDR int: leitura analógica do sensor LDR de indíce indexLDR
 --		           a leitura possui range de 0 a 1023
 --			    -1 - ERRO
 **/
int LARA:: leituraSensorLuz(int indexLDR){
			return -1;

}//fim leituraLDR

/**
** Método que retorna a leitura do sensor de ultrasso
--     O sensor de ultrassom é usado para calcular a distância do robô em relação à um obstáculo
**@param indexUltrassom int: indíce do sensor ultrassom
--		              5 - frente
--		              0 - direita
--		              1 - esquerda
--			      
**@param type int: unidade de medida da distância          
**@return distanciaUltrassom int : calculo de distância em centímetros do sensor ultrassom
--				   -1 - ERRO
**/
int LARA::distancia(int indexUltrassom , int type){
	return -1;
}//fim distancia


/**
** (Passagem por Referência)
** Método que seta em três variáveis o valor das leituras dos sensores de LDR
**@param ldrDireita &int : variável para a leitura do ldr da direita
**@param ldrEsquerda &int : variável para a leitura do ldr da esquerda
**@param ldrCentro &int: variável pa
ra a leitura do ldr do centro
**@return void
**/
void LARA::getLeiturasSensorDeLuz(int *ldrDireita, int *ldrEsquerda, int *ldrCentro){
        *ldrDireita=leituraSensorLuz(DIREITA);
        *ldrEsquerda=leituraSensorLuz(ESQUERDA);
        *ldrCentro=leituraSensorLuz(CENTRO);
}//fim getLeiturasLDR


/**
** (Passagem por Referência)
** Método que seta em três variáveis o valor das leituras dos sensores de ultrassom
**@param ultDireita &int : variável para a leitura do ultrassom da direita
**@param ultEsquerda &int : variável para a leitura do ultrassom da esquerda
**@param ultFrente &int: variável para a leitura do ultrassom do frente
**@param ultTras &int : variável para a leitura do ultrassom de tras
**@param type int: unidade de medida da distância calculada pelos sensores de ultrassom
--                  pode assumir os valores das constantes : CM - centímetro, POL - polegadas e 
--                  M - metros;
**@return void
**/
void LARA:: getLeiturasUltrassom (int *ultDireita, int *ultEsquerda, int *ultFrente, int *ultTras, 
	                                           int *ultFrenteDireita, int *ultFrenteEsquerda, int type){
     *ultDireita=distancia(DIREITA, type);
     *ultEsquerda=distancia(ESQUERDA, type);
     *ultFrente=distancia(FRENTE, type);
     *ultTras=distancia(TRAS, type);
     *ultFrenteEsquerda = distancia(FRENTE_ESQUERDA, type);
     *ultFrenteDireita = distancia(FRENTE_DIREITA, type);
}//fim getLeiturasLDR

/**
** (Passagem por referência)
** Método que seta as três variáveis para os valores das leituras dos sensores de infravermelho
--      no módulo seguidor de linha
-- caso a leitura falhe, o programa é interrompido o robô é redirecionado para um loop infinito 
-- sem realizar nenhuma ação
**@param irDireita &int : referência para a leitura do sensor da direita
**@param irEsquerda &int : referência para a leitura do sensor da esquerda
**@param irCentro &int : referência para a leitura do sensor do centro
**@param type int : tipo de leitura, se é digital ou analógica
--                  se o interesse for digital, então a constante DIGITAL deve ser passada por
--                   parâmetro. Já se o interesse for na leitura analógica, então a constante
--                  ANALOGICO deve ser passado por parâmetro
** @return void
**/
void LARA:: getLeiturasIR(int *irDireita, int *irEsquerda, int *irCentro, int type){
}//fim getLeiturasIR

/** 
** (Passagem por referência)
** Método que seta as três variáveis para os valores das leituras dos eixos dó sensor magnetômetro (gy-271 Bússola)
**@param xAxis float : eixo x
**@param yAxis float : eixo y
**@param zAxis float : eixo z
**@return void
**/
void  LARA:: getLeiturasBussola(int *xAxis, int *yAxis, int *zAxis){
}//fim getLeiturasBussola

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>MÉTODOS DE ESTRATÉGIAS DOS SENSORES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/**
**Método que retorna o índice do sensor que atualmente está na linha
--   Este método pode ser usado no algoritmo para seguir linha. Ele disponibiliza uma interfacie mais fácil para quem está  
--   començando a programar e pretende fazer o robô seguir a linha.
**@return line int : índice do sensor que está atualmente lendo a linha
--		     DIREITA 0
--		     ESQUERDA 1
--		     CENTRO 2
--          -1 se nenhum sensor estiver lendo a linha
**/   
int LARA:: getLinha(){
	return -1;//nenhum sensor lÊ a linha
}//fim getLinha
		
/** 
** Método que retorna o índice do sensor que está lendo a menor distância relativa à um obstáculo
--     Este método pode ser usado no algoritmo de desvio de obstáculos. Ele disponibiliza uma interface mais fácil para manipular no 
--     referido algoritmo.
**@return indiceUlt int : índice do sensor de ultrassom que está atualmente lendo a menor distância relativa à um obstáculo
--		          DIREITA 0
--		          ESQUERDA 1
--		          FRENTE 5
--		          -1 - ERRO
**/
int LARA:: getMinDistancia(){
	return -1; // ERRO
}//fim getMinDistancia

/** 
** Método que retorna o índice do sensor que está lendo a maior distância relativa à um obstáculo
--     Este método pode ser usado no algoritmo de desvio de obstáculos. Ele disponibiliza uma interface mais fácil para manipular 
--     no referido algoritmo.
**@return indiceUlt int : índice do sensor de ultrassom que está atualmente lendo a maior distância relativa à um obstáculo
--		          DIREITA 0
--		          ESQUERDA 1
--		          FRENTE 5
--  			  -1 - ERRO
**/
int LARA:: getMaxDistancia(){
	return -1;//ERRO
}//fim getMaxDistancia


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MÉTODOS DE MOVIMENTO >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
	/*Considerações Gerais
	>> As funções de movimento que executam uma traslação na posição do robô é controlado pelo 
	         pela algoritmo de controle conhecido como Proporcional Integral e Derivativo (PID). 
	         As variáveis e constantes do controle PID são atualizadas via evento disparado tempo (timer).
	         É importante salientar que neste momento há uma questão de projeto a ser discutido. O Timer, 
	         interrompe a execução do código para realizar a atualização das funções (chamada do método "updateL1R2"),
	         Desta forma, sua execução leva a uma interrupção no fluxo do código. Assim sendo, quanto menor for
	         o intervalo para a atualização, mais preciso será os valores, contuto, mais interrupções no fluxo de código ocorrerá
	   >> As funções de rotação do robô são baseados no modelo cinemático, e leva em conta a quantidade de interrupções dos
	   		 encoders que são necessários para uma rotação completa da roda. Desta forma, é possível calcular as interrupções 
	   		 necessárias para executar o movimento de rotação.
	   >> A velocidades dos motores, definidos pelo sinal PWM, é autoregulável pelo controle PID, bem como, seu valor inicial pode
	         ser setado pelo usuário da biblioteca
	   >> Todos os movimentos do robô são interrompidos caso um obstáculo seja detectado obstruindo a sequência do movimento
	 **/


/**
**Método que faz o robô se locomover para frente  
**@param tempo unsigned long  :   tempo que o robô deve seguir em frente
--		                         O tempo do robô é definido em milessegundos e não pode ser um valor negativo
**@param velocidade int : velocidade que o robô deve executar o percurso 
--                        velocidade recebe por default o valor de VELOCIDADE_DEFAULT = 5cm/seg
--                        A velocidade do robô, passada por parâmetro nas funções movimento (frente e re), está definida como cm/s, 
--                        e sua conversão para valor PWM  é feito com base em uma escala pré-definida
--                        A velocidade está limitado em um range (intervalo) que vai de 5cm/s a 17cm/c
**@return void
**/	
void LARA::  frente( long &tempo, unsigned int velocidade){
  if(velocidade<RANGE_VELMIN){
  	Serial.println("./l1r2err.==.Erro na execução da função (frente): Velocidade muito baixa!");
  	end();
  }else if(velocidade>RANGE_VELMAX){
  	Serial.println("./l1r2err.==.Erro na execução da função (frente): Velocidade muito alta!");
  	end();
  }//fim if-else
  carro -> _frente(tempo, VEL_TO_PWM(velocidade));
}//fim frente

/**
**Método que faz o robô se locomover para frente 
**@param distancia int  : distância que o robô deve seguir em frente
--                        distância recebe por default o valor de DIST_DEFAULT = 10cm
--                        A conversão da distância segue pela cálculo da relação com as interrupções 
--                        dos encoders. Por testes prévios, sabe que, para o robô se deslocar por 1cm é necessário
--                        ocorrer 307.3 interrupções, isso independe da velocidade do robô. A partir de então a cada valor
--                        passado por parâmetro é possível descobrir quantas interrupções são necessárias para que o robô
--                        desloque tal distância. Lembrando, que se a unidade do valor passado for diferente de CM, este valor
--                        é convertido em CM antes de se calcular as interrupções.
**@param type int: unidade de medida da distância, a unidade pode ser CM(centímetro), M(metro) ou  POL(polegadas)
**@param velocidade int : velocidade que o robô deve executar o percurso
--                        velocidade recebe por default o valor de VELOCIDADE_DEFAULT = 5cm/seg
--                        A velocidade do robô, passada por parâmetro nas funções movimento (frente e re), está definida como cm/s, 
--                        e sua conversão para valor PWM é feito com base em uma escala pré-definida
--                        A velocidade está limitado em um range (intervalo) que vai de 5cm/s a 17cm/c
**@return void
**/
void LARA:: frente(unsigned int distancia, int type, unsigned int velocidade){
  if(type!=CM && type!=M && type!=POL){
	Serial.println("./l1r2err.==.Erro na execução da função (frente). Por favor, verifique a unidade de medida da distância, passada por parâmetro");
	end();
	return;
  }//fim if	

  if(velocidade<RANGE_VELMIN){
  	Serial.println("./l1r2err.==.Erro na execução da função (frente): Velocidade muito baixa!");
  	end();
  }else if(velocidade>RANGE_VELMAX){
  	Serial.println("./l1r2err.==.Erro na execução da função (frente): Velocidade muito alta!");
  	end();
  }//fim if-else
	  
  carro -> _frente(distancia, type, VEL_TO_PWM(velocidade));
}//fim frente

/**
**Método que faz o robô se locomover de marcha à ré 
**@param tempo float  : tempo que o robô deve seguir de marcha à ré
--                        O tempo do robô é definido em milessegundos e não pode ser um valor negativo
**@param velocidade int : velocidade que o robô deve executar o percurso
--                        velocidade recebe por default o valor de VELOCIDADE_DEFAULT = 5cm/seg
--                        A velocidade do robô, passada por parâmetro nas funções movimento (frente e re), está definida como cm/s, 
--                        e sua conversão para valor PWM é  é feito com base em uma escala pré-definida
--                        A velocidade está limitado em um range (intervalo) que vai de 5cm/s a 17cm/c
**@return void
**/
void LARA:: re(long &tempo, unsigned int velocidade){
  if(velocidade<RANGE_VELMIN){
  	Serial.println("./l1r2err.==.Erro na execução da função (re): Velocidade muito baixa!");
  	end();
  }else if(velocidade>RANGE_VELMAX){
  	Serial.println("./l1r2err.==.Erro na execução da função (re): Velocidade muito alta!");
  	end();
  }//fim if-else

  carro -> _re(tempo, VEL_TO_PWM(velocidade));
}//fim re

/**
**Método que faz o robô se locomover de marcha à ré 
**@param distancia int  : distância que o robô deve seguir de marcha à ré
--                        distância recebe por default o valor de DIST_DEFAULT = 10cm
--                        A conversão da distância segue pela cálculo da relação com as interrupções 
--                        dos encoders. Por testes prévios, sabe que, para o robô se deslocar por 1cm é necessário
--                        ocorrer 307.3 interrupções, isso independe da velocidade do robô. A partir de então a cada valor
--                        passado por parâmetro é possível descobrir quantas interrupções são necessárias para que o robô
--                        desloque tal distância. Lembrando, que se a unidade do valor passado for diferente de CM, este valor
--                        é convertido em CM antes de se calcular as interrupções.
**@param type int: unidade de medida da distância, a unidade pode ser CM(centímetro), M(metro) ou POL(polegadas)
**@param velocidade int : velocidade que o robô deve executar o percurso
--                        velocidade recebe por default o valor de VELOCIDADE_DEFAULT = 5cm/seg
--                        A velocidade do robô, passada por parâmetro nas funções de movimento (frente e re), está definida como cm/s, 
--                        e sua conversão para valor PWM é  é feito com base em uma escala pré-definida
--                        A velocidade está limitado em um range (intervalo) que vai de 5cm/s a 17cm/c
**@return void
**/	
void LARA::re(unsigned int distancia,int type, unsigned int velocidade){
  if(type!=CM && type!=M && type!=POL){
	Serial.println("./l1r2err.==.Erro na execução da função (re). Por favor, verifique a unidade de medida da distância, passada por parâmetro");
	end();
	return;
  }//fim if	
	 
  if(velocidade<RANGE_VELMIN){
  	Serial.println("./l1r2err.==.Erro na execução da função (re): Velocidade muito baixa!");
  	end();
  }else if(velocidade>RANGE_VELMAX){
  	Serial.println("./l1r2err.==.Erro na execução da função (re): Velocidade muito alta!");
  	end();
  }//fim if-else
  
  carro -> _re(distancia, type, VEL_TO_PWM(velocidade));
}//fim re

/**
**Método que faz o robô rotacionar sobre seu eixo no sentido da esquerda por uma angulação 
**@param angulo int : angulação que o robô pode virar. 
--                    a angulação que é permitida ao robô rotacionar é limitada pelo intervalor RANGE_ANGMAX (1080) e RANGE_ANGMIN(-1080) 
--                    estes valores de range foram definidos como método de segurança do movimento do robô                  
--                    o movimento é controlado pelo cálculo de interrupções dos encoders acoplados as rodas do robô; 
--                    sabe-se que para rotacionar 1º o robô precisa dar 34,85 interrupções, a partir daí é possivel saber quantas interrupções 
--                    necessárias para cada ângulo de rotação.
--                    caso o parâmetro passado for negativo, significa que o robô deve rotacionar aquele ângulo, só que em um sentido inverso ao
--                    pedido, ou seja, se a função esquerda receber -"angulo", ele deve rotacionar para direita "angulo" graus.
**@return void
**/
void LARA:: esquerda(int angulo){
	if(angulo > RANGE_ANGMAX || angulo < RANGE_ANGMIN){
		Serial.println("./l1r2err.==.Erro na execução da função (esquerda): o robô não consegue virar este ângulo");
		end();
	}//fim if
	carro -> _esquerda(angulo);
}//fim esquerda

/**
**Método que faz o robô rotacionar sobre seu eixo no sentido da direita por uma angulação 
**@param angulo int : angulação que o robô pode virar. 
--                    a angulação que é permitida ao robô rotacionar é limitada pelo intervalor RANGE_ANGMAX (1080) e RANGE_ANGMIN(-1080) 
--                    estes valores de range foram definidos como método de segurança do movimento do robô                  
--                    o movimento é controlado pelo cálculo de interrupções dos encoders acoplados as rodas do robô; 
--                    sabe-se que para rotacionar 1º o robô precisa dar 34,85 interrupções, a partir daí é possivel saber quantas interrupções 
--                    necessárias para cada ângulo de rotação.
--                    caso o parâmetro passado for negativo, significa que o robô deve rotacionar aquele ângulo, só que em um sentido inverso ao
--                    pedido, ou seja, se a função direita receber -"angulo", ele deve rotacionar para esquerda "angulo" graus.
**@return void
**/		
void LARA::direita(int angulo){
	if(angulo > RANGE_ANGMAX || angulo < RANGE_ANGMIN){
		Serial.println("./l1r2err.==.Erro na execução da função (direita): o robô não consegue virar este ângulo");
		end();
	}//fim if
	carro -> _direita(angulo);
}//fim direita

/**
**Método que para a execução de qualquer movimento do L1R2
-- Para a execução de quanquel movimento, setando os motores para LOW e zerando a leitura dos encoders
**@return void
**/
void LARA::parar(){
	//__TODO__ função de parar
   carro -> _parar();
}//fim parar

/**
** Método que retorna a velocidade atual do robô em cm/s
-- A velocidade é consultado do objeto carro que é a interface de controle de movimento do robô
**@return velocidade int: velocidade atual do robô, em cm/s
**/
int LARA::getVelocidade(){
 return carro -> _getVelocidade();
}//fim getVelocidade

/**
** Método que seta a velocidade do robô
**@param velocidade int : velocidade do robô em cm/s
--                        no método ocorre a conversão de cm/s em PWM e passada como parÂmetro para a 
--                        função implementada na classe CARRO.h que recebe como parâmetro o valor PWM
--                        para então mudar a velocidade do robô
**@return void
**/
void  LARA::setVelocidade (unsigned int velocidade){
	if(velocidade > RANGE_VELMAX || velocidade < RANGE_VELMIN){
		Serial.println("./l1r2err.==.Erro na execução da função. A velocidade passada por parâmetro é muito grande ou muito pequena.");
		end();
		return;
	}//fim if
	carro -> _setVelocidade(VEL_TO_PWM(velocidade));
}//fim setVelicidade


/**
**Método que retorna o ângulo do robô em relação ao norte magnético
**@return ang float
**/
float LARA::leituraAnguloNorteMagnetico(){
 	return -1.0;
}//fim leituraAnguloNorteMagnetico

/**
**Método que retorna o ângulo de referência do robô (norte do robô)
**@return ang float
**/
float LARA::leituraAnguloReferencia(){
  return -1.0;
}//fim leituraAnguloReferencia

/**
**Método que muda o ângulo de referência do robô (norte do robô)
**@param angulo float : novo ângulo de referÊncia do robô
**@return void
**/
void LARA::setAnguloReferencia(float angulo){
}//fim serAnguloReferencia


/*****************************************************
                  FUNÇÕES LED
*****************************************************/

/**
** Método que liga os leds (farois) do L1R2
-- O método trabalha de várias formas. É possível ligar cada led separadamente ou os dois ao mesmo tempo.
-- Além disso, é possivel mudar a cor do led, para tanto é necessário criar um registro do tipo Cor e setar
--  os valores (r, g e b) no registro, passando-o como parâmetro da função. Caso nenhuma cor seja atribuida à
--  função, ela assume o valor padrão que é azul.
**@param cor Cor : cor do led
**@param led int : indicação de qual led deverá ser ligado - 
--                 DIREITA - led da direita
--                 ESQUERDA - led da esquerda
--                 DIREITA_ESQUERDA - ambos os leds ao mesmo tempo
**@return void
**/
void  LARA::ligarFarol(int led, int cor){
}//fim ligarFarol


/**
** Método que desliga os leds (farois) do L1R2
-- O método trabalha de várias formas. É possível desligar cada led separadamente ou os dois ao mesmo tempo.
**@param led int : indicação de qual led deverá ser ligado - 
--                 DIREITA - led da direita
--                 ESQUERDA - led da esquerda
--                 DIREITA_ESQUERDA - ambos os leds ao mesmo tempo
**@return void
**/
void  LARA::desligarFarol(int led){
}//fim desligarFarol

/**
** Método que faz os leds (faróis) piscarem. Esse método atua de duas formas difente,
--   podendo fazer cada led piscar separadamente ou ambos ao mesmo tempo
**@param unsigned n int: quantidade de vezes que o led precisa piscar. Por default é 10 vezes
**@param led int: led que deverá piscar, podendo ser: DIREITA, ESQUERDA ou DIREITA_ESQUERDA (ambos os leds)
**@param cor Cor: Cor do led. Por default é azul
**@param unsigned int tempo : tempo que o led fica ligado e desligado
**/
void  LARA::piscarFarol(unsigned int n, unsigned int tempo, int led, int cor){
}//fim piscarFarol

/*****************************************************
               FUNÇÕES PRIVADAS
*****************************************************/
  /**
   ** Método que encerra a execução de um método, quando um erro de semântica for detectado
   **@return void
   **/
void LARA::end(){
    parar();
    for(;;);
}//fim end
