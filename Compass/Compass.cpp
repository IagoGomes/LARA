/* Author = helscream (Omer Ikram ul Haq)
  Last edit date = 2014-06-22
  Website: http://hobbylogs.me.pn/?p=17
  Location: Pakistan
  Ver: 0.1 beta --- Start
  Ver: 0.2 beta --- Debug feature included
*/

#include <Arduino.h>
#include "Wire/Wire.h"
#include "Compass.h"

/**------------------------------------------------------------
                   FUNÇÕES IMPLEMENTADAS 
-------------------------------------------------------------**/

/**
**Método Construtor da Classe
**@return void
**/
 Compass :: Compass(){
  compass_x_offset =40.68;
  compass_y_offset = 38.62;
  compass_z_offset = -285.30;
  compass_gain_fact = 1;
  compass_x_gainError = 1.08;
  compass_y_gainError = 1.07;
  compass_z_gainError = 1.00;
  bearing = 0;
  compass_x = 0;
  compass_y = 0;
  compass_z = 0;
  compass_debug = 0;
  angleReference = 0;
}//fim compass

/**
** Método que seta os valores dos offset dos eixos da bússola
**@return void
**/
void Compass :: setOffset(float x_offset, float y_offset, float z_offset){
  this -> compass_x_offset = x_offset;
  this -> compass_y_offset = y_offset;
  this -> compass_z_offset = z_offset;
}//fim setOffset

/**
** Método que seta os valores do ganho de erro dos eixos da bússola
**@return void
**/
void Compass :: setGainError(float x_gainError, float y_gainError, float z_gainError){
  this -> compass_x_gainError = x_gainError;
  this -> compass_y_gainError = y_gainError;
  this -> compass_z_gainError = z_gainError;
}//fim setGainError

/**
 ** Método que retorna (por referência) a leitura dos eixos da bússulo, sem nenhum tratamento prévio. 
 --   Os valores retornados são os lidos diretamente do barramento i2c
 ** @return void
 **/
void Compass :: getAxis(int *x_axis, int *y_axis, int *z_axis){
  /*int *x, *y, *z;
  
  x=&x_axis;
  y=&y_axis;
  z=&z_axis;
   */
  compass_read_XYZdata();
   
  *x_axis=compass_x;
  *y_axis=compass_y;
  *z_axis=compass_z;
}//fim getAxis

/**
 ** Método que retorna o ângulo que o robô precisa deslocar para se alinhar ao norte (ângulo de referência)
 ** 
 **@return angle float: ângulo do robô à origem (referência; norte do robô) 
 **/
float Compass :: getAngleToReference(){
  float ang =(bearing - angleReference + 360);
  if(ang > 180)
    ang-=360;
  return ang;
}//fim getAngleToReference

/**
 **Método que retorno o ângulo de referência (norte do robô)
 **@param angle float: ângulo de referÊncia
 **@return void
 **/
 void Compass :: setReferenceAngle(float angulo){
   this->angleReference = angulo;
 }//fim setReferenceAngle

/**
 **Método que retorna o ângulo de referência do robô (norte do robô)
 **@return angleReference float
 **/
float Compass :: getReferenceAngle(){
  return angleReference;
}//fim getReferenceAngle

/**------------------------------------------------------------
          FUNÇÕES PRESENTES NA VERSÃO BASEDA DA BIBLIOTECA
Modificadas
-------------------------------------------------------------**/

// --------------------------------------------------------------------------
// Setting the gain
// This Function updates the gain_fact variable
/**
 **Modificação: Substituição das estruturas de if-else por switch
 **/
