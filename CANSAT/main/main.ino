#include "UI.hpp"

int last_sensor_update;

void setup(){


  delay(4000);

  Serial.begin (115200);

  setup_gps();
  initializeSD();
  setup_UI();
  setupBMEADXL();

  clear_file("data.txt");
  

  last_sensor_update = millis();
  
  
}



void loop(){
  
  loop_ui();
  
  
  if (millis() - last_sensor_update > 500){
    
    loop_sensors();
    last_sensor_update = millis();
  }

  

}
