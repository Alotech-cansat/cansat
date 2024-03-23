#include <ArduinoJson.h>
#include <fstream>
#include <vector>
#include "Sensors.hpp"

const String languages_filename= "/lang.json";

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






class DistressCall{
  public:

    int secret_key = 0;
    int code;
    DistressCall(){}

    int get_code(){
      return this->body_part * 100 + this->injury;
    }
    
    vector<int> get_distress_calls(){
       return this -> distress_calls;
    }



    vector<LangOption> get_langs(fs::FS &fs){
      vector<LangOption> result;
      
      File lang_file = fs.open(languages_filename);

      StaticJsonDocument<1024> doc;

      if(!lang_file){
        Serial.println("language file not found");
        return result;
      }
      
      DeserializationError error = deserializeJson(doc, lang_file);
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
  
      lang_file.close();


      return result;
      
    }


   
    vector<BodyPartOption> choose_lang(fs::FS &fs, LangOption file){


      this->language  = file.name;
      this->json_file = file.file;
      
      current_level++; 

      return get_body_parts(fs, file.file);
     }



  vector<BodyPartOption> get_body_parts(fs::FS &fs, String filename){

       
    vector<BodyPartOption> result;
    
    File file = fs.open("/" +  filename);

  
    StaticJsonDocument<2048> doc;
   
    if(!file){
      Serial.println("/" + filename + " file not found");
      Serial.println(file);
      return result;
    }

    DeserializationError error = deserializeJson(doc, file); 
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

      BodyPartOption new_body_part;

      new_body_part.name = name;
      new_body_part.id   = id;
      new_body_part.possible_injuries = possible_injuries;

      result.push_back(new_body_part);
      
    }

    file.close();

    return result;
} 

   
    vector<InjuryOption> choose_body_part(fs::FS &fs,BodyPartOption body_part){

      this->body_part  = body_part.id;

    
      current_level++; 

      return get_injuries(fs, this->json_file, body_part.possible_injuries);
     }

    
  vector<InjuryOption> get_injuries(fs::FS &fs,String filename, vector<int> possible_injuries){
    //initializeSD();
       
    vector<InjuryOption> result;
    
    File file = SD.open("/" +  filename);

  
    StaticJsonDocument<2048> doc;
   
    if(!file){
      Serial.println("/" + filename + " file not found");
      Serial.println(file);
      return result;
    }

    DeserializationError error = deserializeJson(doc, file); 
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


      new_injury.name = name;
      new_injury.id   = id;
      new_injury.ask_about_pain = ask_about_pain;
      if(std::find(possible_injuries.begin(), possible_injuries.end(), new_injury.id) != possible_injuries.end()){
        result.push_back(new_injury);
      }
      
    }


    file.close();

    return result;
} 
    void choose_injury(InjuryOption injury){
      this->injury = injury.id;
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