void Compass :: compass_init(int gain){

  byte gain_reg,mode_reg;
  Wire.beginTransmission(compass_address);
  Wire.write(0x01);

  switch (gain){
    case 0:
          gain_reg = 0b00000000;
          compass_gain_fact = 0.73;
          break;
     case 1:
          gain_reg = 0b00100000;
          compass_gain_fact= 0.92;
          break;
     case 2:
          gain_reg = 0b01000000;
          compass_gain_fact= 1.22;
          break; 
     case 3:
          gain_reg = 0b01100000;
          compass_gain_fact= 1.52;
          break;
     case 4:
          gain_reg = 0b10000000;
          compass_gain_fact= 2.27;
          break;
     case 5:
          gain_reg = 0b10100000;
          compass_gain_fact= 2.56;
          break;
     case 6:
          gain_reg = 0b11000000;
          compass_gain_fact= 3.03;
          break;
     case 7:
          gain_reg = 0b11100000;
          compass_gain_fact= 4.35;
          break;
     default:
          break;
  }//fim switch
  
  Wire.write(gain_reg); // bit configuration = g2 g1 g0 0 0 0 0 0, g2 g1 g0 = 0 0 1 for 1.3 guass and 0 1 0 for 1.9 Guass
  Wire.write(0b00000011);  // Putting the Magnetometer in idle
  // Writing the register value 0000 0000 for continous mode
  // Writing the register value 0000 0001 for single
  // Writing the register value 0000 0011 for Idel
  Wire.endTransmission();
  //Serial.print("Gain atualizado para  = ");
  //Serial.print(compass_gain_fact);
  //Serial.println(" mG/bit");
}// fim compass_init


/**------------------------------------------------------------
          FUNÇÕES PRESENTES NA VERSÃO BASEDA DA BIBLIOTECA
Sem modificação
-------------------------------------------------------------**/

/**
 **Método que atualiza os valores das variáveis compass_x_scalled, compass_y_scalled e compass_z_scalled
 **  com os valores atuais dos eixos da bússola
 **@return void
 **/
void Compass :: compass_scalled_reading(){
  compass_read_XYZdata();
  compass_x_scalled=compass_x*compass_gain_fact*compass_x_gainError+compass_x_offset;
  compass_y_scalled=compass_y*compass_gain_fact*compass_y_gainError+compass_y_offset;
  compass_z_scalled=compass_z*compass_gain_fact*compass_z_gainError+compass_z_offset;
}//fim compass_scalled_reading


/**
**Método que realiza o cálculo do ângulo do robô
**@return bearing float : ângulo cálculado
*/
float Compass :: compass_heading(){
  compass_scalled_reading();
  if (compass_y_scalled>0){
    bearing = 90-atan(compass_x_scalled/compass_y_scalled)*compass_rad2degree;
  }else if (compass_y_scalled<0){
    bearing = 270-atan(compass_x_scalled/compass_y_scalled)*compass_rad2degree;
  }else if (compass_y_scalled==0 & compass_x_scalled<0){
    bearing = 180;
  }else{
    bearing = 0;
  }//fim if-else
  return bearing;
}//fim compass_heading


