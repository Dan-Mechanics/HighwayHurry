#include "Car.h"

Car::Car() = default;

Car::Car(const sf::RenderWindow& const window, const sf::Sprite& const sprite) : Entity{ window, sprite } {
	minX = 0;
	minY = 0;
	
	maxX = screenWidth - sizeX;
	maxY = screenHeight - sizeY;
}