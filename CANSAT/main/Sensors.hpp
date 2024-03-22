/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <iostream>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ADXL345_U.h>
#include <string>
#include <Arduino.h>
#include <vector>
#include "SDCARD.hpp"
#include "GPS.hpp"


using namespace std; 

#define BME_SDA 39 //SDA
#define BME_SCL 40 //SCL

#define ADXL_SDA 33 //SDA
#define ADXL_SCL 35 //SCL

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const String data_filename = "data.txt";

unsigned long delayTime;
int count_time;

struct Measurment{
  int time;
  
  float acx;
  float acy;
  float acz;
  
  int temp;
  int pressure;
  int humidity;
  
  float altitude;
  float longitude;
  float latitude;

};



String showTimeOfMeasurements(int x)
{
  int seconds = x % 1000;
  int minutes = x / 1000;
  String output = String(minutes) + ":" + String(seconds);
  return output;
}


Measurment printValuesBMEADXL()
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  //Serial.println(showTimeOfMeasurements(count));
  count_time = millis();
  /* Display the results (acceleration is measured in m/s^2) */

  Measurment measurment;

  measurment.time = count_time;
  measurment.acx = event.acceleration.x;
  measurment.acy = event.acceleration.y;
  measurment.acz = event.acceleration.z;
  measurment.temp = bme.readTemperature();
  measurment.pressure = bme.readPressure();
  measurment.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  measurment.humidity = bme.readHumidity();

  Location loc = get_gps();

  measurment.latitude = loc.latitude;
  measurment.longitude = loc.longitude;
  measurment.altitude = loc.altitude;

  
  write_to_file(data_filename, "ACCELERATION (x,y,z) (m/s^2): (" + String(measurment.acx) + "," + String(measurment.acy) + "," + String(measurment.acz) + ") \t TEMPERATURE (C): " + String(measurment.temp) + " \t ALTITUDE: " + String(measurment.altitude) + " \t PRESSURE: " + String(measurment.pressure) + " \t HUMIDITY: " + String(measurment.humidity) + "\t LOCATION (longitude, latitude): (" + measurment.longitude + "," + measurment.latitude + ")");


  return measurment;
  
}

void setupBMEADXL()
{
    count_time = 0;
    unsigned status;
    
    Wire1.begin(BME_SDA, BME_SCL);
    status = bme.begin(0x76, &Wire1);  

    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }

    Serial.println("BME280 initialized");
    
   
    delayTime = 1000;


    Wire.begin(ADXL_SDA, ADXL_SCL);


    if(!accel.begin())
    {

      Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
      
    }
    Serial.println("ADXL345 initialized");

    accel.setRange(ADXL345_RANGE_16_G);

    Serial.println("");
}


void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  delay(500);
}


void loop_sensors() {
  

  Measurment data = printValuesBMEADXL();




}
