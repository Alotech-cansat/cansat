#include "UI.hpp"


int last_sensor_update;
String sensor_msg;

void setup(){

  Serial.begin(115200);
  while (!Serial);

  //setup LoRa transceiver module
  
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa_setup();

initializeSD();



setup_gps();
  
setup_UI();
setupBMEADXL();

  
 clear_file("data.txt");
  

  last_sensor_update = millis();
  
  
}



void loop(){
  
  String res = loop_ui();
if (res != ""){
  send_message(res);
}
  
  
  if (millis() - last_sensor_update > 500){
    
   sensor_msg = loop_sensors();
   // send_message(sensor_msg);
    last_sensor_update = millis();
  }

  

}
