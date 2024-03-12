#define encoderPinA  2  
#define encoderPinB  4 

void doEncoder() {
  if (digitalRead(encoderPinB)==HIGH) {
    next_option();
  } else {
    previous_option();
  }
}

void setup_encoder(){
  pinMode(encoderPinA, INPUT_PULLUP); 
  digitalWrite(encoderPinA, HIGH); 
  pinMode(encoderPinB, INPUT_PULLUP); 
  digitalWrite(encoderPinB, HIGH);
  attachInterrupt(2, doEncoder, RISING);
}
