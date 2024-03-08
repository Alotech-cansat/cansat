#include <ArduinoJson.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <SD.h>

#define languages_file "/Data/langs.js"

File file = SD.open(languages_file);

using namespace std;


struct MenuOption{
  int id;
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

    vector<MenuOption> get_langs(){
      
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
