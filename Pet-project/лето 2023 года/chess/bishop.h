#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
	Bishop(int row, int col, int ind_c);
	~Bishop();
	string type() { return "Bishop"; }
	char print(bool white) { return white?'b':'B'; }
	void next_poss(const Game& game, vector<Coords>& next_pos);
	void beat_poss(const Game& game, vector<Coords>& beat_pos);
private:
};
