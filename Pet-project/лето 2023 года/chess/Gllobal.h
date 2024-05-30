#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <fstream>

using namespace std;
using namespace sf;

extern const int boardSize;

struct Coords
{
	Coords()
	{
		row = -1;
		col = -1;
	}
	Coords(int r, int c)
	{
		row = r;
		col = c;
	}
	bool operator== (const Coords& other) const
	{
		return (row == other.row) && (col == other.col);
	}
	int row, col;
};

struct Comunication
{
	bool game_alive;
	queue<pair<int, vector<int>>> events;
};

struct Global
{
	static RenderWindow window;
	static bool on_field(Coords pos)
	{
		return (1 <= pos.row && pos.row <= 8) && (1 <= pos.col && pos.col <= 8);
	}
	static pair<float, float> pos_to_coords(Coords pos, int ind_color)
	{
		if (ind_color == 0)
			return { float((window.getSize().x - boardSize) / 2 + 44 + (pos.col - 1) * 101 + 26),
					 float((window.getSize().y - boardSize) / 2 + 44 + (8 - pos.row) * 101 + 10) };
		else
			return { float((window.getSize().x - boardSize) / 2 + 44 + (8 - pos.col) * 101 + 26),
					float((window.getSize().y - boardSize) / 2 + 44 + (pos.row - 1) * 101 + 10) };
	}
	static Coords coords_to_pos(pair<int, int> pos, int ind_color)
	{
		if (ind_color == 0)
			return { int(8 - (pos.second - ((window.getSize().y - boardSize) / 2 + 44)) / 101),
					int((pos.first - ((window.getSize().x - boardSize) / 2 + 44))/101 + 1)};
		else
			return  {int((pos.second - ((window.getSize().y - boardSize) / 2 + 44)) / 101+ 1),
					 int(8 - (pos.first - ((window.getSize().x - boardSize) / 2 + 44)) / 101) };
	}
};

class Game;
class Drawing;

void loading();
int start_board();
bool Instruction();
bool PlayGame();
void PlayBlack(Game& game);
void PlayWhite(Game& game);
void reading(Game& game, pair<Coords, Coords>& points, int ind_p);
int read_wanted_figure(Game* game, pair<Coords, Coords> move);
void start_of_game(int& ind, bool& game_alive);
int end_of_game(Game& game);

void way_of_file_to_texture(string way, Texture& figure);

extern const Color backgraund_color;

extern Font font;
extern vector<Texture> white_texture;
extern vector<Texture> black_texture;
extern Texture board_w;
extern Texture board_b;
extern Texture selection_rect_w;
extern Texture selection_rect_b;
extern vector<string> instructions_text;