#pragma once
#include "piece.h"

class Queen : public Piece
{
public:
	Queen(int row, int col, int ind_c);
	~Queen();
	string type() { return "Queen"; }
	char print(bool white) { return white?'q':'Q'; }
	void next_poss(const Game& game, vector<Coords>& next_pos);
	void beat_poss(const Game& game, vector<Coords>& beat_pos);
private:
	bool next_poss_helper(Coords cell, const Game& game, vector<Coords>& next_pos);
	bool beat_poss_helper(Coords cell, const Game& game, vector<Coords>& next_pos);
};
