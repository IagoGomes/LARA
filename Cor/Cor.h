#ifndef COR_H
#define COR_H

struct _limiteSensorCor{
 	int r_min; 
	int r_max; 
	int g_min; 
	int g_max;
	int b_min;
	int b_max;
};

typedef struct _limiteSensorCor SensorData;



class Cor{

public:

	/**Construtor de Classe Cor é executado sempre que for instanciado um objeto desta classe.
	*@param r:int
	*@param g:int
	*@param b:int
	*/
	Cor(int r, int g, int b, char name);
 
        Cor();

	/** Método isColor verifica se as variáveis r, g, b possuem o mesmo valor das variáveis da
        * classe.
	*@param r:int
	*@param g:int
	*@param b:int
	*@return bool
	*/
	bool isColor(int r, int g, int b);

	/** Método isEqual verifica se duas cores são iguais comparando os valores das variáveis r, g, b.
	*@param cor
	*@return bool
	*/
	bool isEqual(Cor cor);


	/** Método getR retorna o valor de r.
	*@return int
	*/
	int getR();

        /** Método getG retorna o valor de g.
	*@return int
	*/
	int getG();

	/** Método getB retorna o valor de b.
	*@return int
	*/
	int getB();

	char getName();
	
private:
	int r, g, b;
	int index;
	SensorData sensor_data;
 	char name;
};

#endif
