#include "DistressCall.hpp"
#include "Display.hpp"

 
//vars used only for testing
bool click = false;
int i = 0;


DistressCall mycall;
vector<LangOption> langs;

bool IsChoosingLanguage = true;


void setup(){
  Serial.begin(9600);

  intialize_screen();
  fill_screen();
  langs = mycall.get_langs();

  for(LangOption& i :langs){
    new_option(i.name);
  }
}

void loop(){

   
  previous_option();
  Serial.println(click);
  if(click && IsChoosingLanguage){
    clear_options();

    vector<BodyPartOption> res = mycall.choose_lang(langs[ current_id % langs.size() ]);

    for (BodyPartOption i :res){
      new_option(i.name);

      
    }

    IsChoosingLanguage = false;
    Serial.println("da wat");
  }

  
  delay(3000);
  Serial.println(i);
  if (i > 10){click = true;}
  i++;
  
}
