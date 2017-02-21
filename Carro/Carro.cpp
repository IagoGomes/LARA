
#include "Carro.h"

Encoder encoderDireita (ENCODER_D1,ENCODER_D2); //=Encoder(2,3);//(2,3);
Encoder encoderEsquerda (ENCODER_E1, ENCODER_E2);
PID *pidMotor; 

/************************************************
              MÉTODOS PÚBLICOS

************************************************/

/**
** Método construtor da classe
-- O usuário deve setar os pinos dos motores da direita e esquerda do robô.
**@return void
**/
Carro :: Carro(){

   //inicializando o contador de interrupções dos encoders
   tick_motor_direita =0;
   tick_motor_esquerda =0;
   alpha = 0;
   last_alpha =0;
   //inicializando a velocidade defaut dos motores
   vel_max_pwm_direita = VEL_PWM_DEFAULT;
   vel_max_pwm_esquerda = VEL_PWM_DEFAULT;

   //inicializando as constantes do PID dos motores
   motor_kp =10;
   motor_ki =0;
   motor_kd =0;

   //inicializando as variáveis dos PID dos motores
   motor_input   =0;
   motor_output =0;
   motor_setpoint=0;

   //inicializando o objeto de PID dos motores
   pidMotor =  new PID(&motor_input, &motor_output, &motor_setpoint, motor_kp, motor_ki, motor_kd, DIRECT);

   //inicializando o objeto dos encoders dos motores
   
   //definindo os pinos dos motores como saída
   pinMode(MOTOR_ESQUERDA_N, OUTPUT);
   pinMode(MOTOR_ESQUERDA_P, OUTPUT);
   pinMode(MOTOR_DIREITA_N, OUTPUT);
   pinMode(MOTOR_DIREITA_P, OUTPUT);


   distanciaPercorrida=0;

    Serial.begin(115200);
}//fim construtor


//>>>>>>>>>>>>>>>>>>>>>>>>>>>MÉTODOS DE MOVIENTO>>>>>>>>>>>>>>>>>>>>>>>>>>>>//

void Carro :: _frente(int distancia, int type, int velocidade){
    _setVelocidade(velocidade);

    uint8_t time = 50;
    uint8_t timePID = 25;
    long lastTime = 0; 
    long lastTimePID = 0;

    distanciaPercorrida=0;     
    while(distanciaPercorrida < distancia){
      if(millis()> (time + lastTime)){  
        analogWrite(MOTOR_DIREITA_N, VEL_MIN);
        analogWrite(MOTOR_ESQUERDA_N, VEL_MIN);
        analogWrite(MOTOR_DIREITA_P, vel_max_pwm_direita);
        analogWrite(MOTOR_ESQUERDA_P, vel_max_pwm_esquerda);
        lastTime = millis();
      }else if( millis() > (timePID + lastTimePID)){
        updatePID();
        lastTimePID = millis();
      }
    }//fim while
    _parar();
}//fim _frente


/**
 **Método que faz o robô movimentar-se para a frente
 --   Este método faz o robô andar para a frente por um tempo determinado
 -- e uma velocidade definida por parâmetro.
 **@param tempo long : tempo que o robô deve se locomover para frente, o tempo é definido em milissegundos
 **@param velocidade int : velocidade do robô no movimento
 --                A velocidade do robô é medida com base na saída PWM aplicada 
 --                          nos motores. O range do PWM no arduino é de 0-255, todavia,
 --                          para que o robô execute algum movimento, o PWM mínimo aplicado 
 --                          é de 180.
 -          Caso o valor de velocidade não for passado por parâmetro, então 
 --                          ele assume o valor da constante VELOCIDADE_PWM_DEFAULT
 **@return void 
 **/
void Carro :: _frente(long &tempo, unsigned int velocidade){
}//fim _frente

