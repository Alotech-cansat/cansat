
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

#define MOSI 21
#define SCK 34
#define MISO 1

String received_secret_key;
SPIClass LoRaSPI(HSPI);
int counter = 0;

void LoRa_setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module

  LoRa.setTxPower(TX_POWER);
  LoRa.setSyncWord(SYNC_WORD);
  LoRa.setCodingRate4(CODING_RATE);
  LoRa.setSpreadingFactor(SPREADING_FACTOR);
  LoRa.setSignalBandwidth(BANDWITH);



  Serial.println(SCK);

  LoRa.enableCrc();
  pinMode(ss, OUTPUT);
 // pinMode(dio0, INPUT); // added
  LoRa.setPins(ss, rst, dio0);

  LoRaSPI.begin(SCK, MISO, MOSI, ss);

  LoRa.setSPI(LoRaSPI);

  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void send_message(String msg) {
  Serial.print("Sending packet: ");
  Serial.println(msg);

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();


}