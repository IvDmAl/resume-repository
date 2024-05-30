#include "Gllobal.h"
#include "Game.h"
#include "Drawing.h"

void write_text(vector<string>& strs, int start_pos)
{
	Global::window.clear(backgraund_color);
	int last_size_y = 0;
	for (int i = 0; i < strs.size(); ++i)
	{
		Text text(strs[i], font, 50);
		text.setPosition((Global::window.getSize().x - text.getLocalBounds().getSize().x) / 2,
			(i * last_size_y) + 50 + start_pos);
		Global::window.draw(text);
		
		last_size_y = 75;
	}
	Global::window.display();
}
void event_handling(vector<string>& strs)
{
	int start_pos = 0;
	int min_posible_start_pos = (strs.size() * 75);
	write_text(strs, start_pos);
	while (true)
	{
		Event event;
		if (Global::window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					return;
			if (event.type == Event::MouseWheelScrolled)
			{
				int last_start_pos = start_pos;
				start_pos += event.mouseWheelScroll.delta * 15;
				if (start_pos > 0)
					start_pos = 0;
				if (start_pos < Global::window.getSize().y - min_posible_start_pos - 100)
					start_pos = last_start_pos;

				write_text(strs, start_pos);
			}
		}
	}
}

bool Instruction()
{
	vector<string> strs;
	string tmp;
	for (int i = 0; i < instructions_text.size(); ++i)
	{
		if (tmp.size() + instructions_text[i].size() > 60)
		{
			strs.push_back(tmp);
			tmp = "";
		}
		tmp += " " + instructions_text[i];
	}
	strs.push_back(tmp);
	event_handling(strs);
	return true;
}