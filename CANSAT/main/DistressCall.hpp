#include <ArduinoJson.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <SPI.h>
#include <SD.h>
#include "temporarystorage.hpp"

#define SDCARD_CS 34
#define SDCARD_MOSI 35
#define SDCARD_SCLK 36
#define SDCARD_MISO 37
SPIClass SDSPI(FSPI);

//Commented code is supposed to be uncommented when we get sd card and won't use temporarystorage.hpp

const char *languages_filename = "/lang.json";

using namespace std;


struct BodyPartOption{
  int id;
  String name;
  vector<int> possible_injuries;

};

struct LangOption{
  String file;
  String name;
  
};

struct InjuryOption{
  String name;
  int id;
  bool ask_about_pain;
};

void initializeSD(){

     pinMode(SDCARD_MISO, INPUT_PULLUP);
     SDSPI.begin(SDCARD_SCLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);
     while(1){
      if (!SD.begin(SDCARD_CS, SDSPI)) {
       Serial.println("setup SD card FAILED");
          
     }else{
      Serial.println("setup SD card succesfull");
      break;
    }
  }
}  




class DistressCall{
  public:
    DistressCall(){}


    
    vector<int> get_distress_calls(){
       return this -> distress_calls;
    }



    vector<LangOption> get_langs(){
      //initializeSD();
      vector<LangOption> result;
      
      //File lang_file = SD.open( languages_filename);

      StaticJsonDocument<1024> doc;

      //if(!lang_file){
      //  Serial.println("language file not found");
      //  return result;
      //}
      
      DeserializationError error = deserializeJson(doc, temp_lang_file);
      if (error) {
          Serial.println(F("Failed to read file, using default configuration" + *error.c_str()));
          return result;
      }
  
      if (!doc.is<JsonArray>()) {
          Serial.println(F("File does not contain an array"));
          return result;
      }
  
      JsonArray array = doc.as<JsonArray>();
      for (JsonObject obj : array) {
          for (JsonPair pair : obj) {
              LangOption new_lang;
              new_lang.name = pair.key().c_str(); // Get the key (language)
              new_lang.file = pair.value().as<const char*>();;
              result.push_back(new_lang);
          }
      }
  
      //lang_file.close();


      return result;
      
    }


   
    vector<BodyPartOption> choose_lang(LangOption file){
      Serial.println("halo");

      this->language  = file.name;
      this->json_file = file.file;
      
      current_level++; 

      return get_body_parts(file.file);
     }


  vector<BodyPartOption> get_body_parts(String filename){
    //initializeSD();
       
    vector<BodyPartOption> result;
    
    //File file = SD.open("/" +  filename);

  
    StaticJsonDocument<2048> doc;
   
    //if(!file){
    //  Serial.println("/" + filename + " file not found");
    //  Serial.println(file);
    //  return result;
    //}

    DeserializationError error = deserializeJson(doc, pl); 
    if (error) {
        Serial.println(F("Failed to read file, using default configuration" + *error.c_str()));
        return result;
    }

    JsonArray bodyparts = doc["BodyParts"].as<JsonArray>();

    for (JsonObject bodyPart : bodyparts) {

      int id = bodyPart["id"];
      const char* name = bodyPart["name"];
      vector<int> possible_injuries;
      JsonArray possibleInjuriesJson = bodyPart["PossibleInjuries"].as<JsonArray>();
      for (int injury : possibleInjuriesJson) {
        possible_injuries.push_back(injury);
      } 

      Serial.println(name);
      BodyPartOption new_body_part;

      new_body_part.name = name;
      new_body_part.id   = id;
      new_body_part.possible_injuries = possible_injuries;

      result.push_back(new_body_part);
      
    }

    //file.close();

    return result;
} 

   
    vector<InjuryOption> choose_body_part(BodyPartOption body_part){
      Serial.println("halo");

      this->body_part  = body_part.id;

    
      current_level++; 

      return get_injuries(this->json_file, body_part.possible_injuries);
     }

    
  vector<InjuryOption> get_injuries(String filename, vector<int> possible_injuries){
    initializeSD();
       
    vector<InjuryOption> result;
    
    //File file = SD.open("/" +  filename);

  
    StaticJsonDocument<2048> doc;
   
    //if(!file){
    //  Serial.println("/" + filename + " file not found");
    //  Serial.println(file);
    //  return result;
    //}

    DeserializationError error = deserializeJson(doc, pl); 
    if (error) {
        Serial.println(F("Failed to read file, using default configuration" + *error.c_str()));
        return result;
    }

    JsonArray injuries = doc["Injuries"].as<JsonArray>();

    for (JsonObject injury : injuries) {

      int id = injury["id"];
      const char* name = injury["name"];
      bool ask_about_pain = injury["AskAboutPainLevel"];


      InjuryOption new_injury;
      Serial.println(name);

      new_injury.name = name;
      new_injury.id   = id;
      new_injury.ask_about_pain = ask_about_pain;
      if(std::find(possible_injuries.begin(), possible_injuries.end(), new_injury.id) != possible_injuries.end()){
        result.push_back(new_injury);
      }
      
    }
    Serial.println("halo");

    //file.close();

    return result;
} 
    
    

    
  private:
    vector<int> distress_calls;
    String language;
    String json_file;

    int body_part;
    int injury;
    int pain_level;

    int current_level = 0;
};
