#include "Car.h"

Car::Car() = default;

Car::Car(sf::RenderWindow & window, sf::Sprite & sprite) : Entity{ window, sprite } 
{
	minX = 0;
	minY = 0;
	
	maxX = screenWidth - sizeX;
	maxY = screenHeight - sizeY;
}