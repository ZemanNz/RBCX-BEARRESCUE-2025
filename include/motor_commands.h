#include "Arduino.h"
#include "robotka.h"

/////////////////////////////////////
static const uint8_t Bbutton1 = 34;
static const uint8_t Bbutton2 = 35;
const float roztec = 200.0; // roztec kol v mm


float koeficient_r_f = 1.066;
float koeficient_l_f = 1.034;
float koeficient_r_b = 1.066;
float koeficient_l_b = 1.035;


const float ML_25 = 1.00f, MP_25 = 1.00f;
const float ML_50 = 1.00f, MP_50 = 0.9895f;
const float ML_70 = 1.00f, MP_70 = 0.9021f;
const float ML_95 = 1.00f, MP_95 = 0.65f;
//maximalni rychlost vice nez 60% z 4200 tzs, cirka 2600 je maximalka--65% na 95
// ted je potreba upravovat konstanty, podle noveho maxima 2600
const float ML_25_back = 1.00f, MP_25_back = 1.00f;
const float ML_50_back = 1.00f, MP_50_back = 0.99f;
const float ML_70_back = 1.00f, MP_70_back = 0.98f;
const float ML_95_back = 1.00f, MP_95_back = 0.97f;

void forward(float mm, float speed) {
    float MLc, MPc;
    if (mm > 0) {
        if (speed == 25)      { MLc = ML_25; MPc = MP_25; }
        else if (speed == 50) { MLc = ML_50; MPc = MP_50; }
        else if (speed == 70) { MLc = ML_70; MPc = MP_70; }
        else if (speed == 95) { MLc = ML_95; MPc = MP_95; }
        else                  { MLc = ML_50; MPc = MP_50; }
        Serial.printf("[FORWARD] FWD | speed: %.2f | MLc: %.4f | MPc: %.4f | L: %.2f | P: %.2f\n", speed, MLc, MPc, speed * MLc, speed * MPc);
        rkMotorsDrive(mm, mm, speed * MLc, speed * MPc);
    } else {
        if (speed == 25)      { MLc = ML_25_back; MPc = MP_25_back; }
        else if (speed == 50) { MLc = ML_50_back; MPc = MP_50_back; }
        else if (speed == 70) { MLc = ML_70_back; MPc = MP_70_back; }
        else if (speed == 95) { MLc = ML_95_back; MPc = MP_95_back; }
        else                  { MLc = ML_50_back; MPc = MP_50_back; }
        Serial.printf("[FORWARD] BACK | speed: %.2f | MLc: %.4f | MPc: %.4f | L: %.2f | P: %.2f\n", speed, MLc, MPc, speed * MLc, speed * MPc);
        rkMotorsDrive(mm, mm, speed * MLc, speed * MPc);
    }
}
void encodery() {
  Serial.printf("L: %f, R: %f\n", rkMotorsGetPositionLeft(), rkMotorsGetPositionRight());
}
void radius_r(int degrees, int polomer, int speed)
{
  float sR = speed * ((polomer) / (polomer + roztec));
  float sL = speed ;
  if(degrees > 0){
  float stupne = degrees * koeficient_r_f;
  rkMotorsDrive((((polomer + roztec) * PI * stupne) / 180)  ,(( polomer * PI * stupne) / 180) , sL * MP_50_back , sR * MP_50);
  }
  else{
  float stupne= degrees * koeficient_r_b;
  rkMotorsDrive((((polomer + roztec) * PI * stupne) / 180) , (( polomer * PI * stupne) / 180)  , sL * MP_50_back , sR * MP_50_back);
  }
}
void radius_l(int degrees, int polomer, int speed){
  float sR = speed ;
  float sL = speed * ((polomer) / (polomer + roztec));
  if(degrees > 0){
  float stupne = degrees * koeficient_l_f;
  rkMotorsDrive((( polomer * PI * stupne) / 180) , (((polomer + roztec) * PI * stupne) / 180)  , sL * MP_50_back , sR * MP_50);
  }
  else{
  float stupne = degrees * koeficient_l_b;
  rkMotorsDrive((( polomer * PI * stupne) / 180), (((polomer + roztec) * PI * stupne) / 180) , sL * ML_50_back , sR * MP_50_back);
  }
}
void turn_on_spot(int degrees){
  rkMotorsDrive(((degrees/360) * PI * roztec), ((degrees/360) * -PI * roztec), 30 * MP_50_back , 30 * MP_50);
}
void back_buttons(int speed)
{
    rkMotorsSetPower(-(speed * MP_50_back), -(speed * MP_50));
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