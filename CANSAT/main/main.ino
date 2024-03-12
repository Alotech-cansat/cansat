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
  pinMode(SDCARD_MISO, INPUT_PULLUP);
  SDSPI.begin(SDCARD_SCLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);


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

   uint32_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.print("setupSDCard PASS. SIZE = ");
  Serial.print(cardSize);
  Serial.println(" MB");

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
