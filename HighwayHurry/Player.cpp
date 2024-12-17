#include "Player.h"
#include <iostream>
#include "Utils.h"
#include "Environment.h"
#include "MathUtils.h"
#include "Game.h"

Player::Player() = default;

Player::Player(const sf::Sprite& const sprite) : Entity{ sprite } {
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

void Player::move(const Time& const time) {
	Vector3 input = calculateMovement();
	
	Vector3 movement = input;
	movement.multiply(acceleration);

	rigidbody.addAcceleraton(movement);

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

	/*if (rigidbody.position.yComponent < 0)
	{ 
		rigidbody.position.yComponent = 0;
		rigidbody.velocity.yComponent = 0;
	}*/

	if (rigidbody.position.xComponent > rigidbody.getMaxX())
	{ 
		rigidbody.position.xComponent = rigidbody.getMaxX();
		rigidbody.velocity.xComponent = 0;
	}

	/*if (rigidbody.position.yComponent > maxY)
	{ 
		rigidbody.position.yComponent = maxY;
		rigidbody.velocity.yComponent = 0;
	}*/
}

void Player::doCounterMovement(float fixedInterval, Vector3 movement) {
	Vector3 counterMovement = rigidbody.velocity;

	counterMovement.normalize();
	counterMovement.remove(movement);

	counterMovement.multiply(-1 * acceleration * counterMovementMult * fixedInterval);

	/*if (counterMovement.magnitude > velocity.magnitude && velocity.magnitude != 0f) {
		counterMovement = -velocity;*/

	float velMag = rigidbody.velocity.calculateMagnitude();

	if (velMag != 0 && counterMovement.calculateMagnitude() > velMag)
	{
		counterMovement = rigidbody.velocity;
		counterMovement.multiply(-1);
	}

	rigidbody.addVelocity(counterMovement);
}

bool Player::checkCollision(Score& score, Obstacle& obstacle, const Time& const time) const {
	float leniency = 0.75f; // so we have negative leniency.
	
	//bool hasCollision = checkCircleTouch(rigidbody.position, obstacle.getPosition(), sizeX / 2.0f, obstacle.getSizeX() / 2.0f);
	//bool hasCollision = rigidbody.position.calculateDistanceTo(obstacle.getPosition()) <= sizeX * leniency;
	bool hasCollision = checkCircleTouch(rigidbody.position, obstacle.getPosition(), leniency * sizeX / 2, leniency * obstacle.getSizeX() / 2);

	if (hasCollision) 
	{ 
		obstacle.reset(time);

		return score.Damage(1);
	}

	return false;
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

void Player::draw(sf::RenderWindow& const window, sf::Sprite& const sprite) {
	sprite.setColor(sf::Color::White);
	
	/*Vector3 roundPos(rigidbody.position);
	roundPos.round(10);*/
	
	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);
	
	window.draw(sprite);
}