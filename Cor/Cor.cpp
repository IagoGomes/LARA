#include "Cor.h"


/**Construtor de Classe Cor é executado sempre que for instanciado um    *   objeto desta classe.
*@param r:int
*@param g:int
*@param b:int
*/
Cor::Cor(int r, int g, int b){
	this -> r=r;
	this -> g=g;
	this -> b=b;
        this -> sensor_data.r_min=0;
}

Cor::Cor(){};

/** Método isColor verifica se as variáveis r, g, b possuem o mesmo valor *    das variáveis da classe.
*@param r:int
*@param g:int
*@param b:int
*@return bool
*/
bool Cor::isColor (int r, int g, int b){
	return (this -> r==r) && (this -> g==g) && (this -> b==b);
}

/** Método isEqual verifica se duas cores são iguais comparando os valores *    das variáveis r, g, b.
*@param cor
*@return bool
*/
bool Cor::isEqual(Cor cor){
	return isColor(cor.getR(), cor.getG(), cor.getB());
}

/** Método getR retorna o valor de r.
*@return int
*/
int Cor::getR(){
	return this -> r;
}

/** Método getG retorna o valor de g.
*@return int
*/
int Cor::getG(){
	return this -> g;
}

/** Método getB retorna o valor de b.
*@return int
*/

int Cor::getB(){
	return this -> b;
}



