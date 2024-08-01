#pragma once
#include "Animate.h"
#include "light.h"
#include "lamp.h"

// тестовая локация

char* testMap[] = {
    new char[10] {0, 0, 0, 0, 0, 0, 19, 16, 20, 0},
    new char[10] {1, 2, 2, 2, 2, 2, 14, 17, 15, 3},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {4, 24, 24, 24, 24, 24, 24, 24, 24, 4},
    new char[10] {8, 2, 2, 2, 2, 2, 2, 2, 2, 7},
};
const char* testMapTexts[] = {
    "win!",
    "Hello. This is a beta test, version 0.1",
    "text3",
    "text4",
};
// свет
Light testMapLights[] = {
	Light(sf::Vector2f(3, 2.1), 2.5, &torch, testMap)
};