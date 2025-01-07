#pragma once
#include "Entity.h"
#include "Vector3.h"

extern const int ENVIRONMENT_MARGIN;

class Environment : public Entity {
public:
	Environment();
	Environment(const int sizeX, const int sizeY);

	/// <summary>
	/// The question is wether or not we want to round everything to the nearest pixel.
	/// </summary>
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;

private:
	/// <summary>
	/// Because the environment has to move.
	/// </summary>
	Vector3 position{};
};