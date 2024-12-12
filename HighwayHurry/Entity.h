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
	Entity(const sf::RenderWindow& const window, const sf::Sprite& const sprite);
	//virtual ~Entity(); ???

	virtual void move(const Time& time) = 0; 
};

