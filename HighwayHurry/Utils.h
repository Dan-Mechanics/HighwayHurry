#pragma once
#include <iostream>
#include "Vector3.h"
#include <SFML/Graphics.hpp>
#include "MathUtils.h"

void print(const std::string value);
void print(const int value);
void print(const float value);

bool checkExitCondition(sf::Event& event, sf::RenderWindow& window);

sf::Color randomColor();

void applyGlobalScale(sf::Sprite& sprite);

/// <summary>
/// https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
/// </summary>
void centerText(sf::Text& text, const float x, const float y);

/// <summary>
/// https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
/// </summary>
void centerText(sf::Text& text);

void applyTextBranding(sf::Text& text, const sf::Font& font);

sf::String makeUppercase(sf::String str);