#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Something you can see.
/// </summary>
class Drawable {
public:
	Drawable();
	Drawable(const int sizeX, const int sizeY);

	/// <summary>
	/// We can't make const because we have to write to sprite and window.
	/// The whole thing also cant be const because the inherited will need to make changes.
	/// </summary>
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) = 0;

	int getSizeX() const;
	int getSizeY() const;

protected:
	int sizeX{}, sizeY{};
};