// ---------------------------------------------------------------------------
// Created by Gus Yudha on 03/06/2020
// ---------------------------------------------------------------------------

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define sensorGempa 3
#define ledHijau 5
#define ledMerah 6

RF24 radio(7,8);
const byte alamat[][6] = {"18150", "51012"};
boolean kondisiSaklar = 0;

void setup() {
  pinMode(ledHijau, OUTPUT);
  pinMode(ledMerah, OUTPUT);

  radio.begin();
  radio.openWritingPipe(alamat[1]);
  radio.openReadingPipe(1, alamat[0]);
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  delay(5);
  radio.startListening();
  while(radio.available()){
    radio.read(&kondisiSaklar, sizeof(kondisiSaklar));
    if (kondisiSaklar == HIGH) {
      delay(5);
      radio.stopListening();
      int trigger = digitalRead(sensorGempa);
      radio.write(&trigger, sizeof(trigger));
      digitalWrite(ledHijau, HIGH);
      digitalWrite(ledMerah, LOW);
    } else {
      digitalWrite(ledMerah, HIGH);
      digitalWrite(ledHijau, LOW);
    }
  }
}
