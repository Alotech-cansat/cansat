
#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 18
#define rst 11
#define dio0 10

#define TX_POWER 20
#define SYNC_WORD 0x39
#define CODING_RATE 8
#define SPREADING_FACTOR 7
#define BANDWITH 125E3

#define MOSI 17
#define SCK 34
#define MISO 1

SPIClass LoRaSPI(FSPI);

void LoRa_setup(){
  LoRa.setTxPower(TX_POWER);
  LoRa.setSyncWord(SYNC_WORD);
  LoRa.setCodingRate4(CODING_RATE);
  LoRa.setSpreadingFactor(SPREADING_FACTOR);
  LoRa.setSignalBandwidth(BANDWITH);



  Serial.println(SCK);

  LoRa.enableCrc();
  pinMode(ss, OUTPUT);
  pinMode(dio0, INPUT); // added
  LoRa.setPins(ss, rst, dio0);

  LoRaSPI.begin(SCK, MISO, MOSI, ss);

  LoRa.setSPI(LoRaSPI);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  LoRa.onReceive(onReceive);
  LoRa.receive();
    pinMode(dio0, INPUT);

  Serial.println("intialized");
}

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa_setup();
}

void onReceive(int packetSize){
  //Serial.println("received using interupt");
  
  //Serial.println(packetSize);
  if (packetSize) {
    // received a packet
    

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }
  }
}

void send_message(String msg){
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
}

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  //Serial.println(packetSize);
  if (packetSize) {
    // received a packet
    

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
      
    }
    delay(10);

  }

  send_message(Serial.readString());


}