#include "pawn.h"
#include "Game.h"

Pawn::Pawn(int row, int col, int ind_c)
{
	pos_.row = row;
	pos_.col = col;
	ind_color_ = ind_c;
}

void Pawn::next_poss(const Game& game, vector<Coords>& next_pos)
{
	if (ind_color_ == 0)
	{
		for (int d_row = 1; d_row <= 1 + (pos_.row == 2); ++d_row)
		{
			Coords cell(pos_.row + d_row, pos_.col);
			int type = game.type_cell(cell, ind_color_).second;
			if (type == 0)
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
			else
				break;
		}
		if (pos_.col <= 7 && game.type_cell(Coords(pos_.row + 1, pos_.col + 1), ind_color_).second == -1)
		{
			Coords cell(pos_.row + 1, pos_.col + 1);
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
		if (pos_.col >= 2 && game.type_cell(Coords(pos_.row + 1, pos_.col - 1), ind_color_).second == -1)
		{
			Coords cell(pos_.row + 1, pos_.col - 1);
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
		
		if (pos_.row == 5 && pos_.col <= 7)
		{
			pair<Piece*, int> type_cell = game.type_cell(Coords(pos_.row, pos_.col + 1), ind_color_);
			if (type_cell.second == -1 && type_cell.first->type() == "Pawn" &&
				static_cast<Pawn*>(type_cell.first)->last_pos == Coords(type_cell.first->pos_.row + 2, type_cell.first->pos_.col))
			{
				Coords cell(pos_.row + 1, pos_.col + 1);
				bool flag;
				{
					Coords pos = pos_;
					pos_ = cell;
					flag = game.is_hax(ind_color_);
					pos_ = pos;
				}
				if (!flag)
					next_pos.push_back(cell);
			}
		}
		if (pos_.row == 5 && pos_.col >= 2)
		{
			pair<Piece*, int> type_cell = game.type_cell(Coords(pos_.row, pos_.col - 1), ind_color_);
			if (type_cell.second == -1 && type_cell.first->type() == "Pawn" &&
				static_cast<Pawn*>(type_cell.first)->last_pos == Coords(type_cell.first->pos_.row + 2, type_cell.first->pos_.col))
			{
				Coords cell(pos_.row + 1, pos_.col - 1);
				bool flag;
				{
					Coords pos = pos_;
					pos_ = cell;
					flag = game.is_hax(ind_color_);
					pos_ = pos;
				}
				if (!flag)
					next_pos.push_back(cell);
			}
		}
	}
	else
	{
		for (int d_row = 1; d_row <= 1 + (pos_.row == 7); ++d_row)
		{
			Coords cell(pos_.row - d_row, pos_.col);
			int type = game.type_cell(cell, ind_color_).second;
			if (type == 0)
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
			else
				break;
		}
		if (pos_.col <= 7 && game.type_cell(Coords(pos_.row - 1, pos_.col + 1), ind_color_).second == -1)
		{
			Coords cell(pos_.row - 1, pos_.col + 1);
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
		if (pos_.col >= 2 && game.type_cell(Coords(pos_.row - 1, pos_.col - 1), ind_color_).second == -1)
		{
			Coords cell(pos_.row - 1, pos_.col - 1);
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

		if (pos_.row == 4 && pos_.col <= 7)
		{
			pair<Piece*, int> type_cell = game.type_cell(Coords(pos_.row, pos_.col + 1), ind_color_);
			if (type_cell.second == -1 && type_cell.first->type() == "Pawn" &&
				static_cast<Pawn*>(type_cell.first)->last_pos == Coords(type_cell.first->pos_.row - 2, type_cell.first->pos_.col))
			{
				Coords cell(pos_.row - 1, pos_.col + 1);
				bool flag;
				{
					Coords pos = pos_;
					pos_ = cell;
					flag = game.is_hax(ind_color_);
					pos_ = pos;
				}
				if (!flag)
					next_pos.push_back(cell);
			}
		}
		if (pos_.row == 4 && pos_.col >= 2)
		{
			pair<Piece*, int> type_cell = game.type_cell(Coords(pos_.row, pos_.col - 1), ind_color_);
			if (type_cell.second == -1 && type_cell.first->type() == "Pawn" &&
				static_cast<Pawn*>(type_cell.first)->last_pos == Coords(type_cell.first->pos_.row - 2, type_cell.first->pos_.col))
			{
				Coords cell(pos_.row - 1, pos_.col - 1);
				bool flag;
				{
					Coords pos = pos_;
					pos_ = cell;
					flag = game.is_hax(ind_color_);
					pos_ = pos;
				}
				if (!flag)
					next_pos.push_back(cell);
			}
		}
	}
}

void Pawn::beat_poss(const Game& game, vector<Coords>& beat_pos)
{
	if (ind_color_ == 0)
	{
		if (pos_.col <= 7)
			beat_pos.push_back(Coords(pos_.row + 1, pos_.col + 1));
		if (pos_.col >= 2)
			beat_pos.push_back(Coords(pos_.row + 1, pos_.col - 1));
	}
	else
	{
		if (pos_.col <= 7)
			beat_pos.push_back(Coords(pos_.row - 1, pos_.col + 1));
		if (pos_.col >= 2)
			beat_pos.push_back(Coords(pos_.row - 1, pos_.col - 1));
	}
}

Pawn::~Pawn()
{
}