#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
class CastomFont : public sf::Font {
public:
	CastomFont() {}
	CastomFont(std::string path) {
		loadFromFile(path);
	}
};
CastomFont font("resources\\font.ttf");

class CastomText : public sf::Text {
public:
	sf::Vector2f NullPos;
	CastomText() {}
	CastomText(uint8_t size) {
		setFillColor(sf::Color::White);
		setCharacterSize(size);
		setFont(font);
	}
	CastomText(sf::Vector2f pos, uint16_t size) : CastomText(size) {
		NullPos = pos;
		setPosition(pos);
	}
	CastomText(sf::Vector2f pos, std::string str, uint8_t size) : CastomText(pos, size) {
		setString(str);
	}
};
CastomText dialogText(50 * camera.getSize().x / desctopeSizeX);