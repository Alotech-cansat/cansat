#include <TinyGPS++.h>
#define GPS_TX_PIN 2
#define GPS_RX_PIN 3

TinyGPSPlus gps;

struct Location{
  float longitude;
  float latitude;
  float altitude;
};

void setup_gps() {

    Serial1.begin(9600, SERIAL_8N1, GPS_TX_PIN, GPS_RX_PIN);

    
    Serial.println("GPS start");
}

Location get_gps() {
    Location loc;
    if (Serial1.available()) {

        char c = Serial1.read();
        if(gps.encode(c)) {

            

            loc.latitude  = gps.location.lat();
            loc.longitude = gps.location.lng();
            loc.altitude  = gps.altitude.meters();

            
        }
    }
    vTaskDelay(1 / portTICK_PERIOD_MS); 
    return loc;
}