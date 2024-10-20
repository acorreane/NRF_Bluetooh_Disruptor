#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio1(9, 10, 1000000); //CE, CS, CLOCK (higher clocks require SPI bus shielding by RF interference)
#define RFPOWER RF24_PA_MAX  // using NRF+PA (reduce power on use it with signal boosters)


void setup() {
  pinMode(20, OUTPUT); // led ok (mcu running standalone without xtal on MiniCore at 8MHz)
  pinMode(21, OUTPUT); // led tx
  Serial.begin(115200);
  IOsetup();
  RFsetup();
}

void IOsetup() {
  delay(500); Serial.println("[  SYS  ] init");
  digitalWrite(20, HIGH);
}


void RFsetup() {
  delay(500); Serial.println("[ RADIO ] init");
  if (radio1.begin()) { 
    radio1.stopListening();
    radio1.setDataRate(RF24_2MBPS);
    radio1.setAutoAck(false);
    radio1.startConstCarrier(RFPOWER, 45);
  delay(200); Serial.println("[ RADIO ] ok");
  Serial.end();
  digitalWrite(21, HIGH);
    } 
  else {
    Serial.println("[ RADIO ] fail");
  }
}

void loop() {
  //radio1.setChannel(random(0,80)); //run FHSS carrier from 0 to 80

  for (uint8_t i=1; i<40; i++){
  radio1.setChannel(i*2); //overlap channels to best performance (nrf uses 2MHz bandwidth 80/2 = 40 channels ovelap)
}
