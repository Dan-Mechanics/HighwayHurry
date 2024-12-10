#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Button.h"
#include "Scoreboard.h"

class Menu {
public:
	Menu();

	bool open(bool start, Score& score, Scoreboard& scoreboard, sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sprite& quitButtonSprite, sf::Sprite& playButtonSprite) const;
};