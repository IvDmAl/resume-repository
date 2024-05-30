#include "Gllobal.h"
const Color backgraund_color = Color::Blue;
const int boardSize = 900;
Font font;
vector<Texture> white_texture;
vector<Texture> black_texture;
Texture board_w;
Texture board_b;
Texture selection_rect_w;
Texture selection_rect_b;

vector<string> instructions_text;

void way_of_file_to_texture(string way, Texture& figure)
{
    Image picture;
    bool flag = picture.loadFromFile(way);
    figure.loadFromImage(picture);
    if (!flag)
        cout << "not found " + way;
}