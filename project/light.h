#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "settings.h"
#include "textures.h"
#include "Animate.h"
#include "Player.h"
#define step 0.02
class Light {
private:
	sf::ConvexShape ray;
	Animate* animate = NULL;
	struct Point {
		uint16_t x, y;
	};
	std::vector <Point> points;
	sf::Vector2f pos;
	float r;
public:
	Light(sf::Vector2f pos, float r, Animate* animate, char* map[]) {
		ray.setPointCount(3);
		ray.setPoint(0, sf::Vector2f(pos.x * scale, pos.y * scale));
		ray.setFillColor(sf::Color(255, 255, 255, 50));
		this->animate = animate;
		this->pos = pos;
		this->r = r;

		float angleStep = 0.01;

		bool isWall = false;

		for (float angle = 0; angle < 3.14159 * 2;) {
			sf::Vector2f rayPos = pos;
			sf::Vector2f rayMov(cosf(angle) * step, sinf(angle) * step);
			angleStep = 0.2;

			for (float i = 0; i < r; i += step) {
				rayPos.x += rayMov.x;
				rayPos.y += rayMov.y;
				if (map[(int)rayPos.y][(int)rayPos.x] <= hardBlock + 3) {
					angleStep = 0.05;
					break;
				}
			}
			Point point{ rayPos.x * scale, rayPos.y * scale };
			points.push_back(point);
			angle += angleStep;
		}
	}
	void draw(sf::RenderWindow* window, char* map[]) {
		// если расстояние до источника света слишком больше, то не отрисовывать его
		sf::Vector2f dist(player.x - pos.x, player.y - pos.y);
		if (pifagor(dist) > r + pifagor(sf::Vector2f(desctopeSizeX * 0.01, desctopeSizeY * 0.01))) 
			return;
		// отрисовка спрайта
		animate->setPosition(pos.x * scale, pos.y * scale);
		animate->draw(window);
		// отрисовка света
		for (int i = 0; i < points.size() - 1; i++) {
			ray.setPoint(1, sf::Vector2f(points[i + 1].x, points[i + 1].y));
			ray.setPoint(2, sf::Vector2f(points[i].x, points[i].y));
			window->draw(ray);
		}
		ray.setPoint(2, sf::Vector2f(points[0].x, points[0].y));
		window->draw(ray);

		if (pifagor(dist) > r)
			return;
		if (player.lampTimer > 0) 
			return;

		// определение угла
		float x = player.x + playerSizeX / 2 - pos.x;
		float y = player.y + playerSizeY / 2 - pos.y;
		float angle = 0;
		if (x > 0)
			angle = atanf(y / x);
		else
			angle = 3.14159 + atanf(y / x);
		sf::Vector2f rayPos = pos;
		sf::Vector2f rayMove(cosf(angle) * 0.5, sinf(angle) * 0.5);
		// проверка на свет
		for (float i = 0; i < r; i += 0.5) {
			rayPos.x += rayMove.x;
			rayPos.y += rayMove.y;
			if (map[(int)rayPos.y][(int)rayPos.x] <= hardBlock)
				return;
			if (rayPos.x > player.x && rayPos.x < player.x + playerSizeX) {
				if (rayPos.y > player.y && rayPos.y < player.y + playerSizeY) {
					player.isLight = true;
					return;
				}
			}
		}
	}
};