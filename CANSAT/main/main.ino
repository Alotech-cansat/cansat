#include "DistressCall.hpp"
#include "Display.hpp"

 


DistressCall mycall;
vector<LangOption> langs;


void setup(){
  Serial.begin(9600);

  intialize_screen();
  fill_screen();
  langs = mycall.get_langs();

  
  new_option("aaaaaaaaaaaaaaaa");
  new_option("bbbbbbbbbbbbbbbb");
  new_option("cccccccccccccccc");
  new_option("dddddddddddddddd");
  new_option("eeeeeeeeeeeeeeee");





}

void loop(){
  langs = mycall.get_langs();
  Serial.println(langs.size());
  for(LangOption& i : langs){
    const char * str = i.name.c_str();
    string s = str;
    Serial.println("haloo ");
    //Serial.println(i.file);  
  }

  Serial.println("halooooooooooooo");
   
  back();

  delay(3000);

}
