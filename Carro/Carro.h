#ifndef Carro_h
#define Carro_h

//biblioteca com as funções do arduino
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

#include "PID/PID_v1.h"//biblioteca do controle PID
#include "Encoder/Encoder.h"//biblioteca para controle dos encoders
#include "Thread/Thread.h" //biblioteca para a thread
#include "../Pinos.h" //definição dos pinos do robô
#include "../Constantes.h" //constantes usadas no controle do robô
#include "TimerThree/TimerThree.h"




class Carro {     
        
      private:
     
        //definindo a variavel de controle de PID nos motores Encoders
        double motor_kp,
               motor_ki, 
               motor_kd;

        //variáveis de configuração do PID dos motores
        double motor_setpoint,
               motor_input,
               motor_output;

        #define  PULSOS_POR_VOLTA 128 //números de interrupções por volta do disco de encoder
        #define  PERIMETRO_RODA 20.41 //2*pi*r = 2*3,14*3,25; valor do perímetro da roda em cm
        #define  DIAMETRO_RODA  6.5   //valor do diametro da roda

        #define  RAIO_RODA 3.25
      
        #define  TEMPO_UPDADE   500   //tempo que as variáveis e informações sobre o estado do robô deve ser atualizadas (milissegundos)
        #define  PULSOS_POR_PERIMETRO_RODA 6151 // quantidade de pulsos dos encoders para um permímetro de roda
        #define  PULSOS_POR_1CM  301.3  //quantidade de pulsos dos encoders para o L1R2 deslocar 1 centímetro
        #define DIAMETRO_EIXO_MOTOR 8 //cm
                           //cálculo baseado na regra de três:  6272 -- 20,41; x -- 1 =>  x = 6151/20,41 ~ 301.3
        

        //variáveis que armazenam a contagem de pulsos dos encoders
        volatile int tick_motor_direita, 
                     tick_motor_esquerda;   

        volatile int last_tick_motor_direita,
                     last_tick_motor_esquerda;

        volatile int delta_tick_motor_direita,
		     delta_tick_motor_esquerda;
 
        volatile double alpha, 
                        last_alpha;


        int vel_max_pwm_direita,
            vel_max_pwm_esquerda;
        int vel_default;
        #define VEL_MIN 0

        double dist_esquerda, dist_direita;
        //variável que armazena o valor default da velocidade do robô
        //esta variável pe ajustável pelo usuário
	
 	//variável que armazena a distância(pulsos) percorrida pelo carro
         double distanciaPercorrida;
       
        /**
         ** Método que atualiza a leitura dos encoders e o cálculo do PID
         **@return void
         **/
         void inline updateEncoders();
         void inline updatePID();
         void inline updateOdometria();
           
   
        //Definindo as constantes para controle de movimentos do L1R2
	#define VEL_PWM_DEFAULT 200

        //Funções de conversão
        #define cmToPulsos(x) (PULSOS_POR_1CM*x)
        #define mToPulsos(x)  (PULSOS_POR_1CM*100*x)    //conversão cm to m
        #define polToPulsos(x) (PULSOS_POR_1CM*2.54*x)  //conversão cm to pol

      public:

/*-------------------Construtor---------------------------------------*/
        /**
        ** Método construtor da classe 
        -- Método genérico, o usuário deve setar os pinos dos motores do robô
        **@param motor_direita_p int : pino positivo da direita
        **@param MOTOR_DIREITA_N int : pino negativo da direita
        **@param MOTOR_ESQUERDA_P int : pino positico da esquerda
        **@param MOTOR_ESQUERDA_N int : pino negativo da esquerda
        **@return void
        **/
        Carro ();


/*-------------------Métodos de movimento do robô---------------------*/

  /**
  **Método que faz o robô movimentar-se para a frente
  --   Este método faz o robô andar para a frente por uma quantidade de distancia 
    -- e uma velocidade definida por parâmetro.  
  **@param distancia int : quantidade de distancia que o robô deve se locomover. 
    --                      Caso o valor de distancia não for passado por parâmetro, então ele
    --                      assume o valor da constante DIST_DEFAULT
    **@param type int: unidade de medida da distância desejada. 
    --                 a unidade de medida pode ser CM (centímetro), M (metro) ou POL (polegadas)
  **@param velocidade int : velocidade do robô no movimento
  --                A velocidade do robô é medida com base na saída PWM aplicada 
    --                          nos motores. O range do PWM no arduino é de 0-255, todavia,
    --                          para que o robô execute algum movimento, o PWM mínimo aplicado 
    --                          é de 180.
  --          Caso o valor de velocidade não for passado por parâmetro, então 
    --                          ele assume o valor da constante VELOCIDADE_PWM_DEFAULT
  **@return void 
  **/
    void frente(int distancia=DIST_DEFAULT, int type = CM, int velocidade=VEL_PWM_DEFAULT);
    
