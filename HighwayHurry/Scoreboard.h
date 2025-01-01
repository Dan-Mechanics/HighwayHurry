#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
#include <iostream>

class Scoreboard {
public:
	Scoreboard();
	Scoreboard(const sf::Font& font);

	void draw(sf::RenderWindow& window, const Score& score);
	sf::String getGameString(const Score& score) const;
	sf::String getMenuString(const Score& score) const;

private:
	sf::Text text{};

	sf::String gameString{};
	sf::String menuString{};
};