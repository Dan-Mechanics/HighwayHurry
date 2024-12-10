#pragma once
#include "Entity.h"
#include "Rigidbody.h"

class Car : public Entity {
public:
	Car();
	Car(const sf::RenderWindow& const window, const sf::Sprite& const sprite);

protected:
	//float topSpeed{};
	int minY{}, maxY{};
	int minX{}, maxX{};

	/// <summary>
	/// Might need to put this in public in future.
	/// </summary>
	Rigidbody rigidbody{};
};

