#include "Entity.h"
#include <SFML/Graphics.hpp>

//Entity::Entity() = default;

Entity::Entity() = default;

Entity::Entity(const sf::Sprite& sprite) : Drawable { sprite } { }