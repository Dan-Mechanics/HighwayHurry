#include "Entity.h"
#include <SFML/Graphics.hpp>

//Entity::Entity() = default;

Entity::Entity() = default;

Entity::Entity(const sf::RenderWindow& const window, const sf::Sprite& const sprite) : Drawable{ window, sprite } { }

//Entity::~Entity() = default;
