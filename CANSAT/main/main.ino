#include "DistressCall.hpp"
#include "Display.hpp"
#include "Encoder.hpp"





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
  delay(5000);
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
    Serial.println("choosing lang");
    clear_options();

    BodyParts = mycall.choose_lang(langs[ current_id % langs.size() ]);
  
    for (BodyPartOption i :BodyParts){
      
      new_option(i.name);
    }

    IsChoosingLanguage = false;
    IsChoosingBodyPart = true;
  }
  else if (click && IsChoosingBodyPart){
    Serial.println("choosing body part");
    clear_options();

    Injuries = mycall.choose_body_part(BodyParts[ current_id % langs.size() ]);

    for (InjuryOption i :Injuries){
      
      new_option(i.name);
    }

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
