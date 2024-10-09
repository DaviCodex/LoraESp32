
#include "EBYTE.h"
int humidity;
#define sensor 15   //Sensor de humedad de suelo 
#define PIN_RX 16   // Serial2 RX (connect this to the EBYTE Tx pin)
#define PIN_TX 17   // Serial2 TX pin (connect this to the EBYTE Rx pin)

#define PIN_M0 4    // D4 on the board (possibly pin 24)
#define PIN_M1 22   // D2 on the board (possibly called pin 22)
#define PIN_AX 21   // D15 on the board (possibly called pin 21)


struct DATA {
  unsigned long Count;
  int Bits;
  int humidity; 
  float Volts;
  float Amps;

};

DATA MyData;

// create the transceiver object, passing in the serial and pins
EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AX);

void setup() {

  pinMode(sensor, INPUT);

  Serial.begin(9600);

  Serial2.begin(9600);

  Serial.println("Starting Reader");

  Serial.setDebugOutput(true);

  delay(1000);

  Serial.println(Transceiver.init());

  Transceiver.PrintParameters();

}

void loop() {
  humidity = map(analogRead(sensor), 4092, 0, 0, 100);
  String texto = "D: " + String(humidity);
  Transceiver.SendStruct(&texto, sizeof(texto));

  Serial.print("Sending: "); Serial.println(texto);
  delay(2000);

}