// --------------------------------------------------------------------------
// This Function calculates the offset in the Magnetometer
// using Positive and Negative bias Self test capability
// This function updates X_offset Y_offset and Z_offset Global variables
// Call Initialize before 
void Compass :: compass_offset_calibration(int select){
  // ***********************************************************
  // offset_calibration() function performs two taskes
  // 1. It calculates the diffrence in the gain of the each axis magnetometer axis, using 
  //    inbuilt self excitation function of HMC5883L (Which is useless if it is used as a compass
  //    unless you are very unlucy and got a crapy sensor or live at very High or low temperature)
  // 2. It calculates the mean of each axes magnetic field, when the Magnetometer is rotated 360 degree
  // 3. Do Both
  // ***********************************************************    
  
  
  // *****************************************************************************************
  // Gain offset estimation
  // ***************************************************************************************** 
  if (select == 1 | select == 3){ // User input in the function
    // Configuring the Control register for Positive Bais mode
    //Serial.println("Calibrating the Magnetometer ....... Gain");
    Wire.beginTransmission(compass_address);
    Wire.write(0x00);
    Wire.write(0b01110001); // bit configuration = 0 A A DO2 DO1 DO0 MS1 MS2

    /*
    A A                        DO2 DO1 DO0      Sample Rate [Hz]      MS1 MS0    Measurment Mode
     0 0 = No Average            0   0   0   =   0.75                   0   0   = Normal  
     0 1 = 2 Sample average      0   0   1   =   1.5                    0   1   = Positive Bias
     1 0 = 4 Sample Average      0   1   0   =   3                      1   0   = Negative Bais
     1 1 = 8 Sample Average      0   1   1   =   7.5                    1   1   = -
     1   0   0   =   15 (Default)
     1   0   1   =   30
     1   1   0   =   75
     1   1   1   =   -
     */
    Wire.endTransmission();
    
    compass_read_XYZdata(); // Disregarding the first data

    // Reading the Positive baised Data
    while(compass_x<200 | compass_y<200 | compass_z<200){   // Making sure the data is with Positive baised
       compass_read_XYZdata();
    }//fim while
    
    compass_x_scalled=compass_x*compass_gain_fact;
    compass_y_scalled=compass_y*compass_gain_fact;
    compass_z_scalled=compass_z*compass_gain_fact;
        
    // Offset = 1160 - Data_positive
    compass_x_gainError = (float)compass_XY_excitation/compass_x_scalled;
    compass_y_gainError = (float)compass_XY_excitation/compass_y_scalled;
    compass_z_gainError = (float)compass_Z_excitation/compass_z_scalled;

    // Configuring the Control register for Negative Bais mode
    Wire.beginTransmission(compass_address);
    Wire.write(0x00);
    Wire.write(0b01110010); // bit configuration = 0 A A DO2 DO1 DO0 MS1 MS2

    /*
    A A                        DO2 DO1 DO0      Sample Rate [Hz]      MS1 MS0    Measurment Mode
     0 0 = No Average            0   0   0   =   0.75                   0   0   = Normal  
     0 1 = 2 Sample average      0   0   1   =   1.5                    0   1   = Positive Bias
     1 0 = 4 Sample Average      0   1   0   =   3                      1   0   = Negative Bais
     1 1 = 8 Sample Average      0   1   1   =   7.5                    1   1   = -
                                 1   0   0   =   15 (Default)
                                 1   0   1   =   30
                                 1   1   0   =   75
                                 1   1   1   =   -
     */
    Wire.endTransmission();
    
    compass_read_XYZdata(); // Disregarding the first data
    // Reading the Negative baised Data
    while(compass_x>-200 | compass_y>-200 | compass_z>-200){   // Making sure the data is with negative baised
       compass_read_XYZdata();
    }//fim while
    
    compass_x_scalled=compass_x*compass_gain_fact;
    compass_y_scalled=compass_y*compass_gain_fact;
    compass_z_scalled=compass_z*compass_gain_fact;
    
    // Taking the average of the offsets
    compass_x_gainError = (float)((compass_XY_excitation/abs(compass_x_scalled))+compass_x_gainError)/2;
    compass_y_gainError = (float)((compass_XY_excitation/abs(compass_y_scalled))+compass_y_gainError)/2;
    compass_z_gainError = (float)((compass_Z_excitation/abs(compass_z_scalled))+compass_z_gainError)/2;
      
    Serial.print("x_gain_offset = ");
    Serial.println(compass_x_gainError);
    Serial.print("y_gain_offset = ");
    Serial.println(compass_y_gainError);
    Serial.print("z_gain_offset = ");
    Serial.println(compass_z_gainError);
    
  }//fim if
  
   // Configuring the Control register for normal mode
  Wire.beginTransmission(compass_address);
  Wire.write(0x00);
  Wire.write(0b01111000); // bit configuration = 0 A A DO2 DO1 DO0 MS1 MS2

  /*
  A A                        DO2 DO1 DO0      Sample Rate [Hz]      MS1 MS0    Measurment Mode
   0 0 = No Average            0   0   0   =   0.75                   0   0   = Normal  
   0 1 = 2 Sample average      0   0   1   =   1.5                    0   1   = Positive Bias
   1 0 = 4 Sample Average      0   1   0   =   3                      1   0   = Negative Bais
   1 1 = 8 Sample Average      0   1   1   =   7.5                    1   1   = -
                               1   0   0   =   15 (Default)
                               1   0   1   =   30
                               1   1   0   =   75
                               1   1   1   =   -
   */
  Wire.endTransmission();
  
  // *****************************************************************************************
  // Offset estimation
  // *****************************************************************************************
   if (select == 2 | select == 3){// User input in the function
   // Serial.println("Calibrating the Magnetometer ....... Offset");
    //Serial.println("Please rotate the magnetometer 2 or 3 times in complete circules with in one minute ............. ");
    
    for(byte i=0;i<10;i++){   // Disregarding first few data
         compass_read_XYZdata();
     }//fim for
    
    float x_max=-4000,y_max=-4000,z_max=-4000; 
    float x_min=4000,y_min=4000,z_min=4000;
    
    /*
    Debug code ------------------------------
    */
    if (compass_debug == 1){
      Serial.println("Starting Debug data in ");
      delay(1000);
      Serial.println("3");
      delay(1000);
      Serial.println("2");
      delay(1000);
      Serial.println("1");
      delay(1000);
      Serial.println("0");
      Serial.println();
      Serial.println("***********");
      Serial.println("Debug -- (Offset Calibration)");
      Serial.println("***********");
    }//fim if
    // End Debug code
  
    unsigned long t = millis();
    while(millis()-t <= 30000){
      
      compass_read_XYZdata();
      
      compass_x_scalled=(float)compass_x*compass_gain_fact*compass_x_gainError;
      compass_y_scalled=(float)compass_y*compass_gain_fact*compass_y_gainError;
      compass_z_scalled=(float)compass_z*compass_gain_fact*compass_z_gainError;
      
      if (compass_debug == 1){  //------------------ Debug Data
        Serial.print(compass_x_scalled);
        Serial.print("\t");
        Serial.print(compass_y_scalled);
        Serial.print("\t");
        Serial.println(compass_z_scalled);
      }//--------------------------------- End Debug Data
  
      x_max = max(x_max,compass_x_scalled);
      y_max = max(y_max,compass_y_scalled);
      z_max = max(z_max,compass_z_scalled);
  
      
      x_min = min(x_min,compass_x_scalled);
      y_min = min(y_min,compass_y_scalled);
      z_min = min(z_min,compass_z_scalled);
   
    }//fim if
    
    /*
    Debug code ------------------------------
    */
    if (compass_debug == 1){
      Serial.println();
      Serial.println("***********");
      Serial.println("End Debug -- (Offset Calibration)");
      Serial.println("***********");
    }//fim if
    // End Debug code
  
    compass_x_offset = ((x_max-x_min)/2)-x_max;
    compass_y_offset = ((y_max-y_min)/2)-y_max;
    compass_z_offset = ((z_max-z_min)/2)-z_max;
    
    Serial.print("Offset x  = ");
    Serial.print(compass_x_offset);
    Serial.println(" mG");
    Serial.print("Offset y  = ");
    Serial.print(compass_y_offset);
    Serial.println(" mG");
    Serial.print("Offset z  = ");
    Serial.print(compass_z_offset);
    Serial.println(" mG");
  
  } //fim while
}//fim compass_offset_calibration


/**
** Método que atualiza os valores das variáveis que armazenam os valores dos eixos lidos pela bússola.
--  Os valores são lidos por meio do protocolo I2C
** @return void
**/
void Compass :: compass_read_XYZdata(){
  Wire.beginTransmission(compass_address);
  Wire.write(0x02);
  Wire.write(0b10000001); 
  // Writing the register value 0000 0000 for continous mode
  // Writing the register value 0000 0001 for single
  Wire.endTransmission();
  Wire.requestFrom(compass_address,6);
  if (6 <= Wire.available()){
    compass_x = Wire.read()<<8 | Wire.read();//eixo x
    compass_z = Wire.read()<<8 | Wire.read();//eixo y
    compass_y = Wire.read()<<8 | Wire.read();//eixo z
  }//fim if
}//fim compass_read_XYZdata
