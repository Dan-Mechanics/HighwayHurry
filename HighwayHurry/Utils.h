#pragma once
#include <iostream>
#include "Vector3.h"
#include <SFML/Graphics.hpp>

void print(const std::string value);
void print(const int value);
void print(const float value);

int randomInclusive(const int min, const int max);

bool checkExitCondition(sf::Event& event, sf::RenderWindow& window);

sf::Color randomColor();

void applyGlobalScale(sf::Sprite& sprite);

/// <summary>
/// https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
/// </summary>
void centerText(sf::Text& text, const int x, const int y);

/// <summary>
/// https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
/// </summary>
void centerText(sf::Text& text, const sf::RenderWindow& window);

int roundToInt(const float f);

void applyTextBranding(sf::Text& text, const sf::Font& font);

bool checkCircleTouch(const Vector3 a, const Vector3 b, const float aR, const float bR);
