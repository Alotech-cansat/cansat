#include "DistressCall.hpp"
#include "Display.hpp"
#include "Encoder.hpp"
#include "button.hpp"
#include "radio.hpp"
#include <string>
#include <iostream>

String distress_call_message;

bool click = false;
bool NextUiLevel = false;
bool prev_button_state = false;

DistressCall mycall;
vector<LangOption> langs;
vector<BodyPartOption> BodyParts;
vector<InjuryOption> Injuries;

bool IsChoosingLanguage = true;
bool IsChoosingBodyPart = false;
bool IsChoosingInjury = false;
bool IsSuccess = false;

using namespace std;

void setup_UI(){
  

  digitalWrite(SDCARD_CS,HIGH);
  digitalWrite(TFT_CS,HIGH);
  delay(10);


  setup_encoder();
  Serial.println("Initialized encoder");

  setup_click();
  
  

  Serial.println("Read language file");
  tft.begin();
  intialize_screen();
  fill_screen();
  Serial.println("Initialized screen");
  

  langs = mycall.get_langs(SD);
  Serial.println(langs[0].name);

  for(LangOption& i :langs){
    Serial.print(i.name);
    Serial.println(i.file);
    new_option(i.name);
    
  }

  current_id = 0;
  next_option();
  Serial.println(current_id);

  Serial.println("Setup finished");
 
}

void clear_ui(){

  IsChoosingBodyPart = true;
      clear_options();
    
    for (BodyPartOption i :BodyParts){
      
      new_option(i.name);
    }
    next_option();
    delay(500);

}

String loop_ui(){
  
  distress_call_message = "";
  if(click && IsChoosingLanguage){
    Serial.println("choosing lang");
    

    BodyParts = mycall.choose_lang(SD, langs[ current_id % langs.size() ]);
    clear_options();
    
    for (BodyPartOption i :BodyParts){
      
      new_option(i.name);
    }

    next_option();

    IsChoosingLanguage = false;
    IsChoosingBodyPart = true;
    delay(500);
  }
  else if (click && IsChoosingBodyPart){
    Serial.println("choosing body part");
    

    Injuries = mycall.choose_body_part(SD, BodyParts[ current_id % BodyParts.size() ]);
    clear_options();
    for (InjuryOption i :Injuries){
      
      new_option(i.name);
    }

    previous_option();

    IsChoosingBodyPart = false;
    IsChoosingInjury = true;
    delay(500);
  }else if(click && IsChoosingInjury){
    Serial.println("sending");
    fill_screen();
    mycall.choose_injury( Injuries[ current_id % Injuries.size() ]);

    IsChoosingInjury = false;

    //TODO: kari napisz funkcje
    Location loc = get_gps();

    mycall.code = mycall.get_code();//Send(mycall.get_code())

    if(mycall.secret_key == ""){
      distress_call_message = "D " + String(loc.latitude) + " " + String(loc.longitude)  + " " + String(mycall.code);
    }else{
      distress_call_message = "U " + String(loc.latitude) + " " + String(loc.longitude)  + " " + String(mycall.code) + " " + String(mycall.secret_key);
    }
    succes_message();
    delay(500);

    IsSuccess = true;
   
  }else if(click && IsSuccess){
        clear_ui();
        IsSuccess = false;
        IsChoosingBodyPart = true;
  }

  mycall.secret_key = received_secret_key;

  click = update_button_click(); 

  return distress_call_message;
}