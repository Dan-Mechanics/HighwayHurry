#include "Environment.h"
#include "Utils.h"
#include "Game.h"

const int ENVIRONMENT_MARGIN = 150;

Environment::Environment() = default;

Environment::Environment(const sf::Sprite& sprite) : Entity{ sprite } {
    if (SCREEN_HEIGHT != sizeY || SCREEN_WIDTH != sizeX) { print("Why tho ?"); }

    position.yComponent = -SCREEN_HEIGHT;
}

/// <summary>
/// The question is wether or not we want to round everything to the nearest pixel.
/// </summary>
void Environment::draw(sf::RenderWindow& window, sf::Sprite& sprite) {
    sprite.setPosition(position.xComponent, position.yComponent);

    window.draw(sprite);
}

void Environment::move(const Time& time) {
    position.yComponent += forwardSpeed * time.fixedInterval;

    if (position.yComponent >= 0) { position.yComponent = -1080; }
}