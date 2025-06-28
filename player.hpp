#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

const int text_count3 = 3;

struct MenuContext3 {
    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    sf::Text texts[text_count3];
    std::size_t sizes[text_count3];
    const char* options[text_count3];
    float coords[text_count3][2];
    int position;
    bool select, pressed;
    int playernumber;
};


void setup_menu3(MenuContext3& ctx);
void cleanup_menu3(MenuContext3& ctx);
void init_menu3(MenuContext3& ctx);
void loop_events3(MenuContext3& ctx);
void draw_all3(MenuContext3& ctx);
int run_menu3(MenuContext3& ctx);

