#pragma once
#include <iostream>
#include "Vector3.h"
#include <SFML/Graphics.hpp>
#include "MathUtils.h"

/// https://www.youtube.com/watch?v=Fqn4pSRH6Ec
enum class Scene { MENU_SCENE = 0, GAME_SCENE = 1 };
enum class FrameResult { NEXT_FRAME = 0, NEXT_SCENE = 1, CLOSE_GAME = 2 };

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

/// <summary>
/// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
/// https://www.dafont.com/gamer-2.font?text=hEllLo+this+is+ScoreSCORE+%3A+100
/// </summary>
void applyTextBranding(sf::Text& text, const sf::Font& font);

/// <summary>
/// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
/// </summary>
sf::String makeUppercase(sf::String str);