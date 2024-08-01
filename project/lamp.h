#pragma once
#include <SFML/Graphics.hpp>
#include "Animate.h"
#include "Player.h"
class Lamp {
private:
	Animate* animate;
	float x, y;
	bool IIsUse;
public:
	Lamp(sf::Vector2f pos) {
		animate = new Animate(
			sf::Vector2f(-0.4 * scale, -0.5 * scale),
			sf::Vector2f(20, 34),
			"resources\\sprites\\lamp.png",
			2, 3, 0.1
		);
		x = pos.x;
		y = pos.y;
		animate->setPosition(pos.x * scale, pos.y * scale);
	}
	~Lamp() {
		delete animate;
	}

	void draw(sf::RenderWindow* window) {
		if (IIsUse == true)
			return;
		animate->draw(window);
		if (player.x + playerSizeX > x && player.x < x + 0.20) {
			if (player.y + playerSizeY > y && player.y < y + 0.34) {
				IIsUse = true;
				player.lampTimer = 60 * 10;
			}
		}
	}
};