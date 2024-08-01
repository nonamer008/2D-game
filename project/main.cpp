#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "indicator.h"
#include "textures.h"
#include "Player.h"
#include "Sounds.h"
#include "light.h"
#include "maps.h"
#include "Menu.h"
#include "text.h"

sf::RectangleShape effect;
int main() {
    effect.setSize(sf::Vector2f(desctopeSizeX / 2, desctopeSizeY / 2));
    window.setFramerateLimit(60); 
    window.setVerticalSyncEnabled(settingsInfo.verticalSync);

MainMenu:
    camera.setSize(sf::Vector2f(desctopeSizeX, desctopeSizeY));
    camera.setCenter(desctopeSizeX / 2, desctopeSizeY / 2);
    window.setView(camera);
    menuMusic.play();

    while (window.isOpen()) {
        sf::Event event; 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                sf::Vector2u newSize = window.getSize();
                newSize.x = desctopeSizeX * window.getSize().y / desctopeSizeY;
                window.setSize(newSize);
            }
        }
        mouseX = sf::Mouse::getPosition(window).x * desctopeSizeX / window.getSize().x;
        mouseY = sf::Mouse::getPosition(window).y * desctopeSizeY / window.getSize().y;

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

        window.clear();
        int count = startMenu.draw(&window);
        if (count != -1) {
            if (pressedBtn.getStatus() != pressedBtn.Playing)
                pressedBtn.play();

            if (count == 0)
                break;
            else if (count == 1)
                settings(&window);
            else if (count == 2)
                return 0;
        }
        window.display();
    }
    menuMusic.stop();

updateGame:
    player.x = maps[player.numlvl].startX;
    player.y = maps[player.numlvl].startY;
