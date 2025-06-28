#include "menu.hpp"
#include "level.hpp"
#include "player.hpp"

void setup_menu(MenuContext& ctx){
        ctx.window =new sf::RenderWindow();
        ctx.winclose = new sf::RectangleShape();
        ctx.font = new sf::Font();
        ctx.image = new sf::Texture();
        ctx.bg = new sf::Sprite();
        ctx.position = 0;
        ctx.select = ctx.pressed = false;
    }
    
    void cleanup_menu(MenuContext& ctx) {
    delete ctx.window;
    delete ctx.winclose;
    delete ctx.font;
    delete ctx.image;
    delete ctx.bg;
}
    

void init_menu(MenuContext& ctx) {
    ctx.window->create(sf::VideoMode(1360, 768), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    ctx.window->setPosition(sf::Vector2i(0, 0));

    ctx.font->loadFromFile("images/airstrike.ttf");
    ctx.image->loadFromFile("images/menu.png");
    ctx.bg->setTexture(*ctx.image);
    ctx.pos_mouse = {0, 0};
    ctx.mouse_coord = {0, 0}; //location of mouse according to grid
// For Menu 
    ctx.options[0] = "XONIX";      //Declaring names of the options in menu
    ctx.options[1] = "Start Game";
    ctx.options[2] = "Select Level";
    ctx.options[3] = "Scoreboard";
    ctx.options[4] = "Quit";

    ctx.coords[0][0] = 620; ctx.coords[0][1] = 32;        //location of the names in grid
    ctx.coords[1][0] = 590; ctx.coords[1][1] = 191;
    ctx.coords[2][0] = 582; ctx.coords[2][1] = 282;
    ctx.coords[3][0] = 582; ctx.coords[3][1] = 370;
    ctx.coords[4][0] = 623; ctx.coords[4][1] = 457;

    ctx.sizes[0] = 26;            //Font size of the names of options of menu
    ctx.sizes[1] = 24;
    ctx.sizes[2] = 24;
    ctx.sizes[3] = 24;
    ctx.sizes[4] = 24;

    for (int i = 0; i < text_count; ++i) {
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

void loop_events(MenuContext& ctx) {
    sf::Event event;
    while (ctx.window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ctx.window->close();
        }

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !ctx.pressed) {
            if (ctx.position < 4) {   // implementing movement of cursor on menu 
                ++ctx.position;
                ctx.pressed = true;
                ctx.texts[ctx.position].setOutlineThickness(6); //When the cursor is move on any option on menu it becomes highlighted
                
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
        else if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Enter) {
                ctx.select = true;
                
            }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (ctx.winclose->getGlobalBounds().contains(ctx.mouse_coord)) {
                ctx.window->close();
            }
        }
    }
}

void draw_all(MenuContext& ctx) {
    ctx.window->clear();
    ctx.window->draw(*ctx.bg);
    for (auto t : ctx.texts) { //auto is used to remove text without any error
        ctx.window->draw(t);// it clears text of the menu written
    }
    ctx.window->display();
}

void run_menu(MenuContext& ctx) {
    while (ctx.window->isOpen()) {
        loop_events(ctx);
        draw_all(ctx);
        if (ctx.select) { 
        
         if(ctx.position==1){
          ctx.window->close();
         MenuContext3 menu3;
        setup_menu3(menu3);

        init_menu3(menu3);
       int selected2=run_menu3(menu3);
         cleanup_menu3(menu3);
         ctx.playernumber=selected2;
         ctx.select = false;
         }
        
          else if(ctx.position==2){
          ctx.window->close();
         MenuContext2 menu2;
        setup_menu2(menu2);

        init_menu2(menu2);
        
        int selected=run_menu2(menu2); 
         cleanup_menu2(menu2);
         ctx.difficulty_level=selected;
         ctx.select = false;
         
         
         }
         else if (ctx.position == 4) {
                ctx.window->close();
            }
         }      
    } 
}

