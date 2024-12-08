#include "Environment.h"
#include "Utils.h"

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

Environment::Environment(sf::RenderWindow& window, sf::Sprite& sprite) : Entity{window, sprite }
{
    if (screenHeight != sizeY || screenWidth != sizeX) { print("Why tho ?"); }

    position.yComponent = -screenHeight;
}

void Environment::draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
    Vector3 roundPos(position);
    //roundPos.round(10);
    
    sprite.setPosition(roundPos.xComponent, roundPos.yComponent);

    window.draw(sprite);
}

void Environment::move(Time& time) {
    position.yComponent += forwardSpeed * time.fixedInterval;

    if (position.yComponent >= 0) { position.yComponent = -1080; }
}