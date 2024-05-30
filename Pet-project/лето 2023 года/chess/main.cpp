#include "Drawing.h"
#include "Game.h"


RenderWindow Global::window;

int main()
{
    Global::window.create(VideoMode(1920, 1080), "Chess", Style::Fullscreen);
	Global::window.setVerticalSyncEnabled(true);
	
	loading();

	bool still_app_alive = true;
	while (still_app_alive)
	{
		int ind = start_board();
		switch (ind)
		{
		case -1: still_app_alive = false; break;
		case 0:	
			still_app_alive = PlayGame(); break;
		case 1:
			still_app_alive = Instruction(); break;
		}
	}
	
	Global::window.close();
}