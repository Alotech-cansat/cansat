#include "UI.hpp"


void setup(){


  delay(4000);

  Serial.begin (115200);

  initializeSD();
  setup_UI();
  setupBMEADXL();

  clear_file("data.txt");
  


  
  
}



void loop(){
  
  loop_ui();
  loop_sensors();

}
