#pragma once
#include "Gllobal.h"

class Piece
{
public:
	Piece();
	~Piece();
	virtual string type() { return ""; }
	virtual char print(bool white) { return ' '; }
	virtual void next_poss(const Game& game, vector<Coords>& next_pos) {}
	virtual void beat_poss(const Game& game, vector<Coords>& beat_pos) {}
	Coords get_pos(){return pos_;}

	friend class Game;

	Coords pos_;
	int ind_color_;
protected:
};
