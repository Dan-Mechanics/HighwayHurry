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

	// Inherited via Entity.
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;

private:
	float topSpeed = 1000;
	float movementForceScalar = 7500;
	float counterMovementMult = 0.25f;
	float collisionLeniancy = 0.75f;
	Rigidbody rigidbody{};

	/// <summary>
	/// Questionable if we wanna make a "new" ( not really ) Vector3 here.
	/// We only take A and D keys or arrows so the player can only
	/// move left to right.
	/// </summary>
	Vector3 calculateMovement() const;

	/// <summary>
	/// Does "friction" for the player.
	/// </summary>
	void doCounterMovement(float fixedInterval, Vector3 movement);
};