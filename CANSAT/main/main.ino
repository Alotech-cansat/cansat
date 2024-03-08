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



}

void loop(){


  back();

  delay(3000);

}
