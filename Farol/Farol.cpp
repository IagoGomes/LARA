#include "Farol.h"


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
void Farol:: ligarFarol(int led, int cor){
	if (same) { //Ambos os leds estiverem conectados
		analogWrite(pin_r_1, _rgb[cor].r);
	    	analogWrite(pin_g_1, _rgb[cor].g);
    		analogWrite(pin_b_1, _rgb[cor].b);
	} else { //Caso os leds não estiverem conectados
		switch (led) {// Ligar cada um separadamente
			case DIREITA: //led da direita apenas
	    	             analogWrite(pin_r_1, _rgb[cor].r);
	    	             analogWrite(pin_g_1, _rgb[cor].g);
 	    	             analogWrite(pin_b_1, _rgb[cor].b);
    	                     break;    	             
			case ESQUERDA://led da esquerda apenas
	    	             analogWrite(pin_r_2, _rgb[cor].r);
	    	             analogWrite(pin_g_2, _rgb[cor].g);
	    	             analogWrite(pin_b_2, _rgb[cor].b);
	    	             break;    	             
	    	        case DIREITA_ESQUERDA://ambos os leds
			     analogWrite(pin_r_1, _rgb[cor].r);
	    	             analogWrite(pin_g_1, _rgb[cor].g);
	    	             analogWrite(pin_b_1, _rgb[cor].b);
	    	             analogWrite(pin_r_2, _rgb[cor].r);
	    	             analogWrite(pin_g_2, _rgb[cor].g);
	    	             analogWrite(pin_b_2, _rgb[cor].b);
	    	             break;
	    	        default://caso o parâmetro da pinagem estiver incorreto, não for nenhum dos leds
	    	             Serial.println("./l1r2err.==.Erro: Led não encontrado. Verifique o parÂmetro led passado por parâmetro!"); 
	   }//fim switch
	}//fim else
} //fim ligarFarol



/**
** Método que desliga os leds (farois) do L1R2
-- O método trabalha de várias formas. É possível desligar cada led separadamente ou os dois ao mesmo tempo.
**@param led int : indicação de qual led deverá ser ligado - 
--                 DIREITA - led da direita
--                 ESQUERDA - led da esquerda
--                 DIREITA_ESQUERDA - ambos os leds ao mesmo tempo
**@return void
**/
void Farol::desligarFarol(int led){
	
	if (same) { // Ambos os leds estiverem conectados
		 analogWrite(pin_r_1, 0);
	    	 analogWrite(pin_g_1, 0);
	    	 analogWrite(pin_b_1, 0);  
	} else { //Caso os leds não estiverem conectados
		switch (led) {// Ligar cada um separadamente
			case DIREITA: //led da direita apenas
         		     analogWrite(pin_r_1, 0);
	 	             analogWrite(pin_g_1, 0);
	    	             analogWrite(pin_b_1, 0);
    	             break;
    	             
			case ESQUERDA://led da esquerda apenas 
    		             analogWrite(pin_r_2, 0);
    		             analogWrite(pin_g_2, 0);
    		             analogWrite(pin_b_2, 0);
    	             break;
    	     
    		    case DIREITA_ESQUERDA: //ambos os LEDs
					analogWrite(pin_r_1, 0);
					analogWrite(pin_g_1, 0);
					analogWrite(pin_b_1, 0);
					analogWrite(pin_r_2, 0);
					analogWrite(pin_g_2, 0);
					analogWrite(pin_b_2, 0);
    	 
    	    default://caso o parâmetro da pinagem estiver incorreto, não for nenhum dos leds
    	             Serial.println("./l1r2err.==.Erro: Led não encontrado. Verifique o led passado por parâmetro!");
		
		}// fim switch
	}// fim else*/
}//fim desligarFarol

/**
** Método que faz os leds (faróis) piscarem. Esse método atua de duas formas difente,
--   podendo fazer cada led piscar separadamente ou ambos ao mesmo tempo
**@param unsigned n int: quantidade de vezes que o led precisa piscar. Por default é 10 vezes
**@param led int: led que deverá piscar, podendo ser: DIREITA, ESQUERDA ou DIREITA_ESQUERDA (ambos os leds)
**@param int Cor: Cor do led. Por default é azul
**@param unsigned int tempo : tempo que o led fica ligado e desligado
**/
void  Farol::piscarFarol(unsigned int n,unsigned int tempo, int cor, int led){
   for(int i=0; i<n; i++){
   	 ligarFarol(cor, led);
   	 delay(tempo);
   	 desligarFarol(led);
   	 delay(tempo);
   }//fim for
}//fim piscarFarol

/**
 * Métodos construtores
 **/
 
 /** 
  * Construtor Quando os LEDs estiverem  conectados em curto circuito
  **/
Farol::Farol (int pin_r, int pin_g, int pin_b) {
	 same = true; 
	 this -> pin_r_1 = pin_r_2 = pin_r;
	 this -> pin_g_1 = pin_g_2 = pin_g;
	 this -> pin_b_1 = pin_b_2 = pin_b;
	 
	 //Definindo os pinos dos Faróis como saída
	 pinMode(pin_r_1, OUTPUT);
	 pinMode(pin_g_1, OUTPUT);
	 pinMode(pin_b_1, OUTPUT);
}
 
/**
 * Construtor quando os LEDs estiverem conectados separadamente
 **/
Farol::Farol (int pin_r_1, int pin_g_1, int pin_b_1, int pin_r_2, int pin_g_2, int pin_b_2) {
	 same = false;
	 this -> pin_r_1 = pin_r_1;
	 this -> pin_g_1 = pin_g_1;
	 this -> pin_b_1 = pin_b_1;
	 
	 this -> pin_r_2 = pin_r_2;
	 this -> pin_g_2 = pin_g_2;
	 this -> pin_b_2 = pin_b_2;
	 
	 //Definindo os pinos dos Faróis como saída
	 pinMode(pin_r_1, OUTPUT);
	 pinMode(pin_g_1, OUTPUT);
	 pinMode(pin_b_1, OUTPUT);
	 
	 pinMode(pin_r_2, OUTPUT);
	 pinMode(pin_g_2, OUTPUT);
	 pinMode(pin_b_2, OUTPUT);
}
