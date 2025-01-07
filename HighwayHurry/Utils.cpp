#include "Vector3.h"
#include "MathUtils.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"

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

void applyGlobalScale(sf::Sprite& sprite) {
	sprite.setScale(10, 10);
}

void centerText(sf::Text& text, const float x, const float y) {
	sf::FloatRect textRect = text.getLocalBounds();

	text.setOrigin(round(textRect.left + textRect.width / 2), round(textRect.top + textRect.height / 2));
	text.setPosition(x, y);
}

void centerText(sf::Text& text) {
	centerText(text, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
}

void applyTextBranding(sf::Text& text, const sf::Font& font) {
	text.setFont(font);
	text.setCharacterSize(80); 
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
}

sf::String makeUppercase(sf::String str) {
	for (auto& c : str) c = toupper(c);

	return str;
}