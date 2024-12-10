#include "Menu.h"
#include "Time.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

Menu::Menu() = default;

/// <summary>
/// BIG WARNING: if the button is bugged,
/// then teacher can't play the game.
/// </summary>
bool Menu::open(bool startOfGame, Score & score, Scoreboard & scoreboard, sf::Font& font, sf::RenderWindow & window, sf::Sprite & backgroundSprite, sf::Sprite & quitButtonSprite, sf::Sprite & playButtonSprite) const {
    print("Opening menu.");

    Button quitButton(window, quitButtonSprite, Vector3(), sf::Color::White,
        sf::Color(98, 106, 120), font, "Quit");

    sf::Text titleText;
    sf::Text scoreText;

    applyTextBranding(titleText, font);
    applyTextBranding(scoreText, font);
    
    titleText.setString(startOfGame ? "HIGHWAY HURRY" : "GAME OVER"); // use some to upper method.
    titleText.setCharacterSize(250);

    quitButton.centerAll();
    quitButton.position.yComponent += quitButton.getSizeY() + 15;
    // depends on the bool.

    sf::Text failSave;

    if(startOfGame)
    {
        centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 225);

        applyTextBranding(failSave, font);

        failSave.setPosition(15, window.getSize().y - 70);

        failSave.setString("Tip : press [P] if the button doesn't work.");

        failSave.setCharacterSize(40);
    }
    else 
    {
        // hardcoded yes i know.
        playButtonSprite.setScale(20, 10);

        scoreText.setString(scoreboard.getMenuString(score));
        scoreText.setCharacterSize(100);

        centerText(scoreText, window.getSize().x / 2, window.getSize().y / 2 - 250);
        centerText(titleText, window.getSize().x / 2, window.getSize().y / 2 - 425);
    }

    // this placemetn is very importnat.
    Button playAgainButton(window, playButtonSprite, Vector3(), sf::Color::White,
        sf::Color(98, 106, 120), font, startOfGame ? "Play" : "Play Again");

    playAgainButton.centerAll();

    while (window.isOpen())
    {
        // failsave.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) { return false; }
        
        sf::Event event;
        if (checkExitCondition(event, window)) 
        {
            return true;
        }

        window.clear(sf::Color::Magenta);

        // does cpp have base.blabla(); ??

        window.draw(backgroundSprite);

        playAgainButton.draw(window, playButtonSprite);

        if (!startOfGame) {
            window.draw(scoreText);
            
            quitButton.draw(window, quitButtonSprite);

            if (quitButton.getIsClicked())
            {
                print("quitButton.");
                window.close();
                return true;
            }
        }

        window.draw(titleText);

        if (playAgainButton.getIsClicked())
        {
            print("playAgainButton.");
            return false;
        }

        if (startOfGame) { window.draw(failSave); }

        window.display();
    }

    print("Closing menu.");

    return false;
}