#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Indicator {
private:
	sf::RectangleShape drawscale;
	uint16_t size = 0;
	uint16_t mashtabe = 0;
	short posx = 0;
	short posy = 0;
	float*target = 0;
	float offset = 0;
public:
	Indicator(sf::Vector2f pos, uint16_t size, uint16_t max, float* target, float offset) {
		drawscale.setPosition(pos);
		posx = pos.x - desctopeSizeX / 4;
		posy = pos.y - desctopeSizeY / 4;
		this->size = size;
		this->target = target;
		this->offset = offset;
		mashtabe = size / (max + offset);
	}
	void draw(sf::RenderWindow* window) {

		drawscale.setFillColor(sf::Color::Cyan);
		drawscale.setSize(sf::Vector2f(size + 10, 20));
		drawscale.setPosition(posx + window->getView().getCenter().x, posy + window->getView().getCenter().y);
		window->draw(drawscale);

		drawscale.setFillColor(sf::Color::Blue);
		drawscale.setSize(sf::Vector2f((*target + offset) * mashtabe, 10));
		drawscale.setPosition(posx + 5 + window->getView().getCenter().x, posy + 5 + window->getView().getCenter().y);
		window->draw(drawscale);
	}
};
Indicator stress(sf::Vector2f(0, 0), 100, 3, &player.stress, -1);