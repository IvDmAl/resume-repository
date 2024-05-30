#include "Gllobal.h"

void load_white_texture()
{
    way_of_file_to_texture("images/chess_board_w.png", board_w);
    way_of_file_to_texture("images/selection_rect_w.png", selection_rect_w);
    white_texture.resize(6);
    way_of_file_to_texture("images/w_pawn.png", white_texture[0]);
    way_of_file_to_texture("images/w_rook.png", white_texture[1]);
    way_of_file_to_texture("images/w_knight.png", white_texture[2]);
    way_of_file_to_texture("images/w_bishop.png", white_texture[3]);
    way_of_file_to_texture("images/w_queen.png", white_texture[4]);
    way_of_file_to_texture("images/w_king.png", white_texture[5]);
}
void load_black_texture()
{
    way_of_file_to_texture("images/chess_board_b.png", board_b);
    way_of_file_to_texture("images/selection_rect_b.png", selection_rect_b);
    black_texture.resize(6);
    way_of_file_to_texture("images/b_pawn.png", black_texture[0]);
    way_of_file_to_texture("images/b_rook.png", black_texture[1]);
    way_of_file_to_texture("images/b_knight.png", black_texture[2]);
    way_of_file_to_texture("images/b_bishop.png", black_texture[3]);
    way_of_file_to_texture("images/b_queen.png", black_texture[4]);
    way_of_file_to_texture("images/b_king.png", black_texture[5]);
}
void load_text()
{
    ifstream cin("texts/instruction.txt");
    string tmp;
    while (cin >> tmp)
        instructions_text.push_back(tmp);
}

void loading()
{
    load_text();
	font.loadFromFile("fonts/CyrilicOld.ttf");
    load_white_texture();
    load_black_texture();
}