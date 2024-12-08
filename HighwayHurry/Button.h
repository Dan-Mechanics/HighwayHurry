#pragma once
#include "Entity.h"

class Button : public Entity {
public:
	Vector3 position{};
	
	/// <summary>
	/// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
	/// </summary>
	Button();
	Button(sf::RenderWindow& window, sf::Sprite& sprite, Vector3 position, sf::Color normalColor,
		sf::Color hoveringColor, sf::Font& font, std::string textOnButton);
	//virtual ~Button();
   
	bool getIsHovering();
	bool getIsClicked();
	void centerY();
	void centerX();
	void centerAll();

	// Inherited via Entity.

	/// <summary>
	/// Also does hovering logic.
	/// </summary>
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(Time& time) override;

private:
	bool isHovering{};
	bool isClicked{};

	sf::Color hoveringColor{};
	sf::Color normalColor{};
	sf::Text text{};
};

