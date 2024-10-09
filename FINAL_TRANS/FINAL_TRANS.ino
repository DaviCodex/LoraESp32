#define sensor 15   //Sensor de humedad de suelo 
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
int humidity;
//Ejercicio Laboratorio modulo RF24LO1
//Codigo de transmision
//Se envia un caja de texto

RF24 radio(4, 5); // CE, CSN
//long contador=0;
String weight;

void setup() 
{
  pinMode(sensor, INPUT);
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate (RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(0x1234567890LL);
}

void loop() 
{
  humidity = map(analogRead(sensor), 4092, 0, 0, 100);
  String texto = "D: " + String(humidity);
  radio.write(&texto, sizeof(texto));
  Serial.println("Enviando: "+ texto);
  delay(1000);
  //contador=contador+1;
}