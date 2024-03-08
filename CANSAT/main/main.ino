#include "DistressCall.hpp"
#include "Display.hpp"

 


DistressCall mycall;

void setup(){
  Serial.begin(115200);

  intialize_screen();
  fill_screen(WHITE);

  new_option("aaaaaaaaaaaaaaaa");
  new_option("bbbbbbbbbbbbbbbb");
  new_option("cccccccccccccccc");
  new_option("dddddddddddddddd");
  new_option("eeeeeeeeeeeeeeee");

  choose(2);

}

void loop(){

  //mycall.get_langs();
  back();
  //draw_option(0, 2);
  
  //unchoose((current_id) % display_option.size());
  //draw_option_at((current_id + 1) % display_option.size());
  //current_id++;
  delay(3000);

}
