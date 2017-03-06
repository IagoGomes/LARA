#include "Sensores.h"


Sensores::Sensores(){
    sonar = (NewPing*) calloc(6,sizeof(NewPing));
    sonar [0]= NewPing (10,10,1000);
    sonar [1]= NewPing (10,10,1000);
    sonar [2]= NewPing (10,10,1000);
    sonar [3]= NewPing (10,10,1000);
    sonar [4]= NewPing (10,10,1000);
    sonar [5]= NewPing (10,10,1000);
		    
   compass = new Compass();

};

int Sensores::leituraSensorLuz(int index){
   switch(index){
	case CENTRO:
		return analogRead(PIN_LDR_CENTRO);
		break;
	case DIREITA: 
		return analogRead(PIN_LDR_DIREITA);
		break;
 	case ESQUERDA:
		return analogRead(PIN_LDR_ESQUERDA);
		break;
	default:
		Serial.println("index do sensor de luz está incorreto!");
		return -1;

   }//fim switch
}

int Sensores::distancia(int index, int un){
   int value=-1;
   if(index>=0 && index <6){
	switch(un){
		case CM: 
			value = sonar[index].ping_median_cm();
			break;
		case M:
			value = sonar[index].ping_median_m();
			break;
		case POL:
			value = sonar[index].ping_median_in();
			break;
		default:
			Serial.println("Unidade escolhida para a leitura dos sensores de cor!"); 
	}//fim switch
   }else{
	Serial.println("Index do sensor ultrassom está incorreto!");
   }//fim if-else
   return -1;
}//fim distance

void Sensores::getLeiturasSensorDeLuz(int *ldrDireita, int *ldrEsquerda, int * ldrCentro){
	*ldrDireita=analogRead(PIN_LDR_DIREITA);
	*ldrCentro=analogRead(PIN_LDR_CENTRO);
	*ldrEsquerda=analogRead(PIN_LDR_ESQUERDA);
}//fim gerLeiturasSensoDeLuz


void Sensores::getLeiturasBussola(int *xAxis, int *yAxis, int *zAxis){
	compass -> getAxis(xAxis, yAxis, zAxis);
}

/**
**Método que retorna o ângulo do robô em relação ao norte magnético
**@return ang float
**/
float Sensores::leituraAnguloNorteMagnetico(){
	return compass -> compass_heading(); 
}

/**
**Método que retorna o ângulo de referência do robô (norte do robô)
**@return ang float
**/
float Sensores::leituraAnguloReferencia(){
	return compass -> getReferenceAngle();
}
	
void Sensores::setAnguloReferencia(float angulo){
	compass -> setReferenceAngle(angulo);
}

float Sensores::getAnguloReferencia(){
return -1;
}

int Sensores::getLinha(){
return -1;
}


int Sensores::getMinDistancia(){
        int distFrente = distancia(FRENTE);
	int distDireita = distancia(DIREITA);
	int distEsquerda= distancia(ESQUERDA);
	int distTras = distancia(TRAS);
	int distFrenteEsquerda=distancia(FRENTE_ESQUERDA);
        int distFrenteDireita=distancia(FRENTE_DIREITA);

	if((distFrente <= distDireita) && (distFrente <= distEsquerda) && (distFrente<=distFrenteEsquerda) && (distFrente<=distFrenteDireita)){//se a menor distância pertecer ao sensor do centro
		return FRENTE;
	}//fim if
	else if((distDireita <= distFrente) && (distDireita <= distEsquerda) && (distDireita<=distFrenteEsquerda) && (distDireita<=distFrenteDireita)){//se a menor distância pertencer ao sensor da direita
		return DIREITA;
	}//fim else-if
	else if((distEsquerda <= distFrente) && (distEsquerda <= distDireita) && (distEsquerda<=distFrenteEsquerda) && (distEsquerda<=distFrenteDireita)){//se a menor distância pertencer ao sensor da esquerda
		return ESQUERDA;  
	}//fim else-if
	else if((distFrenteEsquerda <= distFrente) && (distFrenteEsquerda <= distDireita) && (distFrenteEsquerda<=distEsquerda) && (distFrenteEsquerda<=distFrenteDireita)){//se a menor distância pertencer ao sensor da frente à direita
		return FRENTE_ESQUERDA;
	}//fim else-if
	else if((distFrenteDireita <= distFrente) && (distFrenteDireita <= distDireita) && (distFrenteDireita<=distEsquerda) && (distFrenteDireita<=distFrenteEsquerda)){//se a menor distância pertencer ao sensor da frente à esquerda
		return FRENTE_DIREITA;
	}//fim else-if

	return -1; // ERRO
}

int Sensores::getMaxDistancia(){
	int distFrente = distancia(FRENTE);
	int distDireita = distancia(DIREITA);
	int distEsquerda= distancia(ESQUERDA);
	int distTras = distancia(TRAS);
	int distFrenteEsquerda=distancia(FRENTE_ESQUERDA);
	int distFrenteDireita=distancia(FRENTE_DIREITA);

	if((distFrente >= distDireita) && (distFrente >= distEsquerda) && (distFrente>=distFrenteEsquerda) && (distFrente>=distFrenteDireita)){//se a maior distância pertecer ao sensor do centro
		return FRENTE;
	}//fim if
	else if((distDireita >= distFrente) && (distDireita >= distEsquerda) && (distDireita>=distFrenteEsquerda) && (distDireita>=distFrenteDireita)){//se a maior distância pertencer ao sensor da direita
		return DIREITA;
	}//fim else-if
	else if((distEsquerda >= distFrente) && (distEsquerda >= distDireita) && (distEsquerda>=distFrenteEsquerda) && (distEsquerda>=distFrenteDireita)){//se a maior distância pertencer ao sensor da esquerda
		return ESQUERDA;  
	}//fim else-if
	else if((distFrenteEsquerda >= distFrente) && (distFrenteEsquerda >= distDireita) && (distFrenteEsquerda>=distEsquerda) && (distFrenteEsquerda>=distFrenteDireita)){//se a maior distância pertencer ao sensor da frente à direita
		return FRENTE_ESQUERDA;
	}//fim else-if
	else if((distFrenteDireita >= distFrente) && (distFrenteDireita >= distDireita) && (distFrenteDireita>=distEsquerda) && (distFrenteDireita>=distFrenteEsquerda)){//se a maior distância pertencer ao sensor da frente à esquerda
		return FRENTE_DIREITA;
	}//fim else-if

	return -1;//ERRO
}


void getLeituraSensorCor(int *corDireita, int *corCentro, int *corEsquerda){
}

int leituraSensorCor(int index){
return -1;
}
