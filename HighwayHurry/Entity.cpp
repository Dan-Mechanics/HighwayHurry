#include "Entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity() = default;

Entity::Entity(const int sizeX, const int sizeY) : Drawable { sizeX, sizeY } { }