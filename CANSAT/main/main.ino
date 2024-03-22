#include "UI.hpp"
//#include "Sensors.hpp"


void setup(){
  delay(4000);

  initializeSD();
  Serial.begin (115200);

  int x = write_to_file( "data.txt", "twoja stara");
  Serial.println(x);

  setup_UI();
  setupBMEADXL();
  
  
}



void loop(){
  
  loop_ui();
  loop_sensors();

}
