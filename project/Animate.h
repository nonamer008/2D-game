#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
class Animate {
private:
	sf::Texture texture;
	uint8_t cadrCount = 0;
	uint8_t sizeX = 0, sizeY = 0;
	sf::Vector2f offset;
	float speed = 0;
	float timer = 0;
public:
	sf::Sprite sprite;
	Animate(sf::Vector2f size, std::string path, float mashtabe, uint8_t cadrCount, float speed) {
		this->speed = speed;
		this->cadrCount = cadrCount;
		sizeX = size.x;
		sizeY = size.y;
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
		sprite.setScale(sf::Vector2f(
			size.x * mashtabe / sprite.getGlobalBounds().width,
			size.y * mashtabe / sprite.getGlobalBounds().height
		));
	}
	Animate  (sf::Vector2f offset, sf::Vector2f size, std::string path, float mashtabe, uint8_t cadrCount, float speed) 
	: Animate(size, path, mashtabe, cadrCount, speed) {
		this->offset = offset;
	}
	void setPosition(int posX, int posY) {
		sprite.setPosition(posX + offset.x, posY + offset.y);
	}
	void draw(sf::RenderWindow* window) {
		timer += speed;
		if (timer >= cadrCount)
			timer = 0;
		sprite.setTextureRect(sf::IntRect(sizeX * (int)timer, 0, sizeX, sizeY));
		window->draw(sprite);
	}
};
Animate torch(sf::Vector2f(-0.1 * scale, -0.8 * scale), sf::Vector2f(8, 18), "resources\\sprites\\torch.png", 2, 6, 0.05);