#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

Menu::Menu() = default;

Menu::Menu(const sf::RenderWindow& const window, const sf::Font& const font, const sf::Texture& const backgroundTexture, const sf::Texture& const buttonTexture) {  
    first = true;
    
    backgroundSprite.setTexture(backgroundTexture);

    playAgainButtonSprite.setTexture(buttonTexture);
    quitButtonSprite.setTexture(buttonTexture);

    applyGlobalScale(backgroundSprite);
    applyGlobalScale(playAgainButtonSprite);
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

    applyTextBranding(failSafe, font);

    failSafe.setPosition(15, window.getSize().y - 70);

    failSafe.setString("Tip : press [P] if the button doesn't work.");

    failSafe.setCharacterSize(40);

    playAgainButton = { window, playAgainButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play" };

    playAgainButton.centerAll();
}

/// <summary>
/// Make the changes required for the second menu version.
/// Dont repeat if already second.
/// ARE WE ALLOWED TO USE GET METHOD ?
/// </summary>
void Menu::refresh(const sf::RenderWindow& const window, const Score& const score, const Scoreboard& const scoreboard, const sf::Font& const font) {
    scoreText.setString(scoreboard.getMenuString(score));
    
    // we dont have to do this over stuff.
    if (!first) { return; }
    
    titleText.setString("GAME OVER"); // use some to upper method.
    
    playAgainButtonSprite.setScale(playAgainButtonSprite.getScale().y * 2, playAgainButtonSprite.getScale().y);

    //scoreText.setString(scoreboard.getMenuString(score));
    scoreText.setCharacterSize(100);

    // is window.getsize() allowed ???? we can also just define and width and height somewhere and fix this whole skibiidi.
    centerText(scoreText, window.getSize().x / 2, window.getSize().y / 2 - 250);
    centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 425);

    playAgainButton = { window, playAgainButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play Again" };
    playAgainButton.centerAll();

    first = false;
}

/// <summary>
/// Use int for this instead !!!
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
std::string Menu::update(sf::RenderWindow& const window) {
    window.draw(backgroundSprite);

    playAgainButton.draw(window, playAgainButtonSprite);

    if (!first) {
        window.draw(scoreText);

        quitButton.draw(window, quitButtonSprite);

        if (quitButton.getIsClicked())
        {
            print("quitButton.");
            window.close();
            return "quit";
        }
    }

    window.draw(titleText);

    if (playAgainButton.getIsClicked() || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P))
    {
        print("playAgainButton.");
        return "next scene";
    }

    if (first) { window.draw(failSafe); }

    return "next frame";
}