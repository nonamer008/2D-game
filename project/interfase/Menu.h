#pragma once
#include <SFML/Graphics.hpp>
#include "Sounds.h"
#include "settings.h"
#include "text.h"
#include "btnFlags.h"
class Menu {
private:
	bool* isPlay = NULL;
	const char** strings;
	sf::CircleShape mark;
	uint16_t size;
public:
	CastomText* text = NULL;
	uint8_t count;
	uint16_t TextSize;
	Menu(sf::Vector2f pos, uint16_t Tsize, const char** strings, uint8_t count) {
		isPlay = new bool[count];
		text = new CastomText(pos, Tsize);
		TextSize = Tsize;
		this->count = count;
		this->strings = strings;
	}
	~Menu() {
		delete[] isPlay;
		delete text;
	}
	int draw(sf::RenderWindow* window) {
		int result = -1;
		for (uint8_t i = 0; i < count; i++) {
			text->setCharacterSize(TextSize);
			uint16_t TextX = text->NullPos.x;
			uint16_t TextY = text->NullPos.y + TextSize * i;

			text->setPosition(TextX, TextY - 10);
			text->setString(strings[i]);

			if (mouseX > TextX && mouseX < TextX + text->getLocalBounds().width &&
				mouseY > TextY && mouseY < TextY + TextSize)
			{
				if (isPlay[i] == false) 
					touchBtn.play();
				isPlay[i] = true;
				text->setCharacterSize(TextSize + 10);
				if (mouseFirstCadr == true) 
					result = i;
			}
			else
				isPlay[i] = false;
			window->draw(*text);
		}
		return result;
	}
};
const char* strings[] = {
	"play",
	"settings",
	"qout"
};

Menu startMenu(sf::Vector2f(desctopeSizeX / 3, desctopeSizeY / 2), 50, strings, 3);