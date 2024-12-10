#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

Menu::Menu() = default;

Menu::Menu(Score & score, Scoreboard & scoreboard, sf::Font & font, sf::RenderWindow & window, sf::Sprite & backgroundSprite, sf::Sprite & quitButtonSprite, sf::Sprite & playButtonSprite)
{   
    quitButton = { window, quitButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Quit" };
    quitButton.centerAll();
    quitButton.position.yComponent += quitButton.getSizeY() + 15;

    applyTextBranding(titleText, font);
    applyTextBranding(scoreText, font);
    applyTextBranding(failSafe, font);

   // titleText.setString(startOfGame ? "HIGHWAY HURRY" : "GAME OVER"); // use some to upper method.
    titleText.setCharacterSize(250);
}

void Menu::setup(sf::RenderWindow& window, const bool first, const Score& const score, const Scoreboard& const scoreboard, const sf::Font& const font)
{
    this->first = first;
    
    titleText.setString(first ? "HIGHWAY HURRY" : "GAME OVER"); // use some to upper method.
    
    playAgainButton = { window, playAgainButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, first ? "Play" : "Play Again" };
    playAgainButton.centerAll();

    if (first)
    {
        centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 225);

        failSafe.setPosition(15, window.getSize().y - 70);
        failSafe.setString("Tip : press [P] if the button doesn't work.");
        failSafe.setCharacterSize(40);
    }
    else
    {
        playAgainButtonSprite.setScale(20, 10);

        playAgainButton = { window, playAgainButtonSprite, Vector3{ }, sf::Color::White, { 98, 106, 120 }, font, "Play Again" };
        playAgainButton.centerAll();

        scoreText.setString(scoreboard.getMenuString(score));
        scoreText.setCharacterSize(100);

        centerText(scoreText, window.getSize().x / 2, window.getSize().y / 2 - 250);
        centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 425);
    }
}

int Menu::update(sf::RenderWindow& window) {

    // failsave.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) { return 0; }

    window.clear(sf::Color::Magenta);

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
            return 1;
        }
    }

    window.draw(titleText);

    if (playAgainButton.getIsClicked())
    {
        print("playAgainButton.");
        return 0;
    }

    if (first) { window.draw(failSafe); }

    window.display();

    print("Closing menu.");

    return 0;
}