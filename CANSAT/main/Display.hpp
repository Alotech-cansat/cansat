#include <TFT_eSPI.h> 
#include <stdio.h>

#define ROWSIZE 50

#define FONTSIZE 2

#define BLACK 0x0000
#define WHITE 0xFFFF
#define BLUE 0x00FF

using namespace std;

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


int new_option(string Text){
  
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

void draw_option_at(int place, int id, unsigned int color = BLACK){
  tft.fillRect(0, ROWSIZE * place + place, tft.width(), ROWSIZE , color);
  
  tft.drawString(display_option[id].name.c_str(), tft.width() / 2, ROWSIZE / 2 + ROWSIZE * place + place - 1);
}




void next(){



  draw_option_at(0, (current_id - 2) % display_option.size());
  draw_option_at(1,  (current_id - 1) % display_option.size());
  draw_option_at(2,  (current_id) % display_option.size(), BLUE);
  draw_option_at(3,  (current_id + 1)% display_option.size());
  draw_option_at(4,  (current_id + 2) % display_option.size());
  

  current_id++;
}

void back(){
  draw_option_at(0, (current_id - 2) % display_option.size());
  draw_option_at(1,  (current_id - 1) % display_option.size());
  draw_option_at(2,  (current_id) % display_option.size(), BLUE);
  draw_option_at(3,  (current_id + 1)% display_option.size());
  draw_option_at(4,  (current_id + 2) % display_option.size());
  

  current_id--;
}
