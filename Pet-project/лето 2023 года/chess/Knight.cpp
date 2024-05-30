#include "knight.h"
#include "Game.h"

Knight::Knight(int row, int col, int ind_c)
{
	pos_.row = row;
	pos_.col = col;
	ind_color_ = ind_c;
}

void Knight::next_poss(const Game& game, vector<Coords>& next_pos)
{
	vector<int> delts = { -2, -1, 1, 2 };
	for (int d_row : delts)
		for (int d_col : delts)
			if (abs(d_row) != abs(d_col))
			{
				Coords cell(pos_.row + d_row, pos_.col + d_col);
				int type = game.type_cell(cell, ind_color_).second;
				if (Global::on_field(cell) && type <= 0)
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
			}
}

void Knight::beat_poss(const Game& game, vector<Coords>& beat_pos)
{
	vector<int> delts = { -2, -1, 1, 2 };
	for (int d_row : delts)
		for (int d_col : delts)
			if (abs(d_row) != abs(d_col))
			{
				Coords pos(pos_.row + d_row, pos_.col + d_col);
				if (Global::on_field(pos))
					beat_pos.push_back(pos);
			}
}

Knight::~Knight()
{
}