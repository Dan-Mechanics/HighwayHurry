#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Abstract ( interface-like ) implementation in order to have polymorphism std::vector
/// holding all drawables. --> Something you can see.
/// https://www.geeksforgeeks.org/delete-and-free-in-cpp/
/// </summary>
class Drawable {
public:
	Drawable(); // we cannot have this because sprite and window must be assigned.
	Drawable(sf::RenderWindow& window, sf::Sprite& sprite);
	//virtual ~Drawable();

	int getSizeX();
	int getSizeY();

	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) = 0;

protected:
	int sizeX{}, sizeY{};
	int screenWidth{}, screenHeight{};
};

