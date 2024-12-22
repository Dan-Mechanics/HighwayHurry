#pragma once
#include "Entity.h"
#include "Rigidbody.h"
#include "Score.h"

/// <summary>
/// Might rename to just Obstacle. ObstacleCar? Falling obstacle.
/// </summary>
class Obstacle : public Entity {
public:
	Obstacle();
	Obstacle(const sf::Sprite& sprite, Score& score);
	void reset(const Time& time);

	unsigned int getSprite() const;
	Vector3 getPosition() const;
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;
	virtual void move(const Time& time, Score& score) override;

private:
	float downwardImpactForce = 1200;
	int downwardImpactForceVariance = 250;
	int constantForceVariance = 250;
	int highestSpawnPoint = -1080;
	unsigned int spriteIndex{};
	Rigidbody rigidbody{};
	Vector3 constantForce{};
	sf::Color color = sf::Color::White;
};

