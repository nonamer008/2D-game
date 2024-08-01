#pragma once
#include "Animate.h"
#include "light.h"
#include "lamp.h"

char* secondLoc[] = {
    new char[10] {1, 2, 2, 2, 2, 13, 2, 2, 2, 3},
    new char[10] {4, 24, 24, 24, 24, 4, 27, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 12, 22, 22, 22, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {5, 2, 2, 2, 10, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {8, 2, 2, 2, 2, 2, 2, 2, 2, 7},
};
const char* secondLocTexts[] = {
    "thanks for playing!",
    "text2",
    "text3",
    "text4",
};
// свет
Light secondLocLights[] = {
    Light(sf::Vector2f(2, 1.1), 4, &torch, secondLoc)
};
// лампы
Lamp secondLocLamps[] = {
    Lamp(sf::Vector2f(2, 7))
};