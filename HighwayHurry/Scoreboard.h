#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include "Score.h"

/// <summary>
/// REFACTOR !!!
/// </summary>
class Scoreboard {
public:
	Scoreboard();
	Scoreboard(sf::Font& font);
	void draw(sf::RenderWindow& window, Score& score);
	void setGameString(sf::String& string, Score& score);
	sf::String getMenuString(Score& score);

private:
	sf::Text text{};
	sf::String string{};
};

