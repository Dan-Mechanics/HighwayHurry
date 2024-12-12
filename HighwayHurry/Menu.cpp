#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

Menu::Menu() = default;

Menu::Menu(const sf::RenderWindow& const window, const sf::Font& const font, const sf::Texture& const backgroundTexture, const sf::Texture& const buttonTexture) {  
    firstMenuOpen = true;
    
    backgroundSprite.setTexture(backgroundTexture);

    playButtonSprite.setTexture(buttonTexture);
    quitButtonSprite.setTexture(buttonTexture);

    applyGlobalScale(backgroundSprite);
    applyGlobalScale(playButtonSprite);
    applyGlobalScale(quitButtonSprite);

    quitButton = { window, quitButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Quit" };

    applyTextBranding(titleText, font);
    applyTextBranding(scoreText, font);

    //titleText.setString("HIGHWAY HURRY"); // use some to upper method.
    titleText.setString(makeUppercase(TITLE));
    titleText.setCharacterSize(250);

    quitButton.centerAll();
    quitButton.position.yComponent += quitButton.getSizeY() + 15;
    // depends on the bool.

    centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 225);

    applyTextBranding(debugInstructions, font);

    debugInstructions.setPosition(15, window.getSize().y - 70);

    debugInstructions.setString("Tip : press [P] if the button doesn't work.");

    debugInstructions.setCharacterSize(40);

    playButton = { window, playButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play" };

    playButton.centerAll();
}

/// <summary>
/// Make the changes required for the second menu version.
/// Dont repeat if already second.
/// ARE WE ALLOWED TO USE GET METHOD ?
/// </summary>
void Menu::refresh(const sf::RenderWindow& const window, const Score& const score, const Scoreboard& const scoreboard, const sf::Font& const font) {
    scoreText.setString(scoreboard.getMenuString(score));
    
    // we dont have to do this over stuff.
    if (!firstMenuOpen) { return; }
    
    titleText.setString("GAME OVER"); // use some to upper method.
    
    playButtonSprite.setScale(playButtonSprite.getScale().y * 2, playButtonSprite.getScale().y);

    //scoreText.setString(scoreboard.getMenuString(score));
    scoreText.setCharacterSize(100);

    // is window.getsize() allowed ???? we can also just define and width and height somewhere and fix this whole skibiidi.
    centerText(scoreText, window.getSize().x / 2, window.getSize().y / 2 - 250);
    centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 425);

    playButton = { window, playButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play Again" };
    playButton.centerAll();

    firstMenuOpen = false;
}

/// <summary>
/// Use int for this instead !!!
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
unsigned int Menu::update(sf::RenderWindow& const window) {
    window.draw(backgroundSprite);

    playButton.draw(window, playButtonSprite);

    if (!firstMenuOpen) {
        window.draw(scoreText);

        quitButton.draw(window, quitButtonSprite);

        if (quitButton.getIsClicked())
        {
            print("quitButton.");
            //window.close();
            return 2;
        }
    }

    window.draw(titleText);

    if (playButton.getIsClicked() || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P))
    {
        print("playButton.");
        return 1;
    }

    if (firstMenuOpen) { window.draw(debugInstructions); }

    return 0;
}