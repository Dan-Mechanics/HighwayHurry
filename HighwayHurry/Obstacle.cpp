#include "Obstacle.h"
#include <iostream>
#include "MathUtils.h"
#include "Utils.h"
#include "Environment.h"
#include "Game.h"

Obstacle::Obstacle() = default;

Obstacle::Obstacle(const sf::Sprite& sprite, Score& score) :
	Entity{ sprite } {
	
	int maxX = SCREEN_WIDTH - sizeX;
	int maxY = SCREEN_HEIGHT;
	int minX = 0;
	int minY = 0;

	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;

	rigidbody = { 1, maxX, maxY, minX, minY };
}

void Obstacle::reset(const Time& time) {
	color = randomColor();

	// if u wanna know why not fast car look here :
	spriteIndex = randomInclusive(0, 1);
	rigidbody.mass = spriteIndex * -0.35f + 1.45f;

	rigidbody.stopInPlace();

	Vector3 force{ 0, downwardImpactForce + randomInclusive(-downwardImpactForceVariance, downwardImpactForceVariance), 0 };
	force.divide(time.fixedInterval);

	rigidbody.addForce(force);

	rigidbody.position.setAll (
		randomInclusive(rigidbody.getMinX(), rigidbody.getMaxX()), // x
		randomInclusive(highestSpawnPoint, -sizeY), // y
		0 // z
	);

	constantForce.setAll(randomInclusive(-constantForceVariance, constantForceVariance), 0, 0);
}

unsigned int Obstacle::getSprite() const {
	return spriteIndex;
}

Vector3 Obstacle::getPosition() const {
	return rigidbody.position;
}

void Obstacle::draw(sf::RenderWindow& window, sf::Sprite& sprite) {
	sprite.setColor(color);

	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);

	window.draw(sprite);
}

/// <summary>
/// We have to do this because otherwise we cant have a default thing.
/// </summary>
void Obstacle::move(const Time& time) {
	rigidbody.addForce(constantForce);

	rigidbody.process(time);
}

void Obstacle::constrain(const Time& time, Score& score) {
	if (rigidbody.position.xComponent < rigidbody.getMinX()) {
		rigidbody.position.xComponent = rigidbody.getMinX();
		rigidbody.velocity.xComponent = 0;
	}


	if (rigidbody.position.xComponent > rigidbody.getMaxX()) {
		rigidbody.position.xComponent = rigidbody.getMaxX();
		rigidbody.velocity.xComponent = 0;
	}

	if (rigidbody.position.yComponent > rigidbody.getMaxY()) {
		reset(time);
		score.AddScore(1);
		// if we get here that means we did not hit this car.
	}
}