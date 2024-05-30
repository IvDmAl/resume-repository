#pragma once
#include "piece.h"

class King : public Piece
{
public:
	King(int row, int col, int ind_c);
	~King();
	string type() { return "King"; }
	char print(bool white) { return white?'k':'K'; }
	void next_poss(const Game& game, vector<Coords>& next_pos);
	void beat_poss(const Game& game, vector<Coords>& beat_pos);

	bool was_move = false;
private:

};
