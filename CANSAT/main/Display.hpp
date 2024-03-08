#include <TFT_eSPI.h> 
#include <stdio.h>

#define ROWSIZE 50

#define FONTSIZE 2

#define BLACK 0x0000
#define WHITE 0xFFFF
#define BLUE 0x00FF

struct DisplayOption{
  int id;
  string name;
};

int x = 0;
int current_id = 0;

std::vector<DisplayOption> display_option;

TFT_eSPI tft = TFT_eSPI();    

void intialize_screen(){
  tft.begin();
  tft.setRotation(2); // Landscape orientation, USB at bottom right
  tft.setSwapBytes(false);
  tft.setTextSize(FONTSIZE);
  tft.setTextColor(WHITE);
  tft.setTextDatum(MC_DATUM);
}

void fill_screen(unsigned int color){
  tft.fillScreen(WHITE);
}


int draw_option(string Text){
  
  tft.fillRect(0, x, tft.width(), ROWSIZE, BLACK);
  
  

  tft.drawString(Text.c_str(), tft.width() / 2, ROWSIZE / 2 + x);

  DisplayOption new_struct;
  new_struct.id = current_id;
  new_struct.name = Text;
  
  x = x + ROWSIZE + 1;
  current_id++;
  display_option.push_back(new_struct);
  return new_struct.id;
}

void choose(int id){
  tft.fillRect(0, ROWSIZE * id + id, tft.width(), ROWSIZE , BLUE);
  
  tft.drawString(display_option[id].name.c_str(), tft.width() / 2, ROWSIZE / 2 + ROWSIZE * id + id - 1);
  
}

void unchoose(int id){
  tft.fillRect(0, ROWSIZE * id + id, tft.width(), ROWSIZE , BLACK);

  
  tft.drawString(display_option[id].name.c_str(), tft.width() / 2, ROWSIZE / 2 + ROWSIZE * id + id - 1);
}

void next(){
  unchoose(current_id);
  current_id = (current_id + 1) % display_option.size();
  choose(current_id);
}

void back(){
  current_id--;
}
