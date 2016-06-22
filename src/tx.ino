#include <ArdusatSDK.h>
#include "sdCard.h"
#include "thermo.h"
#include "DHT.h"
#include "vcc.h"
#include <VirtualWire.h>



// Sparkfun SD shield: pin 8
void setup()
{
  dhtInit();

    Serial.begin(9600);	  // Debugging only
    Serial.println("setup");
  //pinMode(12,OUTPUT);
    // Initialise the IO and ISR
    //vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_set_tx_pin(12);

}


void loop()
{
  dhtPacket newPacket;
  vccPacket newVcc;

  readTemp(&newPacket);
  readVcc(&newVcc);

  Serial.println(newPacket.millis);
  Serial.println(newPacket.temperature);
  Serial.println(newPacket.humidity);
  Serial.println(sizeof(newPacket));
  Serial.println();
  Serial.println(newVcc.millivolts);
  Serial.println(sizeof(newVcc));





    char msg[40];
    vw_send((uint8_t *)&newPacket, sizeof(newPacket));
    vw_wait_tx(); // Wait until the whole message is gone

    delay(200);

    vw_send((uint8_t *)&newVcc, sizeof(newVcc));
    vw_wait_tx(); // Wait until the whole message is gone
}
