#include "bishop.h"
#include "Game.h"

Bishop::Bishop(int row, int col, int ind_c)
{
	pos_.row = row;
	pos_.col = col;
	ind_color_ = ind_c;
}

void Bishop::next_poss(const Game& game, vector<Coords>& next_pos)
{
	for (int d_row = -1; d_row <= 1; d_row += 2)
		for (int d_col = -1; d_col <= 1; d_col += 2)
			for (int i = 1; i <= 7; ++i)
			{
				Coords cell = Coords(pos_.row + d_row * i, pos_.col + d_col * i);
				if (Global::on_field(cell))
				{
					int type = game.type_cell(cell, ind_color_).second;
					if (type <= 0)
					{
						bool flag;
						{
							pair<Piece*, int> t = game.type_cell(cell, ind_color_);
							if (t.second == -1)
								t.first->pos_ = Coords(-100, -100);

							Coords pos = pos_;
							pos_ = cell;
							flag = game.is_hax(ind_color_);
							pos_ = pos;

							if (t.second == -1)
								t.first->pos_ = cell;
						}
						if (!flag)
							next_pos.push_back(cell);
					}
					if (type != 0)
						break;
				}
				else
					break;
			}
}
void Bishop::beat_poss(const Game& game, vector<Coords>& beat_pos)
{
	for (int d_row = -1; d_row <= 1; d_row += 2)
		for (int d_col = -1; d_col <= 1; d_col += 2)
			for (int i = 1; i <= 7; ++i)
			{
				Coords cell = Coords(pos_.row + d_row * i, pos_.col + d_col * i);
				if (Global::on_field(cell))
				{
					int type = game.type_cell(cell, ind_color_).second;
					beat_pos.push_back(cell);
					if (type != 0)
						break;
				}
				else
					break;
			}
}

Bishop::~Bishop()
{
}