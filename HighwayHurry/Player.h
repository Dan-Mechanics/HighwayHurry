#pragma once
#include "Entity.h"
#include "Rigidbody.h"
#include "Car.h"
#include "Score.h"
#include "Obstacle.h"

class Player : public Car {
public:
	Player();
	Player(const sf::RenderWindow& window, const sf::Sprite& sprite);

	bool checkCollision(Score& score, Obstacle& obstacle) const;

	// Inherited via Car.
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;

private:
	float topSpeed = 1000;
	float acceleration = 7500;
	float counterMovementMult = 0.195f;

	Vector3 calculateMovement() const;
	void doCounterMovement(float fixedInterval, Vector3 movement);

};

