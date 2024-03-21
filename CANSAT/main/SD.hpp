#include <SPI.h>
#include <FS.h>
#include "SD.h"
#include <iostream>

#define SDCARD_CS 8
#define SDCARD_MOSI 15
#define SDCARD_SCLK 14
#define SDCARD_MISO 9

const String data_filename = "/data.txt";

SPIClass SDSPI(FSPI);

void initializeSD(){

     pinMode(SDCARD_MISO, INPUT_PULLUP);
     SDSPI.begin(SDCARD_SCLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);
     
    if (!SD.begin(SDCARD_CS, SDSPI)) {
       Serial.println("setup SD card FAILED");
          
     }else{
      Serial.println("setup SD card succesfull");
      
    }
  
}  


File get_file(fs::FS &fs, String filename){

    File file = fs.open( filename);

    if(!file){
      Serial.println("file not found");
      
    }

    return file;
}
/*
void write_to_file(fs::Fs &fs, String filename, String content){

}*/

