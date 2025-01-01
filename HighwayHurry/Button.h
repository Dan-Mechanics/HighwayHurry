#pragma once
#include "Entity.h"

class Button : public Drawable {
public:
	Vector3 position{};
	
	/// <summary>
	/// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
	/// </summary>
	Button();
	Button(const int sizeX, const int sizeY, const Vector3 position, const sf::Color normalColor,
		const sf::Color hoveringColor, const sf::Font& font, const std::string writing);

	Button(const int sizeX, const int sizeY, const sf::Color hoveringColor, const sf::Font& font, const std::string writing);

	bool getIsHovering() const;
	bool getIsClicked() const;
	void centerY();
	void centerX();
	void centerAll();

	/// <summary>
	/// Also does hovering logic.
	/// </summary>
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;

private:
	bool isHovering{};
	bool isClicked{};

	sf::String writing{};
	sf::Color hoveringColor{};
	sf::Color normalColor{};
	sf::Text text{};
};