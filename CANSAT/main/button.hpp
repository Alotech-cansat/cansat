
#define ButtonPinB 37

bool IsClicked = false;

bool update_button_click(){
  if (digitalRead(ButtonPinB)==LOW) {
    
    return true;
    
    
  }else{
    return false;
  }
}


void setup_click(){

  pinMode(ButtonPinB, INPUT_PULLUP); 
  digitalWrite(ButtonPinB, HIGH);

}
