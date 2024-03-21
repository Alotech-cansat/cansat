#include "UI.hpp"

void setup(){
  Serial.begin (115200);
  setup_UI();
}



void loop(){
  loop_ui();
  //encoder_loop();
}
