#pragma once
#include "piece.h"

class Rook : public Piece
{
public:
	Rook(int row, int col, int ind_c);
	~Rook();
	string type(){return "Rook";}
	char print(bool white) { return white?'r':'R'; }
	void next_poss(const Game& game, vector<Coords>& next_pos);
	void beat_poss(const Game& game, vector<Coords>& beat_pos);
	bool was_move = false;
private:
	bool next_poss_helper(Coords cell, const Game& game, vector<Coords>& next_pos);
	bool beat_poss_helper(Coords cell, const Game& game, vector<Coords>& next_pos);
};
