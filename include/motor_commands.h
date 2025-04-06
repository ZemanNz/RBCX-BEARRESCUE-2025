#include "Arduino.h"
#include "robotka.h"

/////////////////////////////////////
static const uint8_t Bbutton1 = 34;
static const uint8_t Bbutton2 = 35;
const float roztec = 161.185; // roztec kol v mm
const float MP = 0.988425;
const float ML = 1;//rozdil v motorech
const float MP_back = 0.98542;
const float ML_back = 1;//rozdil v motorech
float koeficient_r_f = 1.066;
float koeficient_l_f = 1.034;
float koeficient_r_b = 1.066;
float koeficient_l_b = 1.035;


void encodery() {
  Serial.printf("L: %f, R: %f\n", rkMotorsGetPositionLeft(), rkMotorsGetPositionRight());
}
void forward(float mm, float speed)// od 0 do + 100, i s desetinyma cislama
{
  if(mm>0){
    rkMotorsDrive(mm, mm* MP , speed * ML , speed * MP);
  }
  else{
    rkMotorsDrive(mm, mm* MP_back , speed * ML_back , speed * MP_back);
  }
}
void radius_r(int degrees, int polomer, int speed)
{
  float sR = speed * ((polomer) / (polomer + roztec));
  float sL = speed ;
  if(degrees > 0){
  float stupne = degrees * koeficient_r_f;
  rkMotorsDrive((((polomer + roztec) * PI * stupne) / 180) * ML ,(( polomer * PI * stupne) / 180) * MP, sL * ML , sR * MP);
  }
  else{
  float stupne= degrees * koeficient_r_b;
  rkMotorsDrive((((polomer + roztec) * PI * stupne) / 180) * ML_back, (( polomer * PI * stupne) / 180) * MP_back , sL * ML_back , sR * MP_back);
  }
}
void radius_l(int degrees, int polomer, int speed){
  float sR = speed ;
  float sL = speed * ((polomer) / (polomer + roztec));
  if(degrees > 0){
  float stupne = degrees * koeficient_l_f;
  rkMotorsDrive((( polomer * PI * stupne) / 180) * ML, (((polomer + roztec) * PI * stupne) / 180) * MP , sL * ML , sR * MP);
  }
  else{
  float stupne = degrees * koeficient_l_b;
  rkMotorsDrive((( polomer * PI * stupne) / 180)* ML_back, (((polomer + roztec) * PI * stupne) / 180) * MP_back, sL * ML_back , sR * MP_back);
  }
}
void turn_on_spot(int degrees){
  rkMotorsDrive(((degrees/360) * PI * roztec), ((degrees/360) * -PI * roztec), 30 * ML , 30 * MP);
}
void back_buttons(int speed)
{
    rkMotorsSetPower(-(speed * ML_back), -(speed * MP_back));
    while (true)
    {
      if ((digitalRead(Bbutton1) == LOW)&&(digitalRead(Bbutton2) == LOW)){
        break;
      }
      delay(100);
    }
    delay(150);
    Serial.println("Obě Tlačítka STISKNUTY!");
    rkMotorsSetPower(0, 0);
}
//timeout