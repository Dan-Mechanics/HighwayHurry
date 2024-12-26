#pragma once
#include "Entity.h"
#include "Vector3.h"

extern const int ENVIRONMENT_MARGIN;

class Environment : public Entity {
public:
	// i think i should be able to edit this thats why in public.
	//float forwardSpeed = 3500;

	Environment();
	Environment(const int sizeX, const int sizeY);

	// Inherited via Entity.
	virtual void draw(sf::RenderWindow& window, sf::Sprite& sprite) override;
	virtual void move(const Time& time) override;
private:
	Vector3 position{};
	// because the environment has to move.
};

