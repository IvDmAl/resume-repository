#include "king.h"
#include "Game.h"

King::King(int row, int col, int ind_c)
{
	pos_.row = row;
	pos_.col = col;
	ind_color_ = ind_c;
}

void King::next_poss(const Game& game, vector<Coords>& next_pos)
{
	for (int d_row = -1; d_row <= 1; ++d_row)
		for (int d_col = -1; d_col <= 1; ++d_col)
			if (d_row != 0 || d_col != 0)
			{
				Coords cell(pos_.row + d_row, pos_.col + d_col);
				pair<Piece*, int> t = game.type_cell(cell, ind_color_);
				if (Global::on_field(cell) && t.second <= 0)
				{
					bool flag;
					{
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
	//ракеровка
	Rook* rook =dynamic_cast<Rook*>(ind_color_ == 0 ? game.white[8] : game.black[8]);
	if (rook && !was_move && !rook->was_move)
	{
		int tc2 = game.type_cell(Coords(ind_color_ == 0 ? 1 : 8, 2), ind_color_).second;
		int tc3 = game.type_cell(Coords(ind_color_ == 0 ? 1 : 8, 3), ind_color_).second;
		int tc4 = game.type_cell(Coords(ind_color_ == 0 ? 1 : 8, 4), ind_color_).second;
		if (tc2 == 0 && tc3 == 0 && tc4 == 0)
		{
			bool bc3 = game.cell_beat(Coords(ind_color_ == 0 ? 1 : 8, 3), ind_color_);
			bool bc4 = game.cell_beat(Coords(ind_color_ == 0 ? 1 : 8, 4), ind_color_);
			bool bc5 = game.cell_beat(Coords(ind_color_ == 0 ? 1 : 8, 5), ind_color_);
			if (!bc3 && !bc4 && !bc5)
			{
				next_pos.push_back(Coords(ind_color_ == 0 ? 1 : 8, 3));
			}
		}
	}
	rook = dynamic_cast<Rook*>(ind_color_ == 0 ? game.white[15] : game.black[15]);
	if (rook && !was_move && !rook->was_move)
	{
		int tc7 = game.type_cell(Coords(ind_color_ == 0 ? 1 : 8, 7), ind_color_).second;
		int tc6 = game.type_cell(Coords(ind_color_ == 0 ? 1 : 8, 6), ind_color_).second;
		if (tc6 == 0 && tc7 == 0)
		{
			bool bc7 = game.cell_beat(Coords(ind_color_ == 0 ? 1 : 8, 7), ind_color_);
			bool bc6 = game.cell_beat(Coords(ind_color_ == 0 ? 1 : 8, 6), ind_color_);
			bool bc5 = game.cell_beat(Coords(ind_color_ == 0 ? 1 : 8, 5), ind_color_);
			if (!bc7 && !bc6 && !bc5)
			{
				next_pos.push_back(Coords(ind_color_ == 0 ? 1 : 8, 7));
			}
		}
	}
}

void King::beat_poss(const Game& game, vector<Coords>& beat_pos)
{
	for (int d_row = -1; d_row <= 1; ++d_row)
		for (int d_col = -1; d_col <= 1; ++d_col)
			if (d_row != 0 || d_col != 0)
			{
				Coords pos(pos_.row + d_row, pos_.col + d_col);
				if (Global::on_field(pos))
					beat_pos.push_back(pos);
			}
}


King::~King()
{
}