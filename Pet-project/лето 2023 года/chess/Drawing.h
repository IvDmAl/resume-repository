#pragma once
#include"Gllobal.h"

class Drawing
{
public:
	Drawing(int);
	~Drawing();
	void componized();
	void update(pair<Coords, Coords>* move = nullptr);
	void backlight(Coords cell);
	void show_selection_rect();

	vector<pair<Texture, Coords>> white_pictures;
	vector<pair<Texture, Coords>> black_pictures;
private:
	void Loading_w();
	void Loading_b();
	void Loading_figure_w();
	void Loading_figure_b();

	Texture board;
	Texture selection_rect;
	int ind_color_;
};