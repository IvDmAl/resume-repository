#include "Game.h"
#include "Drawing.h"
#include <stdlib.h>
#include <time.h>

pair<Coords, Coords> calc_move_b(const Game& game)
{
	vector<pair<Coords, Coords>> able_move;
	for (int i = 0; i < game.black.size(); ++i)
	{
		vector<Coords> next_pos;
		game.black[i]->next_poss(game, next_pos);
		for (int j = 0; j < next_pos.size(); ++j)
			able_move.push_back({ game.black[i]->get_pos(), next_pos[j] });
	}

	return able_move[rand() % able_move.size()];
}

void PlayWhite(Game& game)
{
	srand(time(0));
	game.print();
	while (!game.game_over())
	{
		pair<Coords, Coords> move;
		reading(game, move, game.get_ind());

		if (!game.comunication.game_alive)
			break;
		
		game.make_move(move.first, move.second, 0);
		game.print(&move);
		
		if (game.game_over())
			break;
		
		/*move = calc_move_b(game);
		game.make_move(move.first, move.second, 1, rand() % 4 + 1);
		game.print(&move);*/
		reading(game, move, 1 - game.get_ind());
		game.make_move(move.first, move.second, 1);
		game.print(&move);
	}
}