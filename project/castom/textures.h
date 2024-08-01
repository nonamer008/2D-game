#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
class CastomTexture : public sf::Sprite {
private:
	sf::Texture texture;
public:
	CastomTexture(std::string path, sf::Vector2f cadrsize, float mashtabe) {
		texture.loadFromFile(path);
		setTexture(texture);
		setTextureRect(sf::IntRect(0, 0, cadrsize.x, cadrsize.y));
		setScale(sf::Vector2f(
			cadrsize.x * mashtabe / getLocalBounds().width,
			cadrsize.y * mashtabe / getLocalBounds().height
		));
	}
	CastomTexture(std::string path, sf::Vector2f size) {
		texture.loadFromFile(path);
		setTexture(texture);
		setTextureRect(sf::IntRect(0, 0, 16, 16));
		setScale(sf::Vector2f(
			size.x / getGlobalBounds().width,
			size.y / getGlobalBounds().height
		));
	}
	CastomTexture(std::string path, sf::Vector2f size, sf::Color color) : CastomTexture(path, size) {
		setColor(color);
	}
};
CastomTexture walls("resources\\sprites\\walls.png", sf::Vector2f(scale, scale), sf::Color(200, 200, 200));
CastomTexture heart("resources\\sprites\\heart.png", sf::Vector2f(7, 7), 4);