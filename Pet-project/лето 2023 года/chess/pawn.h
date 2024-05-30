#pragma once
#include "piece.h"

class Pawn : public Piece
{
public:
	Pawn(int row, int col, int ind_c);
	~Pawn();
	string type() { return "Pawn"; }
	char print(bool white) { return white ? 'p':'P'; }
	void next_poss(const Game& game, vector<Coords>& next_pos);
	void beat_poss(const Game& game, vector<Coords>& beat_pos);
	Coords last_pos;
private:
};

