#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include "Score.h"

class Scoreboard {
public:
	Scoreboard();
	Scoreboard(const sf::Font& font);

	void draw(sf::RenderWindow& window, Score& score);
	void setGameString(sf::String& string, const Score& score) const;
	sf::String getMenuString(const Score& score) const;

private:
	sf::Text text{};
	sf::String string{};
};

