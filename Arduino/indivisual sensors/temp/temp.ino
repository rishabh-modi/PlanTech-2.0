#include <dht.h>

dht DHT;

#define DHT11_PIN 7

void setup(){
  Serial.begin(9600);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
    Serial.print(DHT.temperature);


  Serial.print("          ");
  
  Serial.print("Humidity = ");
    Serial.print("");

  Serial.print(DHT.humidity);

Serial.println();
  
  delay(2000);
}
