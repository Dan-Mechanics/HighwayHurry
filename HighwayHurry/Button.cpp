#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Utils.h"

Button::Button() = default;

Button::Button(const sf::RenderWindow & window, const sf::Sprite & sprite, const Vector3 position, const sf::Color normalColor, const sf::Color hoveringColor, const sf::Font & font, const std::string textOnButton)
{
    applyTextBranding(text, font);

    text.setString(textOnButton);
}

//Button::Button(sf::RenderWindow & window, sf::Sprite & sprite, Vector3 position, sf::Color normalColor, sf::Color hoveringColor, sf::Font & font, std::string textOnButton) :
//    Entity{ window, sprite, }, position{ position }, normalColor{ normalColor }, hoveringColor{ hoveringColor } {
//
//    applyTextBranding(text, font);
//
//    text.setString(textOnButton);
//}

bool Button::getIsHovering() const {

    return isHovering;
}

bool Button::getIsClicked() const {
    return isClicked;
}

void Button::centerY() {
    position.yComponent = (screenHeight - sizeY) / 2.0f;
}

void Button::centerX() {
    position.xComponent = (screenWidth - sizeX) / 2.0f;
}

void Button::centerAll() {
    centerX();
    centerY();
}

void Button::draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
    int mouseX = sf::Mouse::getPosition().x;
    int mouseY = sf::Mouse::getPosition().y;

    //int xMin = (int)position.xComponent; // yes, we will downcast.
    //int yMin = (int)position.yComponent;

    // !performance ?
    int xMin = roundToInt(position.xComponent); // yes, we will downcast.
    int yMin = roundToInt(position.yComponent);

    int xMax = xMin + sizeX;
    int yMax = yMin + sizeY;

    // we gotta see if thing is within thing.

    // we know pos is topleft.

    // otherwise random memory !!
    // technically this is not allowed.
    isHovering = 
        mouseX >= xMin && mouseY >= yMin && 
        mouseX <= xMax && mouseY <= yMax &&
        window.hasFocus();

    isClicked = isHovering && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    sprite.setColor(isHovering ? hoveringColor : normalColor);
    text.setFillColor(isHovering ? sf::Color::White : sf::Color::Black);

    sprite.setPosition(position.xComponent, position.yComponent);

    centerText(text, roundToInt(position.xComponent) + sizeX / 2, roundToInt(position.yComponent) + sizeY / 2);
    //centerText(text, window);

    window.draw(sprite);
    window.draw(text);
}

void Button::move(const Time& time) {
    // future: add animation for hovering.
    // for now: center text on button.
}
