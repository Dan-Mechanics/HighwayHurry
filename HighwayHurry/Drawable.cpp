// https://www.sfml-dev.org/tutorials/2.6/graphics-sprite.php

#include "Drawable.h"
#include "Utils.h"

Drawable::Drawable() = default;

Drawable::Drawable(sf::RenderWindow& window, sf::Sprite& sprite) {
    screenWidth = window.getSize().x;
    screenHeight = window.getSize().y;

    sizeX = sprite.getTexture()->getSize().x * (int)sprite.getScale().x;
    sizeY = sprite.getTexture()->getSize().y * (int)sprite.getScale().y;
}

int Drawable::getSizeX()
{
    return sizeX;
}

int Drawable::getSizeY()
{
    return sizeY;
}
