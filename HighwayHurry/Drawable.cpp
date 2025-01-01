#include "Drawable.h"
#include "Utils.h"

Drawable::Drawable() = default;

Drawable::Drawable(const int sizeX, const int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
}

int Drawable::getSizeX() const {
    return sizeX;
}

int Drawable::getSizeY() const {
    return sizeY;
}