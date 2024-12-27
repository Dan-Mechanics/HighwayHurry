#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Game.h"

Button::Button() = default;

Button::Button(const int sizeX, const int sizeY, const Vector3 position, const sf::Color normalColor,
    const sf::Color hoveringColor, const sf::Font& font, const std::string writing) : Drawable{ sizeX, sizeY }, position{ position },
    normalColor{ normalColor }, hoveringColor{ hoveringColor }, writing{ writing } {

    applyTextBranding(text, font);
    text.setString(writing);
}

Button::Button(const int sizeX, const int sizeY, const sf::Color hoveringColor, const sf::Font & font, const std::string writing) : Drawable{ sizeX, sizeY }, position{ Vector3{ } },
normalColor{ sf::Color::White }, hoveringColor{ hoveringColor }, writing{ writing } {

    applyTextBranding(text, font);
    text.setString(writing);
}

bool Button::getIsHovering() const {

    return isHovering;
}

bool Button::getIsClicked() const {
    return isClicked;
}

void Button::centerY() {
    position.yComponent = (SCREEN_HEIGHT - sizeY) / 2.0f;
}

void Button::centerX() {
    position.xComponent = (SCREEN_WIDTH - sizeX) / 2.0f;
}

void Button::centerAll() {
    centerX();
    centerY();
}

void Button::draw(sf::RenderWindow& window, sf::Sprite& sprite) {
    auto mouseX = sf::Mouse::getPosition().x;
    auto mouseY = sf::Mouse::getPosition().y;

    // !performance ?
    auto xMin = roundToInt(position.xComponent); // yes, we will downcast.
    auto yMin = roundToInt(position.yComponent);
    auto xMax = xMin + sizeX;
    auto yMax = yMin + sizeY;

    // we gotta see if thing is within thing.

    // we know pos is topleft.

    // otherwise random memory !!
    // technically this is not allowed.
    isHovering = 
        mouseX >= xMin && mouseY >= yMin && 
        mouseX <= xMax && mouseY <= yMax &&
        window.hasFocus();

    isClicked = isHovering && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isClicked) { print(" |BUTTON| " + writing); }

    sprite.setColor(isHovering ? hoveringColor : normalColor);
    text.setFillColor(isHovering ? sf::Color::White : sf::Color::Black);

    sprite.setPosition(position.xComponent, position.yComponent);

    centerText(text, position.xComponent + sizeX / 2.0f, position.yComponent + sizeY / 2.0f);

    window.draw(sprite);
    window.draw(text);
}

//void Button::move(const Time& time) {
//    // future: add animation for hovering.
//    // for now: center text on button.
//}
