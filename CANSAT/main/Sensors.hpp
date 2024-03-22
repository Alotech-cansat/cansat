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

#define BME_SCK 14 //SCL
#define BME_MISO 9 //SDO
#define BME_MOSI 15 //SDA
#define BME_CS 39

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;//(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const String data_filename = "data.txt";

unsigned long delayTime;
int count_time;

String showTimeOfMeasurements(int x)
{
  int seconds = x % 60;
  int minutes = x / 60;
  String output = String(minutes) + ":" + String(seconds);
  return output;
}


std::vector<String> printValuesBMEADXL()
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  //Serial.println(showTimeOfMeasurements(count));
  count_time = count_time + 1;
  /* Display the results (acceleration is measured in m/s^2) */
  int acx, acy, acz, temp, pres, apxalt, hum;
  acx = event.acceleration.x;
  acy = event.acceleration.y;
  acz = event.acceleration.z;
  temp = bme.readTemperature();
  pres = bme.readPressure();
  apxalt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  hum = bme.readHumidity();
  /*Serial.print("X: "); Serial.print(acx); Serial.print("  ");
  Serial.print("Y: "); Serial.print(acy); Serial.print("  ");
  Serial.print("Z: "); Serial.print(acz); Serial.print("  ");Serial.println("m/s^2 ");
  
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(pres / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(apxalt);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(hum);
  Serial.println(" %");*/

  Serial.println();
  //String zapis[8] = {showTimeOfMeasurements(count), String(acx), String(acy), String(acz), String(temp), String(pres), String(apxalt), String(hum)};
  std::vector<String> zapis = {showTimeOfMeasurements(count_time), String(acx), String(acy), String(acz), String(temp), String(pres), String(apxalt), String(hum)};
  
  
  //String* y = zapis;
  delay(delayTime);
  return zapis;
  
}

void setupBMEADXL()
{
    count_time = 0;
    unsigned status;
    
    // default settings
    // Wire.begin(33, 35);
    Wire1.begin(39, 40);
    status = bme.begin(0x76, &Wire1);  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire1);
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


    Wire.begin(33, 35);
    Serial.begin(9600);

    if(!accel.begin())
    {

      Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
      //while(1);
    }
    Serial.println("ADXL345 initialized");

    accel.setRange(ADXL345_RANGE_16_G);


    //displaySensorDetails();

    //displayDataRate();
    //displayRange();
    Serial.println("");
}


void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  delay(500);
}


void loop_sensors() {
  write_to_file(data_filename, "halooo");

  std::vector<String> data = printValuesBMEADXL();

  Serial.print("Time: "); Serial.print(data[0]); Serial.print("  ");
  Serial.print("\nX: "); Serial.print(data[1]); Serial.print("  ");
  Serial.print("Y: "); Serial.print(data[2]); Serial.print("  ");
  Serial.print("Z: "); Serial.print(data[3]); Serial.print("  ");Serial.println("m/s^2 ");
  
  Serial.print("Temperature = ");
  Serial.print(data[4]);
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(data[5]);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(data[6]);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(data[7]);
  Serial.println(" %");
}

