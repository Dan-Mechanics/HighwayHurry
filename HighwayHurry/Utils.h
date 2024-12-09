#pragma once
#include <iostream>
#include "Vector3.h"
#include <SFML/Graphics.hpp>

// If there is a place to implement math functions for the fun of it then it would be here.

//void crossProductNonAlloc(Vector3& target, Vector3 a, Vector3 b);
//void sumNonAlloc(Vector3& target, Vector3 a, Vector3 b);
//Vector3 sumAlloc(Vector3 a, Vector3 b);

void print(std::string value);
void print(int value);
void print(float value);

int randomInclusive(int min, int max);

bool checkExitCondition(sf::Event& event, sf::RenderWindow& window);

sf::Color randomColor();

void applyGlobalScale(sf::Sprite& sprite);

/// <summary>
/// https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
/// </summary>
void centerText(sf::Text& text, int x, int y);

/// <summary>
/// https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
/// </summary>
void centerText(sf::Text& text, sf::Window& window);

int roundToInt(float f);

void applyTextBranding(sf::Text& text, sf::Font& font);

bool checkCircleTouch(Vector3 a, Vector3 b, float aR, float bR);
