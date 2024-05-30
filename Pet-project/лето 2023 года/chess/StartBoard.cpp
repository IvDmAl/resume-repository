#include "Gllobal.h"

void writing(vector<FloatRect>& buttons)
{
	Global::window.clear(backgraund_color);
	{
		Text header("Select function:", font, 100);
		header.setPosition((Global::window.getSize().x - header.getLocalBounds().getSize().x) / 2,
			(Global::window.getSize().y / 4.0 - header.getLocalBounds().getSize().y) / 2.0);
		Global::window.draw(header);
	}
	{
		vector<string> text_on_buttons = { "Game", "Instruction" };
		pair<pair<int, int>, pair<int, int>> size_rect; {
			size_rect = { { Global::window.getSize().x / 4, Global::window.getSize().x / 4 * 3},
						  { Global::window.getSize().y / 4, Global::window.getSize().y} };
		}
		pair<int, int> size_buttons; {
			size_buttons.second = (size_rect.second.second - size_rect.second.first) / (text_on_buttons.size() + 1);
			size_buttons.first = 0;
			for (string s : text_on_buttons)
				size_buttons.first = max<int>(size_buttons.first, Text(s, font, size_buttons.second * 3 / 4).getLocalBounds().getSize().x * 4 / 3);
		}

		for (int i = 0; i < text_on_buttons.size(); ++i)
		{
			buttons.push_back(FloatRect({ float((size_rect.first.first + size_rect.first.second - size_buttons.first) / 2),
				float(size_rect.second.first + (size_rect.second.second - size_rect.second.first) / text_on_buttons.size() * i) },
				{ float(size_buttons.first), float(size_buttons.second) }));
			FloatRect& button_rect = buttons[buttons.size() - 1];

			RectangleShape background_bar(button_rect.getSize());
			background_bar.setPosition(button_rect.getPosition());
			background_bar.setFillColor(Color::Color(115, 59, 32));
			Global::window.draw(background_bar);

			Text text(text_on_buttons[i], font, size_buttons.second * 3 / 4);
			text.setPosition(float(background_bar.getPosition().x +
				(button_rect.getSize().x - text.getLocalBounds().getSize().x) / 2),
				float(background_bar.getPosition().y + size_buttons.second / 16));
			Global::window.draw(text);
		}
	}
	Global::window.display();
}

int reading(vector<FloatRect>& buttons)
{
	while (true)
	{
		Event event;
		if (Global::window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					return -1;
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				pair<int, int> coords = { event.mouseButton.x, event.mouseButton.y };
				for (int i = 0; i < buttons.size(); ++i)
					if (buttons[i].getPosition().x <= coords.first)
						if (buttons[i].getPosition().y <= coords.second)
							if (coords.first <= (buttons[i].getPosition().x + buttons[i].getSize().x))
								if (coords.second <= (buttons[i].getPosition().y + buttons[i].getSize().y))
									return i;
			}
		}
	}
}

int start_board()
{
	vector<FloatRect> buttons;
	writing(buttons);
	return reading(buttons);
}