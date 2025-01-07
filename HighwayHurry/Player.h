#pragma once
#include "Entity.h"
#include "Rigidbody.h"
#include "Score.h"
#include "Obstacle.h"

extern const float PLAYER_FORWARD_SPEED;

class Player : public Entity {
public:
	Player();
	Player(const int sizeX, const int sizeY);

	void reset();
	void checkCollisionWithObstacle(Obstacle& obstacle, Score& score) const;

	// Inherited via Car.
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;

private:
	float topSpeed = 1000;
	float movementForceScalar = 7500;
	float counterMovementMult = 0.25f;
	float collisionLeniancy = 0.75f;
	Rigidbody rigidbody{};

	Vector3 calculateMovement() const;
	void doCounterMovement(float fixedInterval, Vector3 movement);
};