#include "Game.h"

#include <stdlib.h>
#include <time.h>

pair<Coords, Coords> calc_move_w(const Game& game)
{
	vector<pair<Coords, Coords>> able_move;
	for (int i = 0; i < game.white.size(); ++i)
	{
		vector<Coords> next_pos;
		game.white[i]->next_poss(game, next_pos);
		for (int j = 0; j < next_pos.size(); ++j)
			able_move.push_back({ game.white[i]->get_pos(), next_pos[j] });
	}

	return able_move[rand() % able_move.size()];
}

void PlayBlack(Game& game)
{
	srand(time(0));
	game.print();
	while (!game.game_over())
	{
		pair<Coords, Coords> move = calc_move_w(game);
		game.make_move(move.first, move.second, 0, rand() % 4 + 1);
		game.print(&move);
		
		if (game.game_over())
			break;

		reading(game, move, game.get_ind());
		game.make_move(move.first, move.second, 1);
		game.print(&move);
	}
}