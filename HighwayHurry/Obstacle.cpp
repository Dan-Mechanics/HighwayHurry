#include "Obstacle.h"
#include <iostream>
#include "MathUtils.h"
#include "Utils.h"
#include "Environment.h"
#include "Game.h"

Obstacle::Obstacle() = default;

Obstacle::Obstacle(const int sizeX, const int sizeY, Score& score) :
	Entity{ sizeX, sizeY } {
	
	int maxX = SCREEN_WIDTH - sizeX;
	const int maxY = SCREEN_HEIGHT;
	int minX = 0;
	const int minY = 0;

	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;

	rigidbody = { 1, maxX, maxY, minX, minY };

	rigidbody.addVelocity(Vector3{ 0, -PLAYER_FORWARD_SPEED * 2.5f, 0 });
}

void Obstacle::reset() {
	color = randomColor();

	// This is where we dictate which cars exist basically.
	spriteIndex = randomInclusive(0, 2);
	rigidbody.setMass(getMassFromSpriteIndex(spriteIndex));

	rigidbody.velocity.xComponent = 0;

	rigidbody.position.setAll (
		randomInclusive(rigidbody.getMinX(), rigidbody.getMaxX()), // x
		randomInclusive(highestSpawnPoint, -sizeY), // y
		0 // z
	);

	steerForce.setAll(randomInclusive(-steerForceVariance, steerForceVariance), 0, 0);
	driveForce.yComponent += randomInclusive(-driveForceVariance, driveForceVariance);
}

int Obstacle::getSpriteIndex() const {
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
	rigidbody.velocity.yComponent -= PLAYER_FORWARD_SPEED;
	
	rigidbody.addForce(driveForce);
	rigidbody.addForce(steerForce);

	// https://www1.grc.nasa.gov/wp-content/uploads/drageq.gif
	rigidbody.addForce(rigidbody.velocity * rigidbody.velocity.calculateMagnitude() * 0.5f * airDrag);

	// Because the motion is relative to the player because the player is "stationary."
	rigidbody.velocity.yComponent += PLAYER_FORWARD_SPEED;

	rigidbody.process(time);
}

/// <summary>
/// Where the "miss" collision takes place.
/// </summary>
void Obstacle::constrain(const Time& time, Score& score) {
	if (rigidbody.position.xComponent < rigidbody.getMinX()) {
		rigidbody.position.xComponent = rigidbody.getMinX();
		rigidbody.velocity.xComponent = 0;
		steerForce.multiply(-1);
	}

	if (rigidbody.position.xComponent > rigidbody.getMaxX()) {
		rigidbody.position.xComponent = rigidbody.getMaxX();
		rigidbody.velocity.xComponent = 0;
		steerForce.multiply(-1);
	}

	if (rigidbody.position.yComponent > rigidbody.getMaxY()) {
		reset(time);
		score.addScore(1);
		// if we get here that means we did not hit this car.
	}
}

float Obstacle::getMassFromSpriteIndex(int spriteIndex) const {
	return spriteIndex * -0.19f + 1.45f;
}