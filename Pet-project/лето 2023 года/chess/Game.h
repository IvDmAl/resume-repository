#pragma once
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "pawn.h"

class Game
{
public:
	Game(int ind, Drawing* d);
	~Game();

	void print(pair<Coords, Coords>* move = nullptr);
	pair<Piece*, int> type_cell(Coords cell, int ind_q_p) const;
	bool cell_beat(Coords cell, int ind_q_p) const;
	int get_ind();

	bool game_over()
	{
		bool is_mat_w = is_mat(0);
		bool is_mat_b = is_mat(1);
		bool is_pat_w = is_pat(0);
		bool is_pat_b = is_pat(1);
		return !comunication.game_alive || is_mat_w || is_mat_b || is_pat_w ||is_pat_b;
	}

	bool is_hax(int ind_q_p)const;
	bool is_mat(int ind_q_p);
	bool is_pat(int ind_q_p);

	Coords get_pos_from_ind(int ind, int ind_q_p)
	{
		if (ind_q_p == 0)
			return white[ind]->get_pos();
		else
			return black[ind]->get_pos();
	}

	bool make_move(Coords last_pos, Coords new_pos, int ind_p, int = -1);

	vector<Piece*> white, black;
	int ind_p;
	Comunication comunication;
	Drawing* drawing;
private:
	void init_figures(vector<Piece*>& figures, bool color_white);
	bool cell_beat_helper(Coords cell, vector<Piece*> enemys_figurs) const;
	bool is_hax_helper(Coords pos_king, vector<Piece*> enemys_figurs)const;
	bool is_mat_helper(Piece* king, vector<Piece*> our_figurs, vector<Piece*> enemys_figurs);
	bool is_pat_helper(vector<Piece*> our_figurs);
	bool make_move_helper(Coords, Coords, int, vector<Piece*>, vector<Piece*>, int = -1);
};