gamePlay:
    cave.setLoop(true);
    cave.play();

    camera.setSize(sf::Vector2f(desctopeSizeX / 2, desctopeSizeY / 2));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::Resized) {
                sf::Vector2u newSize = window.getSize();
                newSize.x = desctopeSizeX * window.getSize().y / desctopeSizeY;
                window.setSize(newSize);
            }
        }
        // пауза
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            cave.stop();
            camera.setSize(sf::Vector2f(desctopeSizeX, desctopeSizeY));
            camera.setCenter(desctopeSizeX * 0.5, desctopeSizeY * 0.5);
            window.setView(camera);
            const char* menuStrings[] = {
                "back to game", 
                "back to the main menu",
                "save game",
                "settings",
                "qout"
            };
            Menu pauseMenu(sf::Vector2f((desctopeSizeX * 0.5) * 0.613, desctopeSizeY * 0.5), 60, menuStrings, 5);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::Resized) {
                        sf::Vector2u newSize = window.getSize();
                        newSize.x = desctopeSizeX * window.getSize().y / desctopeSizeY;
                        window.setSize(newSize);
                    }
                }
                mouseX = sf::Mouse::getPosition(window).x * desctopeSizeX / window.getSize().x;
                mouseY = sf::Mouse::getPosition(window).y * desctopeSizeY / window.getSize().y;

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

                window.clear();

                int count = pauseMenu.draw(&window); // если кнопка нажата, то вернёт её номер, если нет, то -1
                if (count != -1) {
                    if (pressedBtn.getStatus() != pressedBtn.Playing)
                        pressedBtn.play();

                    if (count == 0)
                        goto gamePlay;
                    else if (count == 1) 
                        goto MainMenu;
                    else if (count == 2)
                        player.save();
                    else if (count == 3)
                        settings(&window);
                    else if (count == 4)
                        return 0;
                }

                window.display();
            }
        }

        char** map = maps[player.numlvl].map;
        player.move(map);

        camera.setCenter((player.x + playerHalfX) * scale, (player.y + playerHalfY) * scale);
        window.setView(camera);

        window.clear(); 
        // отрисовка карты
        char y = player.y - camera.getSize().y * 0.01;
        if (y < 0) y = 0;
        for (y; y < player.y + camera.getSize().y && y < maps[player.numlvl].sizeY; y++) {
            char x = player.x - camera.getSize().x * 0.01;
            if (x < 0) x = 0;
            for (x; x < player.y + camera.getSize().x && x < maps[player.numlvl].sizeX; x++)  {
                walls.setPosition(x * scale, y * scale);
                walls.setTextureRect(sf::IntRect(16 * map[y][x], 0, 16, 16));
                window.draw(walls);
            }
        }
        for (uint8_t i = 0; i < maps[player.numlvl].toolsCount; i++)
            maps[player.numlvl].tools[i].draw(&window);
        window.draw(player.sprite);

        // отрисовка света
        for (uint8_t i = 0; i < maps[player.numlvl].lightsCount; i++)
            maps[player.numlvl].lights[i].draw(&window, map);
        // отрисовка эффекта
        effect.setFillColor(sf::Color(0, 0, 0, (player.stress - 1) * 255 * 0.333));
        effect.setPosition(
            camera.getCenter().x - camera.getSize().x * 0.5, 
            camera.getCenter().y - camera.getSize().y * 0.5
        );
        window.draw(effect);

        // шкала стресса
        stress.draw(&window);

        // здоровье
        heart.setPosition(
            camera.getCenter().x + camera.getSize().x * 0.5 - 35 * 5, 
            camera.getCenter().y - camera.getSize().y * 0.5
        );
        heart.setTextureRect(sf::IntRect(0, 0, 7, 7));
        for (uint8_t i = 0; i < 5; i++) {
            if (i == player.hp) 
                heart.setTextureRect(sf::IntRect(7, 0, 7, 7));
            window.draw(heart);
            heart.move(35, 0);
        }

        // отрисовка света от игрока (если есть)
        if (player.lampTimer > 0) {
            player.ray.setFillColor(sf::Color(255, 255, 255, player.lampTimer * 50 / 600));
            player.ray.setPoint(0, sf::Vector2f((player.x + playerHalfX) * scale, (player.y + playerHalfY) * scale));
            sf::Vector2f prevPoint(player.x + playerHalfX, player.y + playerHalfY);

            for (float angle = 0; angle < 3.141 * 2; angle += 0.02) {
                sf::Vector2f rayPos = sf::Vector2f(player.x + playerHalfX, player.y + playerHalfY);
                sf::Vector2f rayMov(cosf(angle) * 0.02, sinf(angle) * 0.02);
                for (float i = 0; i < 2; i += 0.02) {
                    rayPos.x += rayMov.x;
                    rayPos.y += rayMov.y;
                    if (map[(int)rayPos.y][(int)rayPos.x] <= hardBlock) 
                        break;
                }
                player.ray.setPoint(1, sf::Vector2f(prevPoint.x * scale, prevPoint.y * scale));
                player.ray.setPoint(2, sf::Vector2f(rayPos.x * scale, rayPos.y * scale));
                prevPoint = rayPos;
                window.draw(player.ray);
            }
            player.lampTimer--;
        }

        // отрисовка текста табличек
        for (float x = -1; x < 1.5; x += 0.5) {
            for (float y = -0.5; y < 1; y += 0.5) {
                char sumbol = map[(int)(player.y + playerSizeY * y)][(int)(player.x + playerSizeX * x)];
                if (sumbol >= tables && sumbol < (tables + 4)) {
                    dialogText.setString(maps[player.numlvl].texts[sumbol - tables]);
                    dialogText.setPosition(
                        camera.getCenter().x - camera.getSize().x * 0.5, 
                        camera.getCenter().y + camera.getSize().y * 0.5 - 70
                    );
                    window.draw(dialogText);
                }
            }
        }
        // переход между уровнями
        if (map[(int)player.y][(int)player.x] == 17) {
            if (player.numlvl < maxLvls) {
                player.numlvl++;
                goto updateGame;
            }
        }
        else if (map[(int)player.y][(int)player.x] == 18) {
            if (player.numlvl > 0) {
                player.numlvl--;
                goto updateGame;
            }
        }

        window.display();
    }
    return 0;
}