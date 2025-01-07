#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
#include <iostream>
#include <sstream>

class ScoreHUD {
public:
	ScoreHUD();
	ScoreHUD(const sf::Font& font);

	void draw(sf::RenderWindow& window, const Score& score);

	/// <summary>
	/// https://stackoverflow.com/questions/2462951/c-equivalent-of-stringbuffer-stringbuilder :
	/// "The C++ way would be to use std::stringstream or just plain string concatenations. C++ strings are mutable so the performance considerations of concatenation are less of a concern."
	/// https://www.geeksforgeeks.org/stringstream-c-applications/
	/// https://stackoverflow.com/questions/662976/how-do-i-convert-from-stringstream-to-string-in-c
	/// </summary>
	sf::String getGameString(const Score& score) const;

	/// <summary>
	/// https://stackoverflow.com/questions/2462951/c-equivalent-of-stringbuffer-stringbuilder
	/// </summary>
	sf::String getMenuString(const Score& score) const;

private:
	sf::Text gameText{};
};