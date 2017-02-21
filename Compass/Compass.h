/* 
  Biblioteca para o controle e manipulação das funções de bússola, por meio do protocolo I2C e da biblioteca Wire
  - A biblioteca é baseada na biblioteca "compass", v.2, disponível em :<https://github.com/helscream/HMC5883L_Header_Arduino_Auto_calibration
  - Documentação da biblioteca que essa implementação utiliza como referência está disponível no link: <http://hobbylogs.me.pn/?p=17#more-17>
*/


#ifndef Compass_h
#define Compass_h
  

class Compass{
  
  private:
    //ângulo em relação ao norte mangnético da terra
    float bearing;

    float compass_x_scalled,
          compass_y_scalled,
          compass_z_scalled;
    
    //offset dos eixos
    float compass_x_offset, 
          compass_y_offset,
          compass_z_offset;

   //ganho de erro dos eixos
   float compass_x_gainError,
         compass_y_gainError,
         compass_z_gainError;

   float compass_gain_fact;

   //variáveis que armazena os valores dos eixos da vússola lidos diretamento do barramento i2c
   int compass_x,
       compass_y,
       compass_z;
    
   int compass_debug;//variáveis que habilita a impressão do debug de calibração do sensor

   float angleReference;//ângulo de referência do robô; "Norte do robô".


   // Definitions ----------------------------------------------------------------
   #define compass_address 0x1E       // Endereço I2C do sensor
   #define compass_XY_excitation 1160 // The magnetic field excitation in X and Y direction during Self Test (Calibration)
   #define compass_Z_excitation 1080  // The magnetic field excitation in Z direction during Self Test (Calibration)
   #define compass_rad2degree 57.3


   #define compass_cal_x_offset 116   // Manually calculated offset in X direction
   #define compass_cal_y_offset 225   // Manually calculated offset in Y direction
   #define compass_cal_x_gain 1.1     // Stored Gain offset at room temperature
   #define compass_cal_y_gain 1.12    // Stored Gain offset at room temperature


   /**
   ** Método que atualiza os valores das variáveis compass_x, compass_y e compass_z, lidos do barramento i2c
   **@return void
   **/
   void compass_read_XYZdata();

   /**
   **Método que atualiza os valores das variáveis compass_x_scalled, compass_y_scalled e compass_z_scalled
   **  com os valores atuais dos eixos da bússola
   **@return void
   **/
   void compass_scalled_reading();

  public:

    /**
    **Método Construtor da classe
    --Inicializa e configura as variáveis e parâmetros da bússola
    **@return void
    **/
    Compass();
    
    /**
    **Método que realiza a calibração do sensor bússola
    **@param select int: 
    --                  1- calibra o ganho de erro do sensor
    --                  2- calibra o offset dos eixos do sensor
    --                  3- calibra o ganho de erro e o offset do sensor
    **@return void
    **/
    void compass_offset_calibration(int select);

    /**
    ** Método define o ganho do sensor, baseado em uma escala. 
    **@param gain int:
    --                gain=0: max scale = 0.73 gauss
    --                gain=1: max scale = 0.92 gauss
    --                gain=2: max scale = 1.22 gauss
    --                gain=3: max scale = 1.52 gauss
    --                gain=4: max scale = 2.27 gauss
    --                gain=5: max scale = 2.56 gauss
    --                gain=6: max scale = 3.03 gauss
    --                gain=7: max scale = 4.35 gauss
    **@return void
    **/
    void compass_init(int gain);

    /**
     **Método que atualiza os valores das variáveis compass_x_scalled, compass_y_scalled e compass_z_scalled
     **  com os valores atuais dos eixos da bússola e realiza o cálculo do ângulo do robô em relação ao norte mangnético
     **@return bearing float : ângulo
     **/
    float compass_heading();
    
    /**
    **Método que seta o valor dos offset do sensor. Esse offset é usado na calibração do sensor, e no cálculo do ângulo 
    **  em relação ao norte magnético
    **@param x_offset float : offset do eixo x
    **@param y_offset float : offset do eixo y
    **@param z_offset float : offset do eixo z
    **@return void
    **/
    void setOffset(float x_offset, float y_offset, float z_offset);

    /**
    **Método que seta o valor dos ganhos de erros do eixos dos sensores. Esses ganho de erro são usados na calibração do sensor,
    **  e no cálculo do ângulo em relação ao norte magnético
    **@param x_gainError float : ganho de erro do eixo x
    **@param y_gainError float : ganho de erro do eixo y
    **@param z_gainError float : ganho de erro do eixo z
    **@return void
    **/
    void setGainError(float x_gainError, float y_gainError, float z_gainError);

    /**
    ** Método que retorna (por referência) os valores das leituras dos eixos da bússola. Esse valor é lido do barramento i2c e 
    **   não recebe nenhum tratamentom extra
    **@param x_axis &int : referência que armazenará o valor do eixo x
    **@param y_axis &int : referência que armazenará o valor do eixo y
    **@param z_axis &int : referência que armazenará o valor do eixo z
    **/
    void getAxis(int *x_axis, int *y_axis, int *z_axis);

    /**
    ** Método que retorna o ângulo que o robô precisa deslocar para se alinhar ao norte (ângulo de referência)
    ** 
    **@return angle float: ângulo do robô à origem (referência; norte do robô)
    --                     o retorno varia de -180º a 180º 
    **/
    float getAngleToReference();

    /**
    **Método que retorno o ângulo de referência (norte do robô)
    **@param angle float: ângulo de referÊncia
    **@return void
    **/
    void setReferenceAngle(float angulo);

    /**
     **Método que retorna o ângulo de referência do robô (norte do robô)
     **@return angleReference float
     **/
    float getReferenceAngle();
};
#endif
