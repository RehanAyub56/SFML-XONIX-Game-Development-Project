#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

const int text_count2 = 5;

struct MenuContext2 {
    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    sf::Text texts[text_count2];
    std::size_t sizes[text_count2];
    const char* options[text_count2];
    float coords[text_count2][2];
    int position;
    bool select, pressed;
    int difficulty_level;
};


void setup_menu2(MenuContext2& ctx);
void cleanup_menu2(MenuContext2& ctx);
void init_menu2(MenuContext2& ctx);
void loop_events2(MenuContext2& ctx);
void draw_all2(MenuContext2& ctx);
int run_menu2(MenuContext2& ctx);


