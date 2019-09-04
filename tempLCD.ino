/*
Termistor based temperature monitor with LCD display.
Requires:
- LCD display (ground, 5v, A4, A5)
- Termistor 
- Resistor (10k) 
Cicle: in -> termistor, out -> A0 , out -> 10k resistor, 10k resistor -> grnd)

*/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
                        
// The LCD constructor - address shown is 0x27 - may or may not be correct for yours
// Also based on YWRobot LCM1602 IIC V1
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

void setup()
{
 
  lcd.begin(16,2); // sixteen characters across - 2 lines
  lcd.backlight();
  // first character - 1st line
  lcd.setCursor(0,0);
  lcd.print("Current temp:");
  
}
 
 
void loop()
{
  Vo = analogRead(ThermistorPin);
  // convert voltage to Kelvin and then subtract to get C
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  // on 2nd line print temperature in far right
  // 8th character - 2nd line 
  lcd.setCursor(8,1);
  lcd.print(T); lcd.print("C");
  delay(500);                                      

}