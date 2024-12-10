#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Button.h"

int main() {
    const sf::String TITLE = "Highway Hurry";

    print(TITLE);

    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    const unsigned int FPS_CAP = 320;
    const int TIMESTEP = 64;
    const int MAX_LIVES = 5;

    // https://www.reddit.com/r/sfml/comments/oyms57/how_t
    // https://youtu.be/lFzpkvrscs4?si=9lYiXu4090IKJ1o1
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE,
        sf::Style::Fullscreen);

    window.setFramerateLimit(FPS_CAP);

    //////////////////////////////////////////////////////

    sf::Font font;
    if (!font.loadFromFile("Gamer.ttf"))
    {
        print("Gamer.ttf not found!");
    }

    Time time{ TIMESTEP };
    Score score{ MAX_LIVES };
    Scoreboard scoreBoard{ font };

    //////////////////////////////////////////////////////

    sf::Texture playerTexture;
    sf::Texture gameBackgroundTexture;
    sf::Texture obstacleTexture;

    if (!playerTexture.loadFromFile("player.png") ||
        !gameBackgroundTexture.loadFromFile("new_road.png") ||
        !obstacleTexture.loadFromFile("obstacle_car.png")) {
        print("texture not found!");
    }

    sf::Sprite playerSprite;
    sf::Sprite gameBackgroundSprite;
    sf::Sprite obstacleSprite;

    playerSprite.setTexture(playerTexture);
    gameBackgroundSprite.setTexture(gameBackgroundTexture);
    obstacleSprite.setTexture(obstacleTexture);

    gameBackgroundSprite.setTextureRect(sf::IntRect(0, 0,
        gameBackgroundTexture.getSize().x, gameBackgroundTexture.getSize().y * 2));

    gameBackgroundTexture.setRepeated(true);

    // smooth ?

    applyGlobalScale(playerSprite);
    applyGlobalScale(gameBackgroundSprite);
    applyGlobalScale(obstacleSprite);

    //////////////////////////////////////////////////////

    sf::Texture menuBackgroundTexture;
    sf::Texture buttonTexture;

    if (!menuBackgroundTexture.loadFromFile("new_menu.png") ||
        !buttonTexture.loadFromFile("button.png")) {
        print("texture not found!");
    }

    sf::Sprite menuBackgroundSprite;
    sf::Sprite playButtonSprite;
    sf::Sprite quitButtonSprite;

    menuBackgroundSprite.setTexture(menuBackgroundTexture);

    playButtonSprite.setTexture(buttonTexture);
    quitButtonSprite.setTexture(buttonTexture);

    applyGlobalScale(menuBackgroundSprite);
    applyGlobalScale(playButtonSprite);
    applyGlobalScale(quitButtonSprite);

    //////////////////////////////////////////////////////

    bool quit = false;
    bool showMenu = true;

    Menu menu{ score, scoreBoard, font, window, menuBackgroundSprite, quitButtonSprite, playButtonSprite };
    Game game{ window, score, time, playerSprite, gameBackgroundSprite, obstacleSprite, font };

    /*while (!quit) {

        quit = menu.update(window) != 0;
    }*/

    // what i also could have done is make another scripts menu.cpp game.cpp and gameover.cpp
    while (window.isOpen())
    {
        sf::Event event;

        if (checkExitCondition(event, window) || quit) {
            //quit = true;
            window.close();

            return 0;
        }

        window.clear(sf::Color::Magenta);

        std::string output = showMenu ? menu.update(window) : game.update(window, score, time);

        window.display();

        if (output == "quit") { quit = true; }
        else if (output == "next scene") 
        {
            showMenu = !showMenu;

            if (showMenu) 
            {
                menu.refresh(window, score, scoreBoard, font);
            }
            else
            {
                // we cant reset the score and time here because the menu need it .
                game.refresh(score, time);
            }
        }
        
    }



    //Game game{ };

    //// i think we have enough while loops here to make it work :^)
    //while (!quit) {

    //    quit = menu.open(first, score, scoreBoard, font, window, menuBackgroundSprite,
    //        quitButtonSprite, playButtonSprite);
    //    
    //    first = false;

    //    if (quit) { return 0; }

    //    quit = game.play(window, playerSprite, gameBackgroundSprite,
    //        obstacleSprite, score, time, scoreBoard);
    //}

    return 0;
}