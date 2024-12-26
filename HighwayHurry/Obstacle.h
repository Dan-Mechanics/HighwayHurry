#pragma once
#include "Entity.h"
#include "Rigidbody.h"
#include "Score.h"

/// <summary>
/// Represents a car for the player to avoid.
/// </summary>
class Obstacle : public Entity {
public:
	Obstacle();
	Obstacle(const int sizeX, const int sizeY, Score& score);
	void reset(const Time& time);

	unsigned int getSpriteIndex() const;
	Vector3 getPosition() const;
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;
	void constrain(const Time& time, Score& score);

private:
	//float downwardImpactForce = 1200;
	float drag = 0.0001f;
	//int downwardImpactForceVariance = 250;
	//int constantForceVariance = 250;
	int highestSpawnPoint = -1080;
	unsigned int spriteIndex{};
	Rigidbody rigidbody{};

	Vector3 driveForce {0, 100000, 0};
	sf::Color color = sf::Color::White;
};