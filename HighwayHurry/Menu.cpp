#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "ScoreHUD.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

const sf::Color BUTTON_HOVERING_COLOR = { 98, 106, 120 };

Menu::Menu() = default;

Menu::Menu(const sf::Font& font, const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture) {  
    print("Opening menu.");
    
    firstMenuOpen = true;
    
    backgroundSprite.setTexture(backgroundTexture);

    playButtonSprite.setTexture(buttonTexture);
    quitButtonSprite.setTexture(buttonTexture);

    applyGlobalScale(backgroundSprite);
    applyGlobalScale(playButtonSprite);
    applyGlobalScale(quitButtonSprite);

    quitButton = { 160, 100, BUTTON_HOVERING_COLOR, font, "Quit" };

    applyTextBranding(titleText, font);
    applyTextBranding(scoreText, font);

    titleText.setString(makeUppercase(TITLE));
    titleText.setCharacterSize(250);

    quitButton.centerAll();
    quitButton.position.yComponent += quitButton.getSizeY() + 15;

    centerText(titleText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 225);

    applyTextBranding(debugInstructions, font);

    debugInstructions.setPosition(15, SCREEN_HEIGHT - 70);

    debugInstructions.setString("Tip : press [P] if the button doesn't work.");
    
    debugInstructions.setCharacterSize(40);

    playButton = { 160, 100, BUTTON_HOVERING_COLOR, font, "Play" };

    playButton.centerAll();
}

/// <summary>
/// Make the changes required for the second menu version.
/// Don't repeat if already second.
/// </summary>
void Menu::refresh(const Score& score, const ScoreHUD& scoreHUD, const sf::Font& font) {
    print("Refresh @ menu.");
    
    scoreText.setString(scoreHUD.getMenuString(score));
    
    // We don't have to do this again.
    if (!firstMenuOpen) { return; }
    
    titleText.setString("GAME OVER"); 

    playButtonSprite.setScale(20, 10);

    scoreText.setCharacterSize(100);

    centerText(scoreText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250);
    centerText(titleText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 425);

    playButton = { 320, 100, BUTTON_HOVERING_COLOR, font, "Play Again" };
    playButton.centerAll();

    firstMenuOpen = false;
}

FrameResult Menu::draw(sf::RenderWindow& window) {
    auto frameResult = FrameResult::NEXT_FRAME;
    
    window.draw(backgroundSprite);

    playButton.draw(window, playButtonSprite);

    if (!firstMenuOpen) {
        window.draw(scoreText);

        quitButton.draw(window, quitButtonSprite);

        if (quitButton.getIsClicked()) {
            frameResult = FrameResult::CLOSE_GAME;
        }
    }

    window.draw(titleText);

    if (playButton.getIsClicked() || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) {
        frameResult = FrameResult::NEXT_SCENE;
    }

    if (firstMenuOpen) { 
        window.draw(debugInstructions);
    }

    return frameResult;
}