   /**
  **Método que faz o robô movimentar-se para a frente
  --   Este método faz o robô andar para a frente por um tempo determinado
    -- e uma velocidade definida por parâmetro.
  **@param tempo float : tempo que o robô deve se locomover para frente, o tempo é definido em milissegundos
  **@param velocidade int : velocidade do robô no movimento
  --                A velocidade do robô é medida com base na saída PWM aplicada 
    --                          nos motores. O range do PWM no arduino é de 0-255, todavia,
    --                          para que o robô execute algum movimento, o PWM mínimo aplicado 
    --                          é de 180.
  --          Caso o valor de velocidade não for passado por parâmetro, então 
    --                          ele assume o valor da constante VELOCIDADE_PWM_DEFAULT
  **@return void 
  **/
    void frente(long &tempo, unsigned int velocidade=VEL_PWM_DEFAULT);

  /**
  **Método que faz o robô movimentar-se de marcha à ré
  --   Este método faz o robô andar de marcha à ré por uma distância 
    -- e uma velocidade definida por parâmetro.  
  **@param distancia int : quantidade de distância que o robô deve se locomover. 
    --                      Caso o valor de distância não for passado por parâmetro, então ele
    --                      assume o valor da constante DIST_DEFAULT
    **@param type int: unidade de medida da distância desejada. 
    --                 a unidade de medida pode ser CM (centímetro), M (metro) ou POL (polegadas)
  **@param velocidade int : velocidade do robô no movimento
  --                A velocidade do robô é medida com base na saída PWM aplicada 
    --                          nos motores. O range do PWM no arduino é de 0-255, todavia,
    --                          para que o robô execute algum movimento, o PWM mínimo aplicado 
    --                          é de 180.
  --          Caso o valor de velocidade não for passado por parâmetro, então 
    --                          ele assume o valor da constante VELOCIDADE_PWM_DEFAULT
  **@return void 
  **/
  void re(int distancia=DIST_DEFAULT, int type = CM, int velocidade=VEL_PWM_DEFAULT);
    
    /**
  **Método que faz o robô movimentar-se de marcha à ré
  --   Este método faz o robô andar de marcha à ré por um tempo determinado
    -- e uma velocidade definida por parâmetro.
  **@param tempo float : tempo que o robô deve se locomover de marcha à ré, o tempo é definido em milissegundos
  **@param velocidade int : velocidade do robô no movimento
  --                A velocidade do robô é medida com base na saída PWM aplicada 
    --                          nos motores. O range do PWM no arduino é de 0-255, todavia,
    --                          para que o robô execute algum movimento, o PWM mínimo aplicado 
    --                          é de 180.
  --          Caso o valor de velocidade não for passado por parâmetro, então 
    --                          ele assume o valor da constante VELOCIDADE_PWM_DEFAULT
  **@return void 
  **/
    void re(long &tempo, unsigned int velocidade=VEL_PWM_DEFAULT);

  /**
  **Método que faz o robô virar à direita
  --   Este método faz o robô virar a direita em uma angulação e uma velocidade definida por  
    --     parâmetro. a velocidade é definida pelo intervalo de 180 a 255, sendo 180 o mínimo e 
    --     255 o máximo. 
  **@param angulo int : angulação que o robô deve virar.  
    --                      Caso o valor de angulo não for passado por parâmetro, então ele assume 
    --                      o valor da constante ANGULACAO_DEFAULT
  **@param velocidade int : velocidade do robô no movimento
  --                A velocidade do robô é medida com base na saída PWM aplicada nos motores. 
    --                          O range do PWM no arduino é de 0-255, todavia, para que o robô execute algum 
    --                          movimento, o PWM mínimo aplicado é de 180.
  --          Caso o valor de velocidade não for passado por parâmetro, então ele assume o
    --                          valor da constante VELOCIDADE_PWM_DEFAULT
  **@return void 
  **/
    void direita(int angulo=ANGULACAO_DEFAULT);


  /**
  **Método que faz o robô virar à esquerda
  --   Este método faz o robô virar a esquerda em uma angulação e uma velocidade definida por parâmetro. 
    --     a velocidade é definida pelo intervalo de 180 a 255, sendo 180 o mínimo e 255 o máximo. 
  **@param angulo int : angulação que o robô deve virar.  
    --                     Caso o valor de angulo não for passado por parâmetro, então ele assume o valor 
    --                       da constante ANGULACAO_DEFAULT
  **@return void 
  **/
    void esquerda(int angulo=ANGULACAO_DEFAULT);

  /**
  **Método que para a execução de qualquer movimento do robô
  **@return void
  **/
    void parar();                


/*----------------------Métodos de Configuração -------------------------*/
    /**
    ** Método que muda o valor da velocidade do robô
    **@param velocidade int: velocidade do robô, em cm/s
    **/
    void setVelocidade(int velocidade);

    /**
    ** Método que retorna a velocidade do robô
    **@return velocidade int
    **/
    int getVelocidade();
};//fim class
#endif
