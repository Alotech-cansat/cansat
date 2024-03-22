#include <SPI.h>
#include <FS.h>
#include "SD.h"
#include <iostream>

#define SDCARD_CS 8
#define SDCARD_MOSI 15
#define SDCARD_SCLK 14
#define SDCARD_MISO 9


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

void create_file(String filename){

}

File get_file(String filename){

    File file = SD.open( filename);

    if(!file){
      Serial.println("file not found");
      
    }

    return file;
}

int write_to_file(String filename, String content){
  File file = SD.open("/" + filename, FILE_APPEND );

  if(file){
    file.println(content);
    file.close();
    Serial.println("succesfully saved");
    return 1;
  }else{
    Serial.println("error opening file");
    return 0;
  }
}

