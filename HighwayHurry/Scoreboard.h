#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include "Score.h"

class Scoreboard {
public:
	Scoreboard();
	Scoreboard(const sf::Font& const font);
	void draw(sf::RenderWindow& window, Score& score);
	void setGameString(sf::String& string, const Score& const score);
	sf::String getMenuString(const Score& const score) const;

private:
	sf::Text text{};
	sf::String string{};
};

