#define encoderPinA  2  
#define encoderPinB  3

void doEncoder() {
  if (digitalRead(encoderPinA)==HIGH) {
    next_option();
  } else {
    previous_option();
  }
}

void setup_encoder(){
  pinMode(encoderPinA, INPUT_PULLUP); 

  pinMode(encoderPinB, INPUT_PULLUP); 

  attachInterrupt(encoderPinA, doEncoder, RISING);
  //attachInterrupt(encoderPinB, doEncoderB, RISING);
}