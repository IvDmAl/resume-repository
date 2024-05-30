#include "Game.h"
#include "Drawing.h"
#include <Windows.h>

Game::Game(int ind, Drawing* d)
{
	drawing = d;
	comunication.game_alive = true;
	ind_p = ind;
	init_figures(white, true);
	init_figures(black, false);
}
void Game::init_figures(vector<Piece*>& figures, bool color_white)
{
	for (int i = 1; i <= 8; ++i)
		figures.push_back(new Pawn(color_white ? 2 : 7, i, color_white ? 0 : 1));

	figures.push_back(new Rook(color_white ? 1 : 8, 1, color_white?0:1));
	figures.push_back(new Knight(color_white ? 1 : 8, 2, color_white ? 0 : 1));
	figures.push_back(new Bishop(color_white ? 1 : 8, 3, color_white ? 0 : 1));
	figures.push_back(new Queen(color_white ? 1 : 8, 4, color_white ? 0 : 1));
	figures.push_back(new King(color_white ? 1 : 8, 5, color_white ? 0 : 1));
	figures.push_back(new Bishop(color_white ? 1 : 8, 6, color_white ? 0 : 1));
	figures.push_back(new Knight(color_white ? 1 : 8, 7, color_white ? 0 : 1));
	figures.push_back(new Rook(color_white ? 1 : 8, 8, color_white ? 0 : 1));
}

void Game::print(pair<Coords, Coords>* move)
{
	sleep(seconds(0.25));
	for (int i = 0; i < 16; ++i)
	{
		drawing->white_pictures[i].second = white[i]->pos_;
		drawing->black_pictures[i].second = black[i]->pos_;
	}
	drawing->update(move);
	Global::window.display();
}

pair<Piece*, int> Game::type_cell(Coords cell, int ind_q_p) const  // -1 не наша 0 пустая 1 наша фигура
{
	for (int i = 0; i < white.size(); ++i)
		if (white[i]->get_pos() == cell)
			return { white[i], ind_q_p == 0 ? 1 : -1 };

	for (int i = 0; i < black.size(); ++i)
		if (black[i]->get_pos() == cell)
			return { black[i], ind_q_p == 1 ? 1 : -1 };

	return { nullptr, 0 };
}

bool Game::cell_beat(Coords cell, int ind_q_p) const
{
	if (ind_q_p == 0)
		return cell_beat_helper(cell, black);
	else
		return cell_beat_helper(cell, white);
}
bool Game::cell_beat_helper(Coords cell, vector<Piece*> enemys_figurs) const
{
	for (int i = 0; i < enemys_figurs.size(); ++i)
	{
		vector<Coords> beat_pos;
		enemys_figurs[i]->beat_poss(*this, beat_pos);
		for (int j = 0; j < beat_pos.size(); ++j)
			if (cell == beat_pos[j])
				return true;
	}
	return false;
}

int Game::get_ind()
{
	return ind_p;
}

bool Game::is_hax(int ind_q_p)const
{
	if (ind_q_p == 0)
		return is_hax_helper(white[12]->get_pos(), black);
	else
		return is_hax_helper(black[12]->get_pos(), white);
}
bool Game::is_hax_helper(Coords pos_king, vector<Piece*> enemys_figurs)const
{
	for (int i = 0; i < enemys_figurs.size(); ++i)
	{
		vector<Coords> beat_pos;
		enemys_figurs[i]->beat_poss(*this, beat_pos);
		for (int j = 0; j < beat_pos.size(); ++j)
			if (pos_king == beat_pos[j])
				return true;
	}
	return false;
}

bool Game::is_mat(int ind_q_p)
{
	if (ind_q_p == 0)
		return is_hax(ind_q_p) && is_mat_helper(white[12], white, black);
	else
		return is_hax(ind_q_p) && is_mat_helper(black[12], black, white);
}
bool Game::is_mat_helper(Piece* king, vector<Piece*> our_figurs, vector<Piece*> enemys_figurs)
{
	vector<Coords> next_pos_king;
	king->next_poss(*this, next_pos_king);
	if (next_pos_king.size() != 0)
		return false;

	vector<Piece*> threat;
	for (int i = 0; i < enemys_figurs.size(); ++i)
	{
		vector<Coords> beat_pos;
		enemys_figurs[i]->beat_poss(*this, beat_pos);
		for (int j = 0; j < beat_pos.size(); ++j)
			if (king->get_pos() == beat_pos[j])
				threat.push_back(enemys_figurs[i]);
	}

	if (threat.size() > 1)
		return true;

	Piece* enemy = threat[0];
	for (int i = 0; i < our_figurs.size(); ++i)
	{
		vector<Coords> next_pos;
		our_figurs[i]->next_poss(*this, next_pos);
		for (int j = 0; j < next_pos.size(); ++j)
			if (enemy->get_pos() == next_pos[j])
				return false;
	}

	if (enemy->type() == "Knight")
		return true;
	
	vector<Coords> way;
	{
		int d_row;
		if (king->get_pos().row > enemy->get_pos().row)
			d_row = 1;
		else if (king->get_pos().row < enemy->get_pos().row)
			d_row = -1;
		else
			d_row = 0;

		int d_col;
		if (king->get_pos().col > enemy->get_pos().col)
			d_col = 1;
		else if (king->get_pos().col < enemy->get_pos().col)
			d_col = -1;
		else
			d_col = 0;

		Coords pos = enemy->get_pos();
		pos.row += d_row;
		pos.col += d_col;
		while (!(pos == king->get_pos()))
		{
			way.push_back(pos);
			pos.row += d_row;
			pos.col += d_col;
		}
	}

	for (Coords goal : way)
	{
		for (int i = 0; i < our_figurs.size(); ++i)
		{
			vector<Coords> next_pos;
			our_figurs[i]->next_poss(*this, next_pos);
			for (int j = 0; j < next_pos.size(); ++j)
				if (goal == next_pos[j])
					return false;
		}
	}

	return true;
}

