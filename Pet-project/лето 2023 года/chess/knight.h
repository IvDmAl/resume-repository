#pragma once
#include "piece.h"

class Knight : public Piece
{
public:
	Knight(int row, int col, int ind_c);
	~Knight();
	string type() { return "Knight"; }
	char print(bool white) { return white?'n':'N'; }
	void next_poss(const Game& game, vector<Coords>& next_pos);
	void beat_poss(const Game& game, vector<Coords>& beat_pos);
private:
};

