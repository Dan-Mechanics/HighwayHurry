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
	void reset();

	int getSpriteIndex() const;
	Vector3 getPosition() const;
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;
	void constrain(const Time& time, Score& score);

private:
	float getMassFromSpriteIndex(int spriteIndex) const;

	float airDrag = 0.00002f;
	float driveForceVariance = 500;
	float steerForceVariance = 40000;
	int highestSpawnPoint = -1080 * 3;
	int spriteIndex{};
	Rigidbody rigidbody{};

	Vector3 steerForce{};
	Vector3 driveForce{0, -200000, 0};
	sf::Color color = sf::Color::White;
};