#include "Entity.h"
#include <SFML/Graphics.hpp>

//Entity::Entity() = default;

Entity::Entity() = default;

Entity::Entity(sf::RenderWindow & window, sf::Sprite & sprite) : Drawable{ window, sprite } { }

//Entity::~Entity() = default;
