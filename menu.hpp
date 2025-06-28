#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
const int text_count=5;
struct MenuContext{
int position;
bool select,pressed,isactive=true;
sf:: RenderWindow * window;
sf:: RectangleShape * winclose;
sf:: Font * font;
sf:: Texture * image;
sf:: Sprite * bg;
sf:: Vector2i pos_mouse;
sf:: Vector2f mouse_coord;
const char* options[text_count];
float coords[text_count][2];
sf::Text texts[text_count];
std :: size_t sizes[text_count];
int difficulty_level;
int playernumber;
};


void setup_menu(MenuContext& ctx);
void cleanup_menu(MenuContext& ctx);
void init_menu(MenuContext& ctx);
void loop_events(MenuContext& ctx);
void draw_all(MenuContext& ctx);
void run_menu(MenuContext& ctx);



