/*
 * LoRa E32-TTL-100
 * Send fixed broadcast transmission message to a specified channel.
 * https://www.mischianti.org/2019/11/10/lora-e32-device-for-arduino-esp32-or-esp8266-fixed-transmission-part-4/
 *
 * E32-TTL-100----- Arduino UNO or esp8266
 * M0         ----- 3.3v (To config) GND (To send) 7 (To dinamically manage)
 * M1         ----- 3.3v (To config) GND (To send) 6 (To dinamically manage)
 * TX         ----- RX PIN 2 (PullUP)
 * RX         ----- TX PIN 3 (PullUP & Voltage divider)
 * AUX        ----- Not connected (5 if you connect)
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E32.h"


//-----------Pines

#define Pin_RX 16  
#define Pin_TX 17

#define Pin_M0 4 
#define Pin_M1 22 
#define Pin_AX 15 

// tx, rx , aux, M0, M1
LoRa_E32 e32ttl(&Serial2, Pin_AX, Pin_M0, Pin_M1);

void setup()
{
	Serial.begin(9600);
	while (!Serial) {
	    ; // wait for serial port to connect. Needed for native USB
    }
	delay(100);

	e32ttl.begin();
	// After set configuration comment set M0 and M1 to low
	// and reboot if you directly set HIGH M0 and M1 to program
	ResponseStructContainer c;
	c = e32ttl.getConfiguration();
	Configuration configuration = *(Configuration*) c.data;
	configuration.ADDL = 0x00;
	configuration.ADDH = 0x01;
	configuration.CHAN = 0x02;
	configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
	e32ttl.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
	//printParameters(configuration);
	c.close();
	// ---------------------------
}

// The loop function is called in an endless loop
void loop()
{
	delay(2000);

	Serial.println("Send message to 00 03 04");
	ResponseStatus rs = e32ttl.sendFixedMessage(0, 3, 0x04, "Message to 00 03 04 device");
	Serial.println(rs.getResponseDescription());
}






