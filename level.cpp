#include "level.hpp"
#include <SFML/Graphics.hpp>
void setup_menu2(MenuContext2& ctx) {
    ctx.window = new sf::RenderWindow();
    ctx.winclose = new sf::RectangleShape();
    ctx.font = new sf::Font();
    ctx.image = new sf::Texture();
    ctx.bg = new sf::Sprite();
    ctx.position = 0;
    ctx.select = ctx.pressed = false;
}

void cleanup_menu2(MenuContext2& ctx) {
    delete ctx.window;
    delete ctx.winclose;
    delete ctx.font;
    delete ctx.image;
    delete ctx.bg;
}

void init_menu2(MenuContext2& ctx) {
    ctx.window->create(sf::VideoMode(1360, 768), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    ctx.window->setPosition(sf::Vector2i(0, 0));

    ctx.font->loadFromFile("images/airstrike.ttf");
    ctx.image->loadFromFile("images/menu.png");
    ctx.bg->setTexture(*ctx.image);

    ctx.pos_mouse = {0, 0};
    ctx.mouse_coord = {0, 0};

    ctx.options[0] = "XONIX";
    ctx.options[1] = "Easy";
    ctx.options[2] = "Medium";
    ctx.options[3] = "Hard";
    ctx.options[4] = "Continuous";

    ctx.coords[0][0] = 630; ctx.coords[0][1] = 32;
    ctx.coords[1][0] = 620; ctx.coords[1][1] = 191;
    ctx.coords[2][0] = 620; ctx.coords[2][1] = 282;
    ctx.coords[3][0] = 620; ctx.coords[3][1] = 370;
    ctx.coords[4][0] = 590; ctx.coords[4][1] = 457;

    ctx.sizes[0] = 26;
    ctx.sizes[1] = 24;
    ctx.sizes[2] = 24;
    ctx.sizes[3] = 24;
    ctx.sizes[4] = 24;

    for (int i = 0; i < text_count2; ++i) {
        ctx.texts[i].setFont(*ctx.font);
        ctx.texts[i].setString(ctx.options[i]);
        ctx.texts[i].setCharacterSize(ctx.sizes[i]);
        ctx.texts[i].setOutlineColor(sf::Color::Black);
        ctx.texts[i].setPosition(sf::Vector2f(ctx.coords[i][0], ctx.coords[i][1]));
    }
    ctx.texts[1].setOutlineThickness(4);
    ctx.position = 1;

    ctx.winclose->setSize(sf::Vector2f(23, 26));
    ctx.winclose->setPosition(1178, 39);
    ctx.winclose->setFillColor(sf::Color::Transparent);
}

void loop_events2(MenuContext2& ctx) {
    sf::Event event;
    while (ctx.window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ctx.window->close();
        }

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !ctx.pressed) {
            if (ctx.position < 4) {
                ++ctx.position;
                ctx.pressed = true;
                ctx.texts[ctx.position].setOutlineThickness(6);
                ctx.texts[ctx.position - 1].setOutlineThickness(0);
                ctx.pressed = false;
                ctx.select = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !ctx.pressed) {
            if (ctx.position > 1) {
                --ctx.position;
                ctx.pressed = true;
                ctx.texts[ctx.position].setOutlineThickness(6);
                ctx.texts[ctx.position + 1].setOutlineThickness(0);
                ctx.pressed = false;
                ctx.select = false;
               
            }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                ctx.select = true;
                ctx.difficulty_level=ctx.position;
               
                
            }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (ctx.winclose->getGlobalBounds().contains(ctx.mouse_coord)) {
                ctx.window->close();
               
            }
        }
    }
}


void draw_all2(MenuContext2& ctx) {
    ctx.window->clear();
    ctx.window->draw(*ctx.bg);
    for (auto &t : ctx.texts) {
        ctx.window->draw(t);
    }
    ctx.window->display();
}

int run_menu2(MenuContext2& ctx) {
    while (ctx.window->isOpen()) {
        loop_events2(ctx);
       
        draw_all2(ctx);
         if (ctx.select) { 
            ctx.window->close();
        }
      
    }
    return ctx.difficulty_level;
}

