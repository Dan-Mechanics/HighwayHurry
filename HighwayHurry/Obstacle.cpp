#include "Obstacle.h"
#include <iostream>
#include "MathUtils.h"
#include "Utils.h"
#include "Environment.h"
//#include "Rigidbody.h" // for global var ?? not required i gues

Obstacle::Obstacle(const sf::RenderWindow& const window, const sf::Sprite& const sprite, Score& score) : 
	Car{ window, sprite }, score{ score } {

	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;
	
	maxY = screenHeight;
}

void Obstacle::reset(const Time& const time) {
	color = randomColor();

	// if u wanna know why not fast car look here :
	spriteIndex = randomInclusive(0, 1);
	rigidbody.mass = spriteIndex * -0.35f + 1.45f;

	rigidbody.stopInPlace();

	Vector3 force{ 0, downwardImpactForce + randomInclusive(-downwardImpactForceVariance, downwardImpactForceVariance), 0 };
	force.divide(time.fixedInterval);

	rigidbody.addForce(force);

	rigidbody.position.setAll (
		randomInclusive(minX, maxX), // x
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

void Obstacle::move(const Time& const time) {
	rigidbody.addForce(constantForce);

	rigidbody.process(time);

	// constrain.
	if (rigidbody.position.xComponent < minX) {
		rigidbody.position.xComponent = minX;
		rigidbody.velocity.xComponent = 0;

		//acceleration.xComponent = abs(acceleration.xComponent);
	}

	/*if (rigidbody.position.yComponent < 0)
	{
		rigidbody.position.yComponent = 0;
		rigidbody.velocity.yComponent = 0;
	}*/

	if (rigidbody.position.xComponent > maxX) {
		rigidbody.position.xComponent = maxX;
		rigidbody.velocity.xComponent = 0;

		//acceleration.xComponent = -abs(acceleration.xComponent);
	}

	if (rigidbody.position.yComponent > maxY) {
		reset(time);
		score.AddScore(1);
		// if we get here that means we did not hit this car.
	}
}

void Obstacle::draw(sf::RenderWindow& const window, sf::Sprite& const sprite) {
	sprite.setColor(color);

	/*Vector3 roundPos(rigidbody.position);
	roundPos.round(10);*/

	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);
	//sprite.setPosition(roundPos.xComponent, roundPos.yComponent);


	window.draw(sprite);
}