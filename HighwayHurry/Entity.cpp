#include "Entity.h"
#include <SFML/Graphics.hpp>

//Entity::Entity() = default;

Entity::Entity() = default;

Entity::Entity(const sf::Sprite& const sprite) : Drawable { sprite } { }

void Entity::move(const Time & time, Score& const score) {

}

//Entity::~Entity() = default;
