#include "Player.h"
#include <iostream>
#include "Utils.h"
#include "Environment.h"
#include "MathUtils.h"
#include "Game.h"

const float PLAYER_FORWARD_SPEED = 3500;

// IDEA: you can maybe get more score points in the middle of the road because its more dangerous there ?

Player::Player() = default;

Player::Player(const int sizeX, const int sizeY) : Entity{ sizeX, sizeY } {
	auto maxX = SCREEN_WIDTH - sizeX;
	auto maxY = SCREEN_HEIGHT - sizeY;
	auto minX = 0;
	auto minY = 0;

	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;

	// Give rigidbody mass + collision bounds.
	rigidbody = { 1, maxX, maxY, minX, minY };

	reset();
}

void Player::reset() {
	rigidbody.position.setAll(rigidbody.getMaxX() * 0.5f, rigidbody.getMaxY() - 10, 0);
	rigidbody.resetAll();
}

void Player::move(const Time& time) {
	Vector3 input = calculateMovement();
	
	Vector3 movement = input;
	movement.multiply(movementForceScalar);

	rigidbody.addForce(movement);

	// We do it after because that feels more responsive.
	doCounterMovement(time.fixedInterval, input);

	rigidbody.limitVelocity(topSpeed);

	rigidbody.process(time);

	// constrain.
	if (rigidbody.position.xComponent < rigidbody.getMinX()) {
		rigidbody.position.xComponent = rigidbody.getMinX();
		rigidbody.velocity.xComponent = 0;
	}

	if (rigidbody.position.xComponent > rigidbody.getMaxX()) {
		rigidbody.position.xComponent = rigidbody.getMaxX();
		rigidbody.velocity.xComponent = 0;
	}

	// Technically, these aren't necessary but they're here just in case / for future.
	// I could add a bool for that.

	if (rigidbody.position.yComponent < rigidbody.getMinY()) {
		rigidbody.position.yComponent = rigidbody.getMinY();
		rigidbody.velocity.yComponent = 0;
	}

	if (rigidbody.position.yComponent > rigidbody.getMaxY()) {
		rigidbody.position.yComponent = rigidbody.getMaxY();
		rigidbody.velocity.yComponent = 0;
	}
}

/// <summary>
/// Aka doFriction()
/// </summary>
void Player::doCounterMovement(float fixedInterval, Vector3 movement) {
	// Because we want to resist the velocity.
	Vector3 counterMovement = rigidbody.velocity;

	counterMovement.normalize();
	counterMovement.remove(movement);

	// Invert, scale, etc.
	counterMovement.multiply(-1 * movementForceScalar * counterMovementMult * fixedInterval);

	float velMag = rigidbody.velocity.calculateMagnitude();

	if (velMag != 0 && counterMovement.calculateMagnitude() > velMag) {
		counterMovement = rigidbody.velocity;

		// Invert velocity.
		counterMovement.invert();
	}

	// Convert to force because forces.
	counterMovement.multiply(rigidbody.getMass() / fixedInterval);
	rigidbody.addForce(counterMovement);
}

void Player::checkCollisionWithObstacle(Obstacle& obstacle, Score& score) const {
	bool hit = checkCircleIntersection(rigidbody.position, obstacle.getPosition(),
		collisionLeniancy * sizeX / 2, collisionLeniancy * obstacle.getSizeX() / 2);
	
	if (hit) { 
		obstacle.reset();
		score.damage(1);
	}
}

/// <summary>
/// Questionable if we wanna make a "new" ( not really ) Vector3 here.
/// We only take A and D keys or arrows so the player can only
/// move left to right.
/// </summary>
Vector3 Player::calculateMovement() const {
	Vector3 movement { };
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
	{
		movement.xComponent--;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
	{
		movement.xComponent++;
	}

	movement.normalize();

	return movement;
}

void Player::draw(sf::RenderWindow& window, sf::Sprite& sprite) {
	sprite.setColor(sf::Color::White);
	
	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);
	
	window.draw(sprite);
}