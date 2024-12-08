#pragma once
#include "Drawable.h"
#include "Vector3.h"
#include "Time.h"

/// <summary>
/// Something that moves and you can see.
/// </summary>
class Entity : public Drawable {
public:
	//Position position;
	Entity();
	Entity(sf::RenderWindow& window, sf::Sprite& sprite);
	//virtual ~Entity(); ???

	virtual void move(Time& time) = 0; 
};

