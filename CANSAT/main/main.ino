#include "DistressCall.hpp"
#include "Display.hpp"
#include "Encoder.hpp"

//vars used only for testing
bool click = false;
int i = 0;

DistressCall mycall;
vector<LangOption> langs;

bool IsChoosingLanguage = true;



void setup(){

  Serial.begin (9600);



  setup_encoder();
  
  langs = mycall.get_langs();

  intialize_screen();
  fill_screen();

  for(LangOption& i :langs){
    new_option(i.name);
  }
  previous_option();
}



void loop(){

  

  if(click && IsChoosingLanguage){
    clear_options();

    vector<BodyPartOption> res = mycall.choose_lang(langs[ current_id % langs.size() ]);

    for (BodyPartOption i :res){
      new_option(i.name);

      
    }

    IsChoosingLanguage = false;
  }


  delay(1000);
  if (i > 10){click = true;}
  i++;
  
}
