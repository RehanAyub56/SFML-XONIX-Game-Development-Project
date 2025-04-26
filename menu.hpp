#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
const int text_count=5;
struct menu{
int position;
bool select,pressed;
sf:: RenderWindow * window;
sf:: RectangleShape * winclose;
sf:: Font * font;
sf:: Texture * image;
sf:: Sprite * bg;
sf:: Vector2i pos_mouse;
sf:: Vector2f mouse_coord;
sf::Text texts[text_count];
std :: size_t sizes[text_count];

};
extern const char* options[5];
extern const float* coords[5][2];

void set_value(menu& ctx);
void loop_events(menu& ctx);
void draw_all(menu& ctx);
void run_menu(menu& ctx);



