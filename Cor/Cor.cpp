#include "Cor.h"


/**Construtor de Classe Cor é executado sempre que for instanciado um    *   objeto desta classe.
*@param r:int
*@param g:int
*@param b:int
*/
Cor::Cor(){
	
}

/** Método isColor verifica se as variáveis r, g, b possuem o mesmo valor *    das variáveis da classe.
*@param r:int
*@param g:int
*@param b:int
*@return bool
*/
bool Cor::isColor(int r, int g, int b) { 
	return (r>=r_min && r<=r_max) && (g>=g_min && g<=g_max) && (b>=b_min && b<=b_max);
}

void Cor::setR(int r_min, int r_max) { 
	this->r_min = r_min;
	this->r_max = r_max;
}

void Cor::setG(int g_min, int g_max) { 
	this->g_min = g_min;
	this->g_max = g_max;
}

void Cor::setB(int b_min, int b_max) { 
	this->b_min = b_min;
	this->b_max = b_max;
}





