#include <ArduinoJson.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <SD.h>

//#include "/lang.txt"

const char *languages_filename = "/lang.txt";

File lang_file = SD.open(languages_filename);

using namespace std;


struct MenuOption{
  int id;
  string name;
};

struct LangOption{
  string file;
  string name;
};

class DistressCall{
  public:
    DistressCall(){}
    
    vector<int> get_distress_calls(){
       return this -> distress_calls;
    }

    vector<MenuOption> get_choices(){
      
    }

    vector<LangOption> get_langs(){
      vector<LangOption> result;
  
      StaticJsonDocument<2048> doc;

      if (!lang_file){
          Serial.println(F("File not found"));
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
    
    void choose(){
      //TODO:
      current_level++; 
     }

    
  private:
    vector<int> distress_calls;
    string language;
    string json_file;

    int body_part;
    int injury;
    int pain_level;

    int current_level = 0;
};
