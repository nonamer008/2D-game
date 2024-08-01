#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "text.h"
class Regulator {
private:
	char* target;
	sf::RectangleShape mainScale;
	sf::RectangleShape slider;
	uint16_t max;
	uint16_t size;

	bool isTouth = false;

	CastomText* text = NULL;
public:
	Regulator(sf::Vector2f position, uint16_t max, uint16_t size, char* target) {
		this->target = target;
		this->max = max;
		this->size = size;

		mainScale.setPosition(position);
		mainScale.setSize(sf::Vector2f(size, 6));
		mainScale.setFillColor(sf::Color(255, 255, 255));

		slider.setSize(sf::Vector2f(12, 24));
		slider.setPosition(sf::Vector2f(position.x + (*target * size / max), position.y - 6));
		slider.setFillColor(sf::Color(200, 200, 200));
	}
	Regulator(sf::Vector2f pos, uint16_t max, uint16_t size, char* target, std::string str) : Regulator(pos, max, size, target) {
		text = new CastomText(sf::Vector2f(pos.x + size + 15, pos.y - 24), str, 30);
	}

	~Regulator() {
		delete text;
	}

	void draw(sf::RenderWindow* window) {
		window->draw(mainScale);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (mouseX > slider.Pos.x && mouseX < slider.Pos.x + 12) {
				if (mouseY > slider.Pos.y && mouseY < slider.Pos.y + 24)
					isTouth = true;
			}
		}
		else
			isTouth = false;

		if (isTouth == true) {
			if (mouseX >= mainScale.Pos.x && mouseX <= mainScale.Pos.x + size) {
				slider.setPosition(mouseX, slider.Pos.y);
				*target = max * (slider.Pos.x - mainScale.Pos.x) / size;
			}
			else if (mouseX < mainScale.Pos.x) {
				slider.setPosition(mainScale.Pos.x, slider.Pos.y);
				*target = 0;
			}
			else {
				slider.setPosition(mainScale.Pos.x + size, slider.Pos.y);
				*target = max;
			}
		}
		window->draw(slider);
		if (text != NULL)
			window->draw(*text);
	}
};