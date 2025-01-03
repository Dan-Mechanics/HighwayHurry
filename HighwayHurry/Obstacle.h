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

	float airDrag = 0.005f;
	float driveForceVariance = 800;
	float steerForceVariance = 3000;
	int highestSpawnPoint = -3240;
	int spriteIndex{};
	Rigidbody rigidbody{};

	Vector3 steerForce{};
	Vector3 driveForce{0, -23500, 0};
	sf::Color color = sf::Color::White;
};