// This #include statement was automatically added by the Particle IDE.
#include <JsonParserGeneratorRK.h>

// This #include statement was automatically added by the Particle IDE.
#include <Grove_Temperature_And_Humidity_Sensor.h>

// Adding delay of 30 seconds between reading amd defining input pin for dht11
#define DELAY 30000 
#define PIN D6

DHT dht(PIN);

// Declaring double variables for gathering input from dht11
double temp;
double hum;

void createEventPayload(double temperature, double humidity) {
    JsonWriterStatic<256> jw;
    {
        JsonWriterAutoObject obj(&jw);
        jw.insertKeyValue("temp", temperature);
        jw.insertKeyValue("hum", humidity);
    }
    Particle.publish("dht11", jw.getBuffer(), PRIVATE);
}

void setup() {
    dht.begin();
    pinMode(PIN, INPUT);
}

void loop() {
    temp = dht.getTempCelcius();
    hum = dht.getHumidity();
    createEventPayload(temp, hum);
    delay(DELAY);
}