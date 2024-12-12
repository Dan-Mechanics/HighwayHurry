#pragma once
#include "Entity.h"
#include "Rigidbody.h"
#include "Car.h"
#include "Score.h"

/// <summary>
/// Might rename to just Obstacle. ObstacleCar? Falling obstacle.
/// </summary>
class Obstacle : public Car {
public:
	//Obstacle();
	// we cant have a default construcor because we have a reference to score.
	// and references cannot be null pointer. 
	Obstacle(const sf::RenderWindow& const window, const sf::Sprite& const sprite, Score& score);
	void reset();
	Vector3 getPosition() const;
	//virtual ~ObstacleCar();

	// Inherited via Car.
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;

private:
	float fallingSpeed = 1200;
	//float spawnMargins = 245;
	int fallingSpeedVariance = 150;
	int highestSpawnPoint = -1080;

	Vector3 accel{};
	sf::Color color = sf::Color::White;
	Score& score;
};

