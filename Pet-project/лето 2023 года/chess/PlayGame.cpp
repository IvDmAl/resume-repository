#include "Drawing.h"
#include "Game.h"

bool PlayGame()
{
	int ind;
	bool game_alive = true;
	bool app_alive = true;
	while (game_alive)
	{
		start_of_game(ind, game_alive);
		if (!game_alive)
			break;

		Drawing drawing(ind);
		Game game(ind, &drawing);

		game.comunication.game_alive = game_alive;

		if (game.get_ind() == 0)
			PlayWhite(game);
		else
			PlayBlack(game);

		app_alive = game.comunication.game_alive;

		int ind = end_of_game(game);
		game_alive = false;
		switch (ind)
		{
		case -1: game_alive = true; break;
		case 0: game_alive = true; break;
		}	
	}
	return true;
}