#include "DistressCall.hpp"
#include "Display.hpp"

 


DistressCall mycall;

void setup(){
  Serial.begin(115200);

  intialize_screen();
  fill_screen(WHITE);

  draw_option("aaaaaaaaaaaaaaaa");
  draw_option("aaaaaaaaaaaaaaaa");
  draw_option("aaaaaaaaaaaaaaaa");
  draw_option("aaaaaaaaaaaaaaaa");
  draw_option("aaaaaaaaaaaaaaaa");

  choose(2);

}

void loop(){
  Serial.println(x);
  //mycall.get_langs();
  //next();
  unchoose((current_id) % display_option.size());
  choose((current_id + 1) % display_option.size());
  current_id++;
  delay(3000);

}
