#include "Vector3.h"
#include "MathUtils.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

void print(const std::string value) {
	std::cout << " > " << value << std::endl;
}

void print(const int value) {
	std::cout << " > " << value << std::endl;
}

void print(const float value) {
	std::cout << " > " << value << std::endl;
}

bool checkExitCondition(sf::Event& event, sf::RenderWindow& window) {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)) {

			return true;
		}
	}

	return false;
}

sf::Color randomColor() {
	return sf::Color{ (sf::Uint8)randomInclusive(0, 255), (sf::Uint8)randomInclusive(0, 255), (sf::Uint8)randomInclusive(0, 255) };
}

void applyGlobalScale(sf::Sprite& const sprite) {
	sprite.setScale(10, 10);
}

void centerText(sf::Text& text, const int x, const int y) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(roundToInt(textRect.left + textRect.width / 2), roundToInt(textRect.top + textRect.height / 2));
	//text.setOrigin(round(textRect.left + textRect.width / 2), round(textRect.top + maxHeight / 2));

	text.setPosition(x, y);
}

void centerText(sf::Text& text, const sf::RenderWindow& window) {
	centerText(text, window.getSize().x / 2, window.getSize().y / 2);
}

/// <summary>
/// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
/// https://www.dafont.com/gamer-2.font?text=hEllLo+this+is+ScoreSCORE+%3A+100
/// </summary>
void applyTextBranding(sf::Text& text, const sf::Font& font) {
	text.setFont(font);
	text.setCharacterSize(80); 
	//text.setFillColor(sf::Color::Black);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
}

/// <summary>
/// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
/// </summary>
sf::String makeUppercase(sf::String str) {
	for (auto& c : str) c = toupper(c);

	return str;
}
