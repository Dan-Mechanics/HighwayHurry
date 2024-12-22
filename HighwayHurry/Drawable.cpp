// https://www.sfml-dev.org/tutorials/2.6/graphics-sprite.php

#include "Drawable.h"
#include "Utils.h"

Drawable::Drawable() = default;

Drawable::Drawable(const sf::Sprite& sprite) {
    sizeX = sprite.getTexture()->getSize().x *
        (int)sprite.getScale().x;
    sizeY = sprite.getTexture()->getSize().y * (int)sprite.getScale().y;
}

int Drawable::getSizeX() const {
    return sizeX;
}

int Drawable::getSizeY() const {
    return sizeY;
}
