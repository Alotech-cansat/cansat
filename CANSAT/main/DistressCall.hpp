#include <ArduinoJson.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <SPI.h>
#include <SD.h>
#include "temporarystorage.hpp"

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


class DistressCall{
  public:
    DistressCall(){
    

    }
    
    vector<int> get_distress_calls(){
       return this -> distress_calls;
    }



    vector<LangOption> get_langs(){
      vector<LangOption> result;
      
      //File lang_file = SD.open(languages_filename);

      StaticJsonDocument<2048> doc;

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
      

      this->language  = file.name;
      this->json_file = file.file;
      
      current_level++; 

      return get_body_parts(file.file);
     }


  vector<BodyPartOption> get_body_parts(String filename){
    //File lang_file = SD.open(filename);
    vector<BodyPartOption> result;
  
    StaticJsonDocument<2048> doc;

    //if(!lang_file){
    //  Serial.println("language file not found");
    //  return result;
    //}

    DeserializationError error = deserializeJson(doc, pl); // For now always open pl file
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
