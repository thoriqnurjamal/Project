#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  
int ledR = 8;
int ledG = 7;
int sensor = A0;
int buzzer = 6;
int sensorThresh = 400;

void setup()
{
pinMode(ledR, OUTPUT);
pinMode(ledG,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(sensor,INPUT);
Serial.begin(9600);
lcd.begin(16,2);
}

void loop()
{
  int analogValue = analogRead(sensor);
  Serial.print(analogValue);
  if(analogValue>sensorThresh)
  {
    digitalWrite(ledR,HIGH);
    digitalWrite(ledG,LOW);
    tone(buzzer,1000,10000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("BAHAYA");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("AREA BERBAHAYA");
    delay(1000);
  }
  else
  {
    digitalWrite(ledG,HIGH);
    digitalWrite(ledR,LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AMAN");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("BERSIH");
    delay(1000);
  }  
     
}