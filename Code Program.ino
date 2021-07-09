/**
 * SMART OMAR
 * by Kelompok 11
 * Description:
 * Smart O.M.A.R. adalah sebuah sistem berbasis Arduino yang 
 * diterapkan di pintu mall agar berfungsi untuk menyeleksi  
 * pengunjung yang akan masuk ke dalam mall.
*/

#include <avr/sleep.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define motor_pin 9
#define dht_dpin 0
#define interruptPin 2
#define buzzer_out 6
DHT dht(dht_dpin, DHT11);
int pirState = LOW; 
float temperature;
void tempSensor();
void wakeup();
void gonna_sleep();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(buzzer_out, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  pinMode(interruptPin,INPUT);
  lcd.begin(16, 2);
  Serial.println("Mesin dinyalakan!");
  lcd.print("SMARTOMAR");
  lcd.setCursor(0,1);
  lcd.print("activated!");
  lcd.setCursor(0,0);
  delay(1000);
  lcd.clear();
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motor_pin, LOW);
  dht.begin();
}

void loop() {
  delay(250);
  gonna_sleep();
}

void gonna_sleep(){
//  sleep_enable();
//  lcd.print("Zzz");
//  attachInterrupt(0, wakeUp, LOW);
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  delay(1000);
//  sleep_cpu();
  if(digitalRead(interruptPin) == 1){
    tempSensor();
    delay(250);
  }
  else {
    lcd.clear();
    Serial.println("Gaada Orang");
    lcd.print("Gaada orang");
    sleep_mode();
  }
}

//void wakeUp(){
//  lcd.clear();
//  Serial.println("There is a person here!");
//  lcd.print("There is a person here!");
//  lcd.print("Hi! I'm Awake");
//  sleep_disable();
//  detachInterrupt(0);
//}

void tempSensor(){
  lcd.clear();
  lcd.print("Hi! :)");
  lcd.setCursor(0,1);
  temperature = dht.readTemperature();
  Serial.println(temperature);
  lcd.print("Temperature : ");
  lcd.print(temperature);
  delay(500);
  if(temperature > 37.2){
    handleDecline();
  } else {
    handleAccept();
  }
}

void handleAccept(){
  lcd.clear();
  digitalWrite(motor_pin, HIGH);
  Serial.println("Masuk");
  lcd.print("Silakan masuk");
  delay(250);
  digitalWrite(motor_pin, LOW);
}

void handleDecline(){
  lcd.clear();
  tone(6, 440, 1500);
  Serial.println("Keluar");
  lcd.print("Dilarang Masuk");
  delay(250);
  noTone(6);
}
