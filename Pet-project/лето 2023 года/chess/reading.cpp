#include "Game.h"
#include "Drawing.h"

void reading_helper(Game& game, Coords pos, Coords& first_point, Coords& second_point, int ind_p)
{
	if (Global::on_field(pos))
	{
		if (first_point == Coords())
		{
			if (game.type_cell(pos, ind_p).second == 1)
			{
				game.drawing->update();
				game.drawing->backlight(pos);
				Global::window.display();
				first_point = pos;
			}
		}
		else
		{
			vector<Coords> next_pos;
			game.type_cell(first_point, ind_p).first->next_poss(game, next_pos);
			bool is_in = false;
			for (Coords& i : next_pos)
				if (i == pos)
				{
					is_in = true;
					break;
				}
			if (is_in)
			{
				game.drawing->update();
				game.drawing->backlight(pos);
				Global::window.display();
				second_point = pos;
			}
			else
			{
				first_point = Coords();
				reading_helper(game, pos, first_point, second_point, ind_p);
			}
		}
	}
	else
		first_point = Coords();
}

void reading(Game& game, pair<Coords, Coords>& points, int ind_p)
{
	bool still_reading = true;
	Coords first_point;
	Coords second_point;
	while (still_reading)
	{
		Event event;
		if (Global::window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
				{
					game.comunication.game_alive = false;
					still_reading = false;
					break;
				}
				}
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				pair<int, int> coords = { event.mouseButton.x, event.mouseButton.y };
				Coords pos = Global::coords_to_pos(coords, game.get_ind());
				reading_helper(game, pos, first_point, second_point, ind_p);
				if (!(second_point == Coords()))
				{
					points = { first_point, second_point };
					still_reading = false;
				}
			}
		}
	}
}

int read_wanted_figure(Game* game, pair<Coords, Coords> move)//1 rook 2 knight 3 bishop 4 queen
{
	game->drawing->update(&move);
	game->drawing->show_selection_rect();
	Global::window.display();

	while (true)
	{
		Event event;
		if (Global::window.pollEvent(event))
			if (event.type == Event::MouseButtonPressed)
			{
				pair<int, int> coords = { event.mouseButton.x, event.mouseButton.y };
				if (212 <= coords.first && coords.first <= 300 &&
					304 <= coords.second && coords.second <= 775)
				{
					if (coords.second <= 403)
						return 2;
					if (coords.second <= 537)
						return 3;
					if (coords.second <= 633)
						return 1;
					return 4;
				}
			}
	}
}