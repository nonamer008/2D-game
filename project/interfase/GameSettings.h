#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Regulator.h"
#include "settings.h"
#include "btnFlags.h"
#include "Sounds.h"
#include "Menu.h"
#include "text.h"
struct {
	char musicVolume = 0;
	char soundVolume = 0;
	bool verticalSync = false;
	bool fullScreen = true;
	uint32_t windowSizeX;
	uint32_t windowSizeY;
} settingsInfo;

void settings(sf::RenderWindow* window) {
	Regulator musicRegulator(sf::Vector2f(desctopeSizeX / 20, desctopeSizeY / 4.0), 100, desctopeSizeX / 3, &settingsInfo.musicVolume, "music volume");
	Regulator soundRegulator(sf::Vector2f(desctopeSizeX / 20, desctopeSizeY / 3.6), 100, desctopeSizeX / 3, &settingsInfo.soundVolume, "sound volume");

	const char* strings[] = {
		"vertical synchronization",
		"full screen",
		"back"
	};
	Menu settingsMenu(sf::Vector2f(desctopeSizeX / 20, desctopeSizeY / 20), 60, strings, 3);

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
			else if (event.type == sf::Event::Resized) {
				sf::Vector2u newSize = window->getSize();
				newSize.x = desctopeSizeX * window->getSize().y / desctopeSizeY;
				window->setSize(newSize);
			}
		}
		mouseX = sf::Mouse::getPosition(*window).x * desctopeSizeX / window->getSize().x;
		mouseY = sf::Mouse::getPosition(*window).y * desctopeSizeY / window->getSize().y;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (mouseBtn == false) {
				mouseBtn = true;
				mouseFirstCadr = true;
			}
			else
				mouseFirstCadr = false;
		}
		else {
			mouseFirstCadr = false;
			mouseBtn = false;
		}

		window->clear();
		soundRegulator.draw(window);
		musicRegulator.draw(window);

		int count = settingsMenu.draw(window);
		if (count != -1) {
			pressedBtn.play();
			if (count == 0)
				settingsInfo.verticalSync = !settingsInfo.verticalSync;
			else if (count == 1) {
				if (settingsInfo.fullScreen == false)
					window->create(sf::VideoMode(desctopeSizeX, desctopeSizeY), "dark is a lie", sf::Style::Default);
				else
					window->create(sf::VideoMode(desctopeSizeX, desctopeSizeY), "dark is a lie", sf::Style::Fullscreen);
				settingsInfo.fullScreen = !settingsInfo.fullScreen;
			}
			else if (count == 2) {
				updateVolume(settingsInfo.soundVolume, settingsInfo.musicVolume);

				window->setVerticalSyncEnabled(settingsInfo.verticalSync);

				settingsInfo.windowSizeX = window->getSize().x;
				settingsInfo.windowSizeY = window->getSize().y;

				std::ofstream file;
				file.open("resources\\saves\\settings");
				file.write((char*)&settingsInfo, sizeof(settingsInfo));
				file.close();

				return;
			}
		}
		window->display();
	}
}