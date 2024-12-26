#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

Menu::Menu() = default;

Menu::Menu(const sf::Font& font, const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture) {  
    firstMenuOpen = true;
    
    backgroundSprite.setTexture(backgroundTexture);

    playButtonSprite.setTexture(buttonTexture);
    quitButtonSprite.setTexture(buttonTexture);

    applyGlobalScale(backgroundSprite);
    applyGlobalScale(playButtonSprite);
    applyGlobalScale(quitButtonSprite);

    quitButton = { 160, 100, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Quit" };

    applyTextBranding(titleText, font);
    applyTextBranding(scoreText, font);

    //titleText.setString("HIGHWAY HURRY"); // use some to upper method.
    titleText.setString(makeUppercase(TITLE));
    titleText.setCharacterSize(250);

    quitButton.centerAll();
    quitButton.position.yComponent += quitButton.getSizeY() + 15;
    // depends on the bool.

    centerText(titleText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 225);

    applyTextBranding(debugInstructions, font);

    debugInstructions.setPosition(15, SCREEN_HEIGHT - 70);

    debugInstructions.setString("Tip : press [P] if the button doesn't work.");
    
    debugInstructions.setCharacterSize(40);

    playButton = { 160, 100, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play" };

    playButton.centerAll();
}

/// <summary>
/// Make the changes required for the second menu version.
/// Dont repeat if already second.
/// ARE WE ALLOWED TO USE GET METHOD ?
/// </summary>
void Menu::refresh(const Score& score, const Scoreboard& scoreboard, const sf::Font& font) {
    print("Opening menu.");
    
    scoreText.setString(scoreboard.getMenuString(score));
    
    // we dont have to do this over stuff.
    if (!firstMenuOpen) { return; }
    
    titleText.setString("GAME OVER"); // use some to upper method.
    
    //playButtonSprite.setScale(playButtonSprite.getScale().y * 2, playButtonSprite.getScale().y);
    playButtonSprite.setScale(20, 10);

    //scoreText.setString(scoreboard.getMenuString(score));
    scoreText.setCharacterSize(100);

    // is window.getsize() allowed ???? we can also just define and width and height somewhere and fix this whole skibiidi.
    centerText(scoreText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250);
    centerText(titleText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 425);

    // in the future i could make this button different that's why construvtor here.
    playButton = { 160, 100, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play Again" };
    playButton.centerAll();

    firstMenuOpen = false;
}

int Menu::update(sf::RenderWindow& window) {
    unsigned int result = 0;
    
    window.draw(backgroundSprite);

    playButton.draw(window, playButtonSprite);

    if (!firstMenuOpen) {
        window.draw(scoreText);

        quitButton.draw(window, quitButtonSprite);

        if (quitButton.getIsClicked()) {
            print("quitButton.");
            //window.close();
            result = 2;
        }
    }

    window.draw(titleText);

    if (playButton.getIsClicked() || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) {
        print("playButton.");
        result =  1;
    }

    if (firstMenuOpen) { window.draw(debugInstructions); }

    return result;
}