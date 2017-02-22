#ifndef COR_H
#define COR_H

class Cor{
   private:
	int r_min; 
	int r_max; 
	int g_min; 
	int g_max;
	int b_min;
	int b_max;
	
   public:
	Cor();

	bool isColor(int r, int g, int b);
	
	void setR(int r_min, int r_max);

	void setG(int g_min, int g_max);

	void setB(int b_min, int b_max);


};


#endif
