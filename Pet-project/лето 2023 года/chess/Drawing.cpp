#include "Drawing.h"

Drawing::Drawing(int ind_color)
{
    ind_color_ = ind_color;

    if (ind_color_ == 0)
        Loading_w();
    else
        Loading_b();

    Loading_figure_w();
    Loading_figure_b();
}
void Drawing::Loading_w()
{
    board = board_w;
    selection_rect = selection_rect_w;
}
void Drawing::Loading_b()
{
    board = board_b;
    selection_rect = selection_rect_b;
}
void Drawing::Loading_figure_w()
{
    white_pictures.resize(16);
    for (int i = 0; i < 8; ++i)
    {
        white_pictures[i].first = white_texture[0];
        white_pictures[i].second = Coords(2, i + 1);
    }

    white_pictures[8].first = white_texture[1];
    white_pictures[8].second = Coords(1, 1);
    white_pictures[9].first = white_texture[2];
    white_pictures[9].second = Coords(1, 2);
    white_pictures[10].first = white_texture[3]; 
    white_pictures[10].second = Coords(1, 3);
    white_pictures[11].first = white_texture[4]; 
    white_pictures[11].second = Coords(1, 4);
    white_pictures[12].first = white_texture[5]; 
    white_pictures[12].second = Coords(1, 5);
    white_pictures[13].first = white_texture[3];
    white_pictures[13].second = Coords(1, 6);
    white_pictures[14].first = white_texture[2];
    white_pictures[14].second = Coords(1, 7);
    white_pictures[15].first = white_texture[1];
    white_pictures[15].second = Coords(1, 8);
}
void Drawing::Loading_figure_b()
{
    black_pictures.resize(16);
    for (int i = 0; i < 8; ++i)
    {
        black_pictures[i].first = black_texture[0];
        black_pictures[i].second = Coords(7, i + 1);
    }

    black_pictures[8].first = black_texture[1];
    black_pictures[8].second = Coords(8, 1);
    black_pictures[9].first = black_texture[2];
    black_pictures[9].second = Coords(8, 2);
    black_pictures[10].first = black_texture[3];
    black_pictures[10].second = Coords(8, 3);
    black_pictures[11].first = black_texture[4];
    black_pictures[11].second = Coords(8, 4);
    black_pictures[12].first = black_texture[5];
    black_pictures[12].second = Coords(8, 5);
    black_pictures[13].first = black_texture[3];
    black_pictures[13].second = Coords(8, 6);
    black_pictures[14].first = black_texture[2];
    black_pictures[14].second = Coords(8, 7);
    black_pictures[15].first = black_texture[1];
    black_pictures[15].second = Coords(8, 8);
}

void Drawing::componized()
{
    Global::window.clear(backgraund_color);
    {
        Sprite sprite;
        sprite.setTexture(board);
        sprite.setPosition(float((Global::window.getSize().x - boardSize) / 2), 
                           float((Global::window.getSize().y - boardSize) / 2));
        Global::window.draw(sprite);
    }
    for (int i = 0; i < 16; ++i)
    {
        if (white_pictures[i].second.row != -1)
        {
            Sprite sprite;
            sprite.setTexture(white_pictures[i].first);
            sprite.setScale(0.58, 0.58);
            pair<float, float> coords = Global::pos_to_coords(white_pictures[i].second, ind_color_);
            sprite.setPosition(coords.first, coords.second);
            Global::window.draw(sprite);
        }
    }
    for (int i = 0; i < 16; ++i)
    {
        if (black_pictures[i].second.row != -1)
        {
            Sprite sprite;
            sprite.setTexture(black_pictures[i].first);
            pair<float, float> coords = Global::pos_to_coords(black_pictures[i].second, ind_color_);
            sprite.setPosition(coords.first, coords.second);
            sprite.setScale(0.58, 0.58);
            Global::window.draw(sprite);
        }
    }
}

void Drawing::update(pair<Coords, Coords>* move)
{
    componized();
    if (move != nullptr)
    {
        backlight(move->first);
        backlight(move->second);
    }
}

void Drawing::backlight(Coords cell)
{
    pair<int, int> coords = Global::pos_to_coords(cell, ind_color_);
    RectangleShape rect({ 100, 100 });
    rect.setFillColor(Color(0, 255, 0, 50));
    rect.setPosition(coords.first - 23, coords.second - 5);
    Global::window.draw(rect);
}

void Drawing::show_selection_rect()
{
    Sprite rect;
    rect.setTexture(selection_rect);
    rect.setPosition(float(((Global::window.getSize().x - boardSize) / 2 - 85)/ 2), 
                     float((Global::window.getSize().y - 470) / 2));
    Global::window.draw(rect);
}

Drawing::~Drawing()
{
}
