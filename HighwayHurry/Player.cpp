#include "Player.h"
#include <iostream>
#include "Utils.h"
#include "Environment.h"
#include "MathUtils.h"
#include "Game.h"

Player::Player() = default;

Player::Player(const sf::Sprite& sprite) : Entity{ sprite } {
	auto maxX = SCREEN_WIDTH - sizeX;
	auto maxY = SCREEN_HEIGHT - sizeY;
	auto minX = 0;
	auto minY = 0;

	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;

	// maybe we just need to give the rigidbody the sizeX and SizeY and the margins and thenwe good.
	// in ieder geval kan ik dit optimizen.
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
	if (rigidbody.position.xComponent < rigidbody.getMinX())
	{ 
		rigidbody.position.xComponent = rigidbody.getMinX();
		rigidbody.velocity.xComponent = 0;
	}

	if (rigidbody.position.xComponent > rigidbody.getMaxX())
	{ 
		rigidbody.position.xComponent = rigidbody.getMaxX();
		rigidbody.velocity.xComponent = 0;
	}

	// Technically, these aren't necessary but they're here just in case.

	if (rigidbody.position.yComponent < rigidbody.getMinY())
	{
		rigidbody.position.yComponent = rigidbody.getMinY();
		rigidbody.velocity.yComponent = 0;
	}

	if (rigidbody.position.yComponent > rigidbody.getMaxY())
	{ 
		rigidbody.position.yComponent = rigidbody.getMaxY();
		rigidbody.velocity.yComponent = 0;
	}
}

/// <summary>
/// Aka doFriction()
/// </summary>
void Player::doCounterMovement(float fixedInterval, Vector3 movement) {
	Vector3 counterMovement = rigidbody.velocity;

	counterMovement.normalize();
	counterMovement.remove(movement);

	counterMovement.multiply(-1 * movementForceScalar * counterMovementMult * fixedInterval);

	/*if (counterMovement.magnitude > velocity.magnitude && velocity.magnitude != 0f) {
		counterMovement = -velocity;*/

	float velMag = rigidbody.velocity.calculateMagnitude();

	if (velMag != 0 && counterMovement.calculateMagnitude() > velMag)
	{
		counterMovement = rigidbody.velocity;
		counterMovement.multiply(-1);
	}

	// but if this is too cool for you.
	//rigidbody.addVelocity(counterMovement);

	// convert to force.
	counterMovement.multiply(rigidbody.mass / fixedInterval);
	rigidbody.addForce(counterMovement);
}

bool Player::checkCollision(const Obstacle& obstacle) const {
	return checkCircleTouch(rigidbody.position, obstacle.getPosition(), collisionLeniancy * sizeX / 2, collisionLeniancy * obstacle.getSizeX() / 2);
}


// should be referecne.
Vector3 Player::calculateMovement() const {
	Vector3 movement { };
	
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
	{
		movement.yComponent--;
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
	{
		movement.xComponent--;
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
	{
		movement.yComponent++;
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
	{
		movement.xComponent++;
	}

	movement.normalize();

	return movement;
}

void Player::draw(sf::RenderWindow& window, sf::Sprite& sprite) {
	sprite.setColor(sf::Color::White);
	
	/*Vector3 roundPos(rigidbody.position);
	roundPos.round(10);*/
	
	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);
	
	window.draw(sprite);
}