void Carro :: _re(int distancia, int type,int velocidade){
    _setVelocidade(velocidade);

    uint8_t time = 50;
    uint8_t timePID = 25;
    long lastTime = 0; 
    long lastTimePID = 0;

    distanciaPercorrida=0;     
    while(distanciaPercorrida < distancia){
      if(millis()> (time + lastTime)){  
        analogWrite(MOTOR_DIREITA_P, VEL_MIN);
        analogWrite(MOTOR_ESQUERDA_P, VEL_MIN);
        analogWrite(MOTOR_DIREITA_N, vel_max_pwm_direita);
        analogWrite(MOTOR_ESQUERDA_N, vel_max_pwm_esquerda);
        lastTime = millis();
      }else if( millis() > (timePID + lastTimePID)){
        updatePID();
        lastTimePID = millis();
      }
    }//fim while
    _parar();
}//fim _re

void Carro :: _re(long &tempo, unsigned int velocidade){
}//fim _frente


/**
** __TODO__
**@return void
**/
void Carro :: _direita(int angulo){
   long _alpha = 0;
   while(_alpha<2*angulo){
        analogWrite(MOTOR_DIREITA_P, VEL_MIN);
        analogWrite(MOTOR_ESQUERDA_N, VEL_MIN);
        analogWrite(MOTOR_ESQUERDA_P, 255);
        analogWrite(MOTOR_DIREITA_N, 255);
        updateOdometria();
        _alpha+=abs(alpha);
        Serial.print("alpha=");
        Serial.println(_alpha);
   }
   _parar();
}//fim _direita

/**
** __TODO__
**@return void 
**/
void Carro :: _esquerda(int angulo){
}//fim _esquerda

/**
** __TODO__
**@return void
**/
void Carro :: _parar(){
 analogWrite(MOTOR_DIREITA_N, VEL_MIN);
 analogWrite(MOTOR_ESQUERDA_N, VEL_MIN);
 analogWrite(MOTOR_DIREITA_P, VEL_MIN);
 analogWrite(MOTOR_ESQUERDA_P, VEL_MIN);
}//fim _parar

//>>>>>>>>>>>>>>>>>>>>>>>>>>>MÉTODOS DE CONFIGURAÇÃO>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/**
**Método que seta a velocidade padrão do robô
--A velocidade do motor é um valor PWM que altera a tensão de alimentação dos motores, logo
-- a velocidade do robô
**@param velocidade int : valor da velocidade do robô, é um valor PWM que vai de 0-255
**@return void
**/
void Carro :: _setVelocidade(int velocidade){
  this -> vel_default=velocidade;
  this -> vel_max_pwm_esquerda = velocidade;
  this -> vel_max_pwm_direita = velocidade;
}//fim setVelocidade

/**
** Método que retorna a velocidade atual do robô
-- A velocidade pode ser setada pelo usuário, caso contrário ela é definida como VELOCIDADE_DEFAULT_PWM
**@return void
**/
int Carro :: _getVelocidade(){
  return this->vel_default;
}//getVelocidade

/************************************************
              MÉTODOS PRIVADOS
*************************************************/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>MÉTODOS DE CONFIGURAÇÃO>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/**
** __TODO__
**@return void
**/
void inline Carro:: updatePID(){
   updateOdometria();
   motor_input = 1000*alpha;
   pidMotor->Compute();
  
   Serial.print(" out=");
   Serial.println(motor_output);
   
   vel_max_pwm_direita = constrain(vel_max_pwm_direita - motor_output, 180 ,255);
   vel_max_pwm_esquerda = constrain(vel_max_pwm_esquerda + motor_output, 180, 255);
}//fim updatePIDMotor

void inline Carro::updateEncoders(){
 tick_motor_direita = encoderDireita.read();
 tick_motor_esquerda = encoderEsquerda.read();
 encoderDireita.write(0);
 encoderEsquerda.write(0);
}

void inline Carro::updateOdometria(){
 updateEncoders();

 double tempE = (double)tick_motor_esquerda/PULSOS_POR_PERIMETRO_RODA;
 double tempD = (double)tick_motor_direita/PULSOS_POR_PERIMETRO_RODA;
 dist_esquerda = PERIMETRO_RODA*tempE;
 dist_direita  = PERIMETRO_RODA*tempD;

 distanciaPercorrida += (dist_esquerda + dist_direita)/2.0;
 
 double temp  = (dist_direita-dist_esquerda);
        temp  =(double) temp/DIAMETRO_EIXO_MOTOR;
   alpha = alpha + temp;

}

