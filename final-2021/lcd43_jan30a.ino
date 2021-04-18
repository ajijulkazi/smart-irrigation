#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

int soil;
int moisture;
int pumppin = 8;
int trigpin = 6;
int echopin = 7;
int distance;
long duration;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.begin();
  dht.begin();
  pinMode(pumppin, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
}

void loop()
{
  soil = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  digitalWrite(trigpin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration*0.034/2;
  moisture = map(soil,275,890,100,0);
  lcd.setCursor(2,0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0,2);
  lcd.print("H=");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(11,2);
  lcd.print("T=");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(9,3);
  lcd.print("L=");
  lcd.print(distance);
  lcd.print("cm");
  if(moisture<60)
  {
    if(t>23){
      digitalWrite(pumppin, HIGH);
      lcd.setCursor(0,1);
      lcd.print("Moisture = ");
      lcd.print(moisture);
      lcd.print("%");
      lcd.setCursor(0,3);
      lcd.print("Pump On");
      }
  
    else{
      digitalWrite(pumppin, LOW);
      lcd.setCursor(0,1);
      lcd.print("Moisture = ");
      lcd.print(moisture);
      lcd.print("%");
      lcd.setCursor(0,3);
      lcd.print("Pump OFF");
    
    }
  }
 else if(moisture>60)
  {
    if(distance>9){
    digitalWrite(pumppin,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Moisture = ");
    lcd.print(moisture);
    lcd.print("%");
    lcd.setCursor(0,3);
    lcd.print("Pump ON");
    }
   else {
    digitalWrite(pumppin,LOW);
    lcd.setCursor(0,1);
    lcd.print("Moisture = ");
    lcd.print(moisture);
    lcd.print("%");
    lcd.setCursor(0,3);
    lcd.print("Pump OFF");

   }
  }
  else{
    digitalWrite(pumppin,LOW);
    lcd.setCursor(0,3);
    lcd.print("Pump OFF");
  }
  
  
  delay(1000);
  lcd.clear();
}
