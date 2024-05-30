#include "Gllobal.h"

void reading_ind(int& ind, bool& game_alive)
{
    bool still_reading = true;
    while (still_reading)
    {
        Event event;
        if (Global::window.pollEvent(event))
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Escape:
                {
                    game_alive = false;
                    still_reading = false;
                    break;
                }
                }
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                pair<int, int> coords = { event.mouseButton.x, event.mouseButton.y };
                if (350 <= coords.first && coords.first <= 598 &&
                    254 <= coords.second && coords.second <= 427)
                {
                    ind = 0;
                    still_reading = false;
                }
                if (1245 <= coords.first && coords.first <= 1492 &&
                    256 <= coords.second && coords.second <= 426)
                {
                    ind = 1;
                    still_reading = false;
                }
            }
    }
}

void start_of_game(int& ind, bool& game_alive)
{
    Global::window.clear(backgraund_color);
    Image picture;
    bool flag = picture.loadFromFile("images/Choose_the_color.png");
    Texture texture;
    texture.loadFromImage(picture);
    Sprite sprite(texture);
    sprite.setPosition(0, 0);
    sprite.setScale({Global::window.getSize().x / sprite.getLocalBounds().getSize().x,
                     Global::window.getSize().y / sprite.getLocalBounds().getSize().y});
    Global::window.draw(sprite);
    Global::window.display();
    reading_ind(ind, game_alive);
}