#include "Obstacle.h"
#include <iostream>
#include "Utils.h"
#include "Environment.h"
//#include "Rigidbody.h" // for global var ?? not required i gues

Obstacle::Obstacle(sf::RenderWindow& window, sf::Sprite& sprite, Score& score) : Car{ window, sprite }, score{score}
{
	minX += ENVIRONMENT_MARGIN;
	maxX -= ENVIRONMENT_MARGIN;
	
	// this could be in Enity.
	//maxX = window.getSize().x - sizeX;
	maxY = screenHeight; // this is important because that means it disappears off the screen ish.
	//color = randomColor();
	//rigidbody.velocity.yComponent = fallingSpeed + randomInclusive(-250, 250); // ish.
	ResetPosition();
}

void Obstacle::ResetPosition()
{
	//rigidbody.velocity.yComponent = fallingSpeed + randomInclusive(-fallingSpeedVariance, fallingSpeedVariance);
	color = randomColor();

	rigidbody.velocity.setAll (
		0, // x
		fallingSpeed + randomInclusive(-fallingSpeedVariance, fallingSpeedVariance), // y
		0 // z
	);

	rigidbody.position.setAll (
		randomInclusive(minX, maxX), // x
		randomInclusive(highestSpawnPoint, -sizeY), // y
		0 // z
	);
}

Vector3 Obstacle::getPosition()
{
	return rigidbody.position;
}

void Obstacle::move(Time& time)
{
	//rigidbody.addAcceleraton(gravity, time);
	//gravity.yComponent += 0.1f;
	rigidbody.limitVelocity(fallingSpeed);

	rigidbody.process(time);

	// constrain.
	if (rigidbody.position.xComponent < 0)
	{
		rigidbody.position.xComponent = 0;
		rigidbody.velocity.xComponent = 0;

		//acceleration.xComponent = abs(acceleration.xComponent);
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

		//acceleration.xComponent = -abs(acceleration.xComponent);
	}

	if (rigidbody.position.yComponent > maxY)
	{
		ResetPosition();
		score.AddScore(1);
		// if we get here that means we did not hit this car.
	}
}

void Obstacle::draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setColor(color);

	/*Vector3 roundPos(rigidbody.position);
	roundPos.round(10);*/

	sprite.setPosition(rigidbody.position.xComponent, rigidbody.position.yComponent);
	//sprite.setPosition(roundPos.xComponent, roundPos.yComponent);


	window.draw(sprite);
}