#pragma once
#include <SFML/Graphics.hpp>
sf::View camera;
#define scale 60
#define pifagor(a) std::sqrtf(a.x * a.x + a.y * a.y)
#define screenSizeX 1200
#define screenSizeY 600

#define desctopeSizeX sf::VideoMode::getDesktopMode().width
#define desctopeSizeY sf::VideoMode::getDesktopMode().height
#define screenProportion sf::VideoMode::getDesktopMode().width / sf::VideoMode::getDesktopMode().height

#define hardBlock 15
#define tables 27

#define Pos getPosition()

uint16_t mouseX = 0, mouseY = 0;

uint8_t lvlcount = 0;

char styles[] = {sf::Style::Default, sf::Style::Fullscreen};