#include <ArduinoJson.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Option{
  int id;
  string name;
};

class DistressCall{
  public:
    vector<int> get_distress_calls(){
       return this -> distress_calls;
    }

    vector<Option> get_choices(){
      //TODO:
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
