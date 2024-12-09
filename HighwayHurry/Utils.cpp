#include "Vector3.h"
#include "Utils.h"
#include <iostream>
#include <random>

//void crossProductNonAlloc(Vector3& target, Vector3 a, Vector3 b)
//{
//	target.setAll(
//		a.yComponent * b.zComponent + a.zComponent * b.yComponent,
//		a.zComponent * b.xComponent + a.xComponent * b.zComponent,
//		a.xComponent * b.yComponent + a.yComponent * b.xComponent
//	);
//}
//
//void sumNonAlloc(Vector3& target, Vector3 a, Vector3 b)
//{
//	/*target.xComponent = a.xComponent + b.xComponent;
//	target.yComponent = a.yComponent + b.yComponent;
//	target.zComponent = a.zComponent + b.zComponent;*/
//
//	target.setAll(
//		a.xComponent + b.xComponent,
//		a.yComponent + b.yComponent,
//		a.zComponent + b.zComponent
//	);
//
//	// TODO: use setall. VV
//}
//
//Vector3 sumAlloc(Vector3 a, Vector3 b)
//{
//	return Vector3(
//		a.xComponent + b.xComponent,
//		a.yComponent + b.yComponent,
//		a.zComponent + b.zComponent
//	);
//}

// you could maybe implement vector maht library here.
// ask rosa for code feedback

void print(std::string value)
{
	std::cout << " > " << value << std::endl;
}

void print(int value)
{
	std::cout << " > " << value << std::endl;
}

void print(float value)
{
	std::cout << " > " << value << std::endl;
}

/// <summary>
/// https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
/// </summary>
int randomInclusive(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

bool checkExitCondition(sf::Event& event)
{
	return event.type == sf::Event::Closed ||
		(event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Escape);
}

sf::Color randomColor()
{
	return sf::Color{ (sf::Uint8)randomInclusive(0, 255), (sf::Uint8)randomInclusive(0, 255), (sf::Uint8)randomInclusive(0, 255) };
}

void applyGlobalScale(sf::Sprite& sprite) 
{
	sprite.setScale(10, 10);
}

void centerText(sf::Text& text, int x, int y)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(roundToInt(textRect.left + textRect.width / 2), roundToInt(textRect.top + textRect.height / 2));
	//text.setOrigin(round(textRect.left + textRect.width / 2), round(textRect.top + maxHeight / 2));

	text.setPosition(x, y);
}

void centerText(sf::Text& text, sf::Window& window)
{
	centerText(text, window.getSize().x / 2, window.getSize().y / 2);
}

int roundToInt(float f)
{
	//return (int)round(f);
	// idk.
	return round(f);
}

/// <summary>
/// https://www.sfml-dev.org/tutorials/2.6/graphics-text.php
/// https://www.dafont.com/gamer-2.font?text=hEllLo+this+is+ScoreSCORE+%3A+100
/// </summary>
void applyTextBranding(sf::Text& text, sf::Font& font)
{
	text.setFont(font);
	text.setCharacterSize(80); 
	//text.setFillColor(sf::Color::Black);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
}

bool checkCircleTouch(Vector3 a, Vector3 b, float aR, float bR)
{
	return a.calculateDistanceTo(b) <= aR + bR;
}
