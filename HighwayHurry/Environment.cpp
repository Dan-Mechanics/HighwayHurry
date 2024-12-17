#include "Environment.h"
#include "Utils.h"
#include "Game.h"

const int ENVIRONMENT_MARGIN = 150;

//Environment::Environment(Position position), position{ position } { }

//void Environment::draw()
//{
//    window.clear(sf::Color::Blue);
//
//    sprite.setPosition(position.xComponent, position.yComponent);
//
//    window.draw(sprite);
//}

Environment::Environment() = default;

Environment::Environment(const sf::Sprite& const sprite) : Entity{ sprite } {
    if (SCREEN_HEIGHT != sizeY || SCREEN_WIDTH != sizeX) { print("Why tho ?"); }

    position.yComponent = -SCREEN_HEIGHT;
}

void Environment::draw(sf::RenderWindow& const window, sf::Sprite& const sprite) {
    Vector3 roundPos(position);
    //roundPos.round(10);
    
    sprite.setPosition(roundPos.xComponent, roundPos.yComponent);

    window.draw(sprite);
}

void Environment::move(const Time& const time) {
    position.yComponent += forwardSpeed * time.fixedInterval;

    if (position.yComponent >= 0) { position.yComponent = -1080; }
}