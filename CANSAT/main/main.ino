#include "DistressCall.hpp"
#include "Display.hpp"
#include "Encoder.hpp"

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

//vars used only for testing
bool click = false;
int i = 0;

DistressCall mycall;
vector<LangOption> langs;
vector<BodyPartOption> BodyParts;
vector<InjuryOption> Injuries;

bool IsChoosingLanguage = true;
bool IsChoosingBodyPart = false;



void setup(){
  digitalWrite(5, HIGH); // TFT screen chip select
  digitalWrite(SDCARD_CS , HIGH); // SD card chips select, must use GPIO 5 (ESP32 SS)
  delay(5000);
  
  Serial.begin (115200);
  
  initializeSD();
  Serial.println("initiliazed Sd reader");

  setup_encoder();
  Serial.println("Initialized encoder");
  
  langs = mycall.get_langs(SD);

  Serial.println("Read language file");
  
  intialize_screen();
  fill_screen();
  Serial.println("Initialized screen");

  for(LangOption& i :langs){
    new_option(i.name);
    
  }
  previous_option();

  Serial.println("Setup finished");
}



void loop(){

File file = SD.open("/lang.json", FILE_READ); //does not work

 

 if(!file){
 Serial.println("/lang.json file not found");
 Serial.println(file);

}else{
 Serial.println(file);
}
 file.close();

  if(click && IsChoosingLanguage){
    Serial.println("choosing lang");
    clear_options();
    
    initializeSD();

    BodyParts = mycall.choose_lang(SD, langs[ current_id % langs.size() ]);
    //tft.getSPIinstance().begin();
    for (BodyPartOption i :BodyParts){
      
      new_option(i.name);
    }

    previous_option();

    IsChoosingLanguage = false;
    IsChoosingBodyPart = true;
  }
  else if (click && IsChoosingBodyPart){
    Serial.println("choosing body part");
    clear_options();

    Injuries = mycall.choose_body_part(SD, BodyParts[ current_id % langs.size() ]);

    for (InjuryOption i :Injuries){
      
      new_option(i.name);
    }

    previous_option();

    IsChoosingBodyPart = false;
  }


  delay(1000);
  if (i == 10){click = true;}
  else if(i == 20){click = true;}
  else{
    click = false;
  }
  i++;
  Serial.println(i);
  
}
