#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Sounds.h"
#include "settings.h"
#include "textures.h"
#define playerSizeY 0.36 * 5.1
#define playerSizeX 0.17 * 5.1
#define playerHalfY 0.36 * 5.1 / 2
#define playerHalfX 0.17 * 5.1 / 2

sf::RenderWindow window;

class Player {
private:
	sf::Texture texture;
	float animate = 0;
	float speed = 0.05;
public:
	sf::ConvexShape ray;
	sf::Sprite sprite;
	uint8_t hp = 5;
	uint8_t numlvl = 0;
	float x = 1.5, y = 1.5;
	float stress = 1;
	bool isLight = false;

	uint16_t lampTimer = 0;

	Player(int) {
		// загрузка настроек и сохранений
		std::ifstream file;
		// сохранение игрока
		file.open("resources\\saves\\saves");
		file.read((char*)&numlvl, 1);
		file.close();
		// настройки
		file.open("resources\\saves\\settings");
		file.read((char*)&settingsInfo, sizeof(settingsInfo));
		file.close();
		// выставление громкости
		updateVolume(settingsInfo.soundVolume, settingsInfo.musicVolume);
		// режим экрана
		if (!settingsInfo.fullScreen == false)
			window.create(sf::VideoMode(settingsInfo.windowSizeX, settingsInfo.windowSizeY), "darkness is a lie");
		else
			window.create(sf::VideoMode(desctopeSizeX, desctopeSizeY), "darkness is a lie", sf::Style::Fullscreen);

		texture.loadFromFile("resources\\sprites\\player.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 20, 36));
		sprite.setScale(sf::Vector2f(
			18 * 3 / sprite.getGlobalBounds().width,
			34 * 3 / sprite.getGlobalBounds().height
		));

		ray.setPointCount(3);
		ray.setFillColor(sf::Color(255, 255, 255, 25));
	}
	void save() {
		std::ofstream file;
		file.open("resources\\saves\\saves");
		file.write((char*)&numlvl, 1);
		file.close();
	}
	void move(char** map) {
		bool isMove = false;
		speed = 0.05 * stress;
		if (isLight == false) {
			if (stress < 3)
				stress += 0.01;
		}
		else if (stress > 1)
			stress -= 0.005;

		cave.setVolume(settingsInfo.soundVolume - stress * settingsInfo.soundVolume / 3);
		screemHeart.setVolume((stress - 1) * settingsInfo.soundVolume);
		if (screemHeart.getStatus() != screemHeart.Playing)
			screemHeart.play();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			isMove = true;
			if (map[(int)y][(int)(x + playerSizeX + speed)] > hardBlock) {
				if (map[(int)(y + playerSizeY)][(int)(x + playerSizeX + speed)] > hardBlock) {
					if (map[(int)(y + playerHalfY)][(int)(x + playerSizeX + speed)] > hardBlock)
						x += speed;
				}
			}
			sprite.setTextureRect(sf::IntRect(18 * (int)animate, (152 * (lampTimer > 0)) + 38 * 2, 18, 38));
			animate += 0.15;
			if (animate > 4.8)
				animate = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			isMove = true;
			if (map[(int)y][(int)(x - speed)] > hardBlock) {
				if (map[(int)(y + playerSizeY)][(int)(x - speed)] > hardBlock) {
					if (map[(int)(y + playerHalfY)][(int)(x - speed)] > hardBlock)
						x -= speed;
				}
			}
			sprite.setTextureRect(sf::IntRect(18 * (int)animate, (152 * (lampTimer > 0)) + 38 * 3, 18, 38));
			animate += 0.15;
			if (animate > 4.8)
				animate = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (isMove == false)
				animate += 0.1;
			else
				animate -= 0.05;
			if (animate > 3.8)
				animate = 0;

			if (map[(int)(y - speed)][(int)x] > hardBlock) {
				if (map[(int)(y - speed)][(int)(x + playerSizeX)] > hardBlock)
					y -= speed;
			}
			sprite.setTextureRect(sf::IntRect(20 * (int)animate, (152 * (lampTimer > 0)) + 38 * 0, 20, 38));
			isMove = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (isMove == false)
				animate += 0.1;
			else
				animate -= 0.05;

			if (animate > 3.7)
				animate = 0;

			if (map[(int)(y + playerSizeY + speed)][(int)x] > hardBlock) {
				if (map[(int)(y + playerSizeY + speed)][(int)(x + playerSizeX)] > hardBlock)
					y += speed;
			}
			sprite.setTextureRect(sf::IntRect(20 * (int)animate, (152 * (lampTimer > 0)) + 38 * 1, 20, 38));
			isMove = true;
		}

		if (isMove == false) {
			walking.stop();
			sprite.setTextureRect(sf::IntRect(0, (152 * (lampTimer > 0)) + 38, 20, 38));
		}
		else {
			if (walking.getStatus() != walking.Playing)
				walking.play();
		}

		if (lampTimer == 0)
			isLight = false;
		else
			isLight = true;

		sprite.setPosition(x * scale, y * scale);
	}
};
Player player(NULL);