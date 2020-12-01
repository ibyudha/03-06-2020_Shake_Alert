// ---------------------------------------------------------------------------
// Created by Gus Yudha on 03/06/2020
// ---------------------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define tombolOn 10
#define tombolOff 9
#define buzzer 11
#define ledPutih 12 

LiquidCrystal_I2C lcd(0x27,16,2);

RF24 radio(7,8);
const byte alamat[][6] = {"18150", "51012"};
boolean kondisiSaklar = 0;
boolean gempa = 0;

void setup() {
  lcd.begin();
  lcd.backlight();
  
  radio.begin();
  radio.openWritingPipe(alamat[0]);
  radio.openReadingPipe(1, alamat[1]);
  radio.setPALevel(RF24_PA_MAX);

  pinMode(tombolOn, INPUT);
  pinMode(tombolOff, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPutih, OUTPUT);
  
  labelPesan();
}

void loop() {
  delay(5);
  
  if(kondisiSaklar == LOW) {
    lcd.setCursor(0,0);
    lcd.print("STATUS SENSOR:  ");
    lcd.setCursor(0,1);
    lcd.print("OFF             ");
  } else {
    lcd.setCursor(0,0);
    lcd.print("STATUS SENSOR:  ");
    lcd.setCursor(0,1);
    lcd.print("ON             ");
  }
  
  radio.stopListening();
  if( digitalRead(tombolOn) == HIGH){
    kondisiSaklar = HIGH;
  }
  if( digitalRead(tombolOff) == HIGH){
    kondisiSaklar = LOW;
    gempa = 0;
  }
  radio.write(&kondisiSaklar, sizeof(kondisiSaklar));
  
  radio.startListening();
  if (radio.available()) {
    while (radio.available()) {
      int trigger = 0;
      radio.read(&trigger, sizeof(trigger));
      if (trigger == HIGH){
        gempa = HIGH;
      }
    }
  }

  if(gempa == HIGH) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPutih, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPutih, LOW);
  }
  
}

void labelPesan(){
  lcd.setCursor(0,0);
  lcd.print("  ALARAM GEMPA  ");
    delay ( 1000 );
  lcd.setCursor(0,1);
  lcd.print("  UAS ROBOTIKA  ");
    delay ( 1000 );
  lcd.setCursor(0,0);
  lcd.print("DICIPTAKAN OLEH:");
    delay ( 1000 );
  lcd.setCursor(0,1);
  lcd.print(" YUDHA  WIRAWAN ");
    delay ( 2000 );
  lcd.setCursor(0,0);
  lcd.print(" KONTAK PERSON: ");
    delay ( 1000 );
  lcd.setCursor(0,1);
  lcd.print("= 082146966897 =");
    delay ( 1000 );
  lcd.setCursor(0,0);
  lcd.print("MENGHIDUPKAN ...");
    delay ( 1000 );
  lcd.setCursor(0,1);
  lcd.print("... ... ... ... ");
    delay ( 1000 );
  lcd.clear();
}
