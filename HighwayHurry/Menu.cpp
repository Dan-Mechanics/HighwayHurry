#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

Menu::Menu() = default;

Menu::Menu(Score & score, Scoreboard & scoreboard, sf::Font & font, sf::RenderWindow & window, sf::Sprite & backgroundSprite, sf::Sprite & quitButtonSprite, sf::Sprite & playButtonSprite)
{   
    //this->playAgainButton = playAgainButton;
    //this->quitButton = quitButton;
    
    first = true;

    //print("Opening menu.");

    this->backgroundSprite = backgroundSprite;
    this->playAgainButtonSprite = playButtonSprite;
    this->quitButtonSprite = quitButtonSprite;

    quitButton = { window, quitButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Quit" };

    applyTextBranding(titleText, font);
    applyTextBranding(scoreText, font);

    titleText.setString("HIGHWAY HURRY"); // use some to upper method.
    titleText.setCharacterSize(250);

    quitButton.centerAll();
    quitButton.position.yComponent += quitButton.getSizeY() + 15;
    // depends on the bool.

    centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 225);

    applyTextBranding(failSafe, font);

    failSafe.setPosition(15, window.getSize().y - 70);

    failSafe.setString("Tip : press [P] if the button doesn't work.");

    failSafe.setCharacterSize(40);

    playAgainButton = { window, playButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play" };

    playAgainButton.centerAll();
}

/// <summary>
/// Make the changes required for the second menu version.
/// Dont repeat if already second.
/// </summary>
void Menu::refresh(sf::RenderWindow& window, const Score& const score, const Scoreboard& const scoreboard, const sf::Font& const font)
{
    //if (!first) { return; }
    first = false;

    titleText.setString("GAME OVER"); // use some to upper method.

    // hardcoded yes i know.
    playAgainButtonSprite.setScale(20, 10);

    scoreText.setString(scoreboard.getMenuString(score));
    scoreText.setCharacterSize(100);

    centerText(scoreText, window.getSize().x / 2, window.getSize().y / 2 - 250);
    centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 425);

    playAgainButton = { window, playAgainButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play Again" };

    playAgainButton.centerAll();
}

std::string Menu::update(sf::RenderWindow& window) {

    // failsave.
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) { return 1; }

    //window.clear(sf::Color::Magenta);

    // does cpp have base.blabla(); ??

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


    //print("Closing menu.");

    return "next frame";
}