#include "Player.h"
#include <iostream>
#include "Utils.h"
#include "Environment.h"

Player::Player() = default;

Player::Player(sf::RenderWindow& window, sf::Sprite& sprite) : Car{ window, sprite }
{
	rigidbody.position.setAll(maxX * 0.5f, maxY - 10, 0);

	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;
}

void Player::move(const Time& time)
{
	Vector3 input = calculateMovement();
	
	Vector3 movement = input;
	movement.multiply(acceleration);

	rigidbody.addAcceleraton(movement, time);

	// We do it after because that feels more responsive.
	doCounterMovement(time.fixedInterval, input);

	rigidbody.limitVelocity(topSpeed);

	rigidbody.process(time);

	// constrain.
	if (rigidbody.position.xComponent < minX)
	{ 
		rigidbody.position.xComponent = minX;
		rigidbody.velocity.xComponent = 0;
	}

	/*if (rigidbody.position.yComponent < 0)
	{ 
		rigidbody.position.yComponent = 0;
		rigidbody.velocity.yComponent = 0;
	}*/

	if (rigidbody.position.xComponent > maxX)
	{ 
		rigidbody.position.xComponent = maxX;
		rigidbody.velocity.xComponent = 0;
	}

	/*if (rigidbody.position.yComponent > maxY)
	{ 
		rigidbody.position.yComponent = maxY;
		rigidbody.velocity.yComponent = 0;
	}*/
}

void Player::doCounterMovement(float fixedInterval, Vector3 movement)
{
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

bool Player::checkCollision(Score& score, Obstacle& obstacle) const {
	float leniency = 0.75f; // so we have negative leniency.
	
	//bool hasCollision = checkCircleTouch(rigidbody.position, obstacle.getPosition(), sizeX / 2.0f, obstacle.getSizeX() / 2.0f);
	bool hasCollision = rigidbody.position.calculateDistanceTo(obstacle.getPosition()) <= sizeX * leniency;

	if (hasCollision) 
	{ 
		obstacle.ResetPosition();

		return score.Damage(1);
	}

	return false;
}


// should be referecne.
Vector3 Player::calculateMovement() const {
	Vector3 movement;
	
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

void Player::draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setColor(sf::Color::White);
	
	/*Vector3 roundPos(rigidbody.position);
	roundPos.round(10);*/
	
	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);
	
	window.draw(sprite);
}