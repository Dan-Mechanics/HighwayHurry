#pragma once
#include "Entity.h"

class Button : public Entity {
public:
	Vector3 position{};
	
	/// <summary>
	/// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
	/// </summary>
	Button();
	Button(const sf::RenderWindow& window, const sf::Sprite& sprite, const Vector3 position, const sf::Color normalColor,
		const sf::Color hoveringColor, const sf::Font& font, const std::string textOnButton);
	//virtual ~Button();
   
	bool getIsHovering() const;
	bool getIsClicked() const;
	void centerY();
	void centerX();
	void centerAll();

	// Inherited via Entity.

	/// <summary>
	/// Also does hovering logic.
	/// </summary>
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;
	// we cant make this const because reference. 

private:
	bool isHovering{};
	bool isClicked{};

	sf::Color hoveringColor{};
	sf::Color normalColor{};
	sf::Text text{};
};

