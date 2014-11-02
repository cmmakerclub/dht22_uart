#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

float h = 0, t = 0;

unsigned int count = 0;

void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  Serial.begin(9600); 

  dht.begin();

  delay(1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h += dht.readHumidity();
  // Read temperature as Celsius
  t += dht.readTemperature();  
  count++;
}

void loop() {

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      h += dht.readHumidity();
      // Read temperature as Celsius
      t += dht.readTemperature();      
      count++;    
      return;
    }


  if (millis() % 2000 == 0) {
    Serial.print("SN:001,");
    Serial.print("HUMIDI:"); 
    Serial.print(h);
    Serial.print(",");   
    Serial.print("TEMPER:"); 
    Serial.println(t);
    
    h = 0;
    t = 0;
    count = 0;
  }
  else {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    h = dht.readHumidity();
    // Read temperature as Celsius
    t = dht.readTemperature();
    count++;    
  }
}

