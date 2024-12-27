#pragma once
#include "Drawable.h"
#include "Vector3.h"
#include "Time.h"
#include "Score.h"

/// <summary>
/// Something that moves and you can see.
/// </summary>
class Entity : public Drawable {
public:
	Entity();
	Entity(const int sizeX, const int sizeY);

	virtual void move(const Time& time) = 0; 
};