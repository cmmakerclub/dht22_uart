#include "DHT.h"
#include <SoftwareSerial.h>

SoftwareSerial softBLE(5, 4); // RX, TX

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE, 3);

#define TRIGGER 9

double h = 0, t = 0;

unsigned int count = 0;
char buf[60];

char floatBuf1[6];
char floatBuf2[6];
  
void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
  delay(70);

  Serial.begin(9600); 
  softBLE.begin(9600);

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
    
  if (millis() % 1000 == 0) {
    dtostrf(h, 2, 2, floatBuf1);
    dtostrf(t, 2, 2, floatBuf2);
    if (digitalRead(TRIGGER) == LOW) {
      snprintf(buf, sizeof(buf), "SN:%s,HUMIDI:%s,TEMPER:%s", "001", floatBuf1, floatBuf2);
    }
    else {
      strcpy(buf, floatBuf2);
    }
    
    Serial.println(buf);
    softBLE.println(buf);
    
    // reset
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