bool Game::is_pat(int ind_q_p)
{
	if (ind_q_p == 0)
		return !is_hax(ind_q_p) && is_pat_helper(white);
	else
		return !is_hax(ind_q_p) && is_pat_helper(black);
}
bool Game::is_pat_helper(vector<Piece*> our_figurs)
{
	int total = 0;
	for (auto figur : our_figurs)
	{
		vector<Coords> next_pos;
		figur->next_poss(*this, next_pos);
		total += next_pos.size();
	}
	if (total == 0)
		return true;
	else
		return false;
}

bool Game::make_move(Coords last_pos, Coords new_pos, int ind_p, int ind_new_figur)
{
	if (ind_p == 0)
		return make_move_helper(last_pos, new_pos, ind_p, white, black, ind_new_figur);
	else
		return make_move_helper(last_pos, new_pos, ind_p, black, white, ind_new_figur);
}
bool Game::make_move_helper(Coords last_pos, Coords new_pos, int ind_p, vector<Piece*> our_figurs, 
	vector<Piece*> enemys_figurs, int ind_new_figur)
{
	Piece* piece = nullptr;
	int index_piece;
	{
		for (int i = 0; i < our_figurs.size(); ++i)
			if (our_figurs[i]->get_pos() == last_pos)
			{
				piece = our_figurs[i];
				index_piece = i;
				break;
			}
	}

	//проверка хода
	{
		if (piece == nullptr)
			return false;
		vector<Coords> able_pos;
		piece->next_poss(*this, able_pos);
		bool in_able_pos = false;
		for (int i = 0; i < able_pos.size(); ++i)
			if (able_pos[i] == new_pos)
			{
				in_able_pos = true;
				break;
			}
		if (!in_able_pos)
			return false;
	}

	int type_new_pos;
	Piece* piece_on_new_pos;
	{
		pair<Piece*, int> tmp = type_cell(new_pos, ind_p);
		piece_on_new_pos = tmp.first;
		type_new_pos = tmp.second;
		if (piece->type() == "Pawn" && last_pos.col != new_pos.col && type_new_pos == 0)
		{
			tmp = type_cell(Coords(last_pos.row, new_pos.col), ind_p);
			piece_on_new_pos = tmp.first;
			type_new_pos = tmp.second;
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		if (white[i]->type() == "Pawn")
			static_cast<Pawn*>(white[i])->last_pos = white[i]->pos_;
		if (black[i]->type() == "Pawn")
			static_cast<Pawn*>(black[i])->last_pos = black[i]->pos_;
	}

	if (piece->type() == "King" && abs(last_pos.col - new_pos.col) == 2)
	{
		if (new_pos.col < last_pos.col)
			our_figurs[8]->pos_ = Coords(piece->ind_color_ == 0 ? 1 : 8, 4);
		else
			our_figurs[15]->pos_ = Coords(piece->ind_color_ == 0 ? 1 : 8, 6);
	}
	piece->pos_ = new_pos;

	if (piece->type() == "Rook")
		static_cast<Rook*>(piece)->was_move = true;
	if (piece->type() == "King")
		static_cast<King*>(piece)->was_move = true;

	if (type_new_pos == -1)
	{
		for (int i = 0; i < white.size(); ++i)
			if (white[i] == piece_on_new_pos)
				white[i] = new Piece();
		for (int i = 0; i < black.size(); ++i)
			if (black[i] == piece_on_new_pos)
				black[i] = new Piece();
		delete piece_on_new_pos;
	}

	if (piece->type() == "Pawn" && piece->get_pos().row == (piece->ind_color_ == 0 ? 8 : 1))
	{
		int ind = read_wanted_figure(this, { last_pos, new_pos });

		Piece* new_piece = nullptr;
		switch (ind)
		{
		case 1: new_piece = new Rook	(piece->get_pos().row, piece->get_pos().col, piece->ind_color_); 
			if (piece->ind_color_ == 0)
				drawing->white_pictures[index_piece] = drawing->white_pictures[8]; 
			else
				drawing->black_pictures[index_piece] = drawing->black_pictures[8]; 
			break;
		case 2: new_piece = new Knight	(piece->get_pos().row, piece->get_pos().col, piece->ind_color_);
			if (piece->ind_color_ == 0)
				drawing->white_pictures[index_piece] = drawing->white_pictures[9];
			else
				drawing->black_pictures[index_piece] = drawing->black_pictures[9];
			break;
		case 3: new_piece = new Bishop	(piece->get_pos().row, piece->get_pos().col, piece->ind_color_);
			if (piece->ind_color_ == 0)
				drawing->white_pictures[index_piece] = drawing->white_pictures[10];
			else
				drawing->black_pictures[index_piece] = drawing->black_pictures[10];
			break;
		case 4: new_piece = new Queen	(piece->get_pos().row, piece->get_pos().col, piece->ind_color_);
			if (piece->ind_color_ == 0)
				drawing->white_pictures[index_piece] = drawing->white_pictures[11];
			else
				drawing->black_pictures[index_piece] = drawing->black_pictures[11];
			break;
		}

		for (int i = 0; i < white.size(); ++i)
			if (white[i] == piece)
				white[i] = new_piece;
		for (int i = 0; i < black.size(); ++i)
			if (black[i] == piece)
				black[i] = new_piece;
		delete piece;
	}

	return true;
}

Game::~Game()
{
	for (int i = 0; i < white.size(); ++i)
		delete white[i];
	for (int i = 0; i < black.size(); ++i)
		delete black[i];
}