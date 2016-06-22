#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22


typedef struct dhtPacket dhtPacket;
struct dhtPacket {
  short id = 0;
  uint32_t millis;
  float temperature;
  float humidity;
};


int dhtInit()
{
  DHT dht(DHTPIN, DHTTYPE);

  dht.begin();
}


int readTemp(dhtPacket *newPacket)
{
  DHT dht(DHTPIN, DHTTYPE);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
/*
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
*/

  newPacket->millis=millis();
  newPacket->temperature = t;
  newPacket->humidity = h;

  return 0;
}