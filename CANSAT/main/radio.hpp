
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

void onReceive(int packetsize){
  Serial.println("aloha");
}

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
  

    pinMode(dio0, INPUT);

  Serial.println("intialized");
}



void send_message(String msg){
  Serial.println(msg);
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket(true);
  LoRa.onReceive(onReceive);
  LoRa.receive();
}


