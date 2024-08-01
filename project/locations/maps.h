#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "testMap.h"
#include "secondLoc.h"

class Location {
public:
	float startX, startY;
	uint8_t sizeX, sizeY;
	Light* lights;
	Lamp* tools;
	uint8_t toolsCount = 0, lightsCount = 0;
	char** map;
	const char** texts;
	Location(char** map, sf::Vector2i size, sf::Vector2f startPos, Light* lights, uint8_t lightCount, Lamp* lamps, uint8_t lampsCount, const char** texts) {
		this->lights = lights;
		this->tools = lamps;
		this->map = map;
		this->toolsCount = lampsCount;
		this->lightsCount = lightCount;
		this->texts = texts;
		startX = startPos.x;
		startY = startPos.y;
		sizeX = size.x;
		sizeY = size.y;
	}
};

uint8_t maxLvls = 1;

Location maps[] = {
	Location(testMap, sf::Vector2i(10, 8), sf::Vector2f(1.5, 3), testMapLights, 1, NULL, 0, testMapTexts),
	Location(secondLoc, sf::Vector2i(10, 10), sf::Vector2f(1, 2), secondLocLights, 1, secondLocLamps, 1, secondLocTexts)
};