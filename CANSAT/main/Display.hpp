#include <TFT_eSPI.h> 
#include <stdio.h>

#define ROWSIZE 50

#define FONTSIZE 2

#define PRIMARY_COLOR 0x2104
#define SECONDARY_COLOR 0xef7e
#define HIGHLIGHT_COLOR 0x544f


using namespace std;

struct DisplayOption{
  int id;
  String name;
  
};

int x = 0;
int current_id = 0;

std::vector<DisplayOption> display_option;

TFT_eSPI tft = TFT_eSPI();    

void clear_options(){
  display_option.clear();  
  current_id = 0;
  x = 0;
}

void intialize_screen(){
  tft.begin();
  Serial.println("Initialized tft");
  tft.setRotation(2); // Landscape orientation, USB at bottom right
  Serial.println("Set rotation");
  tft.setSwapBytes(false);
  tft.setTextSize(FONTSIZE);
  tft.setTextColor(SECONDARY_COLOR);

  tft.setTextDatum(MC_DATUM);
}

void fill_screen(unsigned int color =  SECONDARY_COLOR){
  tft.fillScreen(color);
}


int new_option(String Text){
  
  tft.fillRect(0, x, tft.width(), ROWSIZE, PRIMARY_COLOR);
  
  

  tft.drawString(Text, tft.width() / 2, ROWSIZE / 2 + x);

  DisplayOption new_struct;
  new_struct.id = current_id;
  new_struct.name = Text;
  
  x = x + ROWSIZE + 1;
  current_id++;
  display_option.push_back(new_struct);
  return new_struct.id;
}

void draw_option_at(int place, int id, unsigned int color = PRIMARY_COLOR){
  tft.fillRect(0, ROWSIZE * place + place, tft.width(), ROWSIZE , color);
  
  tft.drawString(display_option[id].name, tft.width() / 2, ROWSIZE / 2 + ROWSIZE * place + place - 1);
}




void next_option(){

  current_id++;

  draw_option_at(0, (current_id - 2) % display_option.size());
  draw_option_at(1,  (current_id - 1) % display_option.size());
  draw_option_at(2,  (current_id) % display_option.size(), HIGHLIGHT_COLOR);
  draw_option_at(3,  (current_id + 1)% display_option.size());
  draw_option_at(4,  (current_id + 2) % display_option.size());
  

  
}

void previous_option(){
  current_id--;
  
  draw_option_at(0, (current_id - 2) % display_option.size());
  draw_option_at(1,  (current_id - 1) % display_option.size());
  draw_option_at(2,  (current_id) % display_option.size(), HIGHLIGHT_COLOR);
  draw_option_at(3,  (current_id + 1)% display_option.size());
  draw_option_at(4,  (current_id + 2) % display_option.size());
  


}


void succes_message(){
  fill_screen(HIGHLIGHT_COLOR);
  
  tft.drawString("message sent ", tft.width() / 2, tft.height() / 2 - ROWSIZE);
  tft.drawString("click button to ", tft.width() / 2, tft.height() / 2);
  tft.drawString("send another message", tft.width() / 2, tft.height() / 2 + ROWSIZE);
}