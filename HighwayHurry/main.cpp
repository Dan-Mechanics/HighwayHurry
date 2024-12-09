#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Button.h"

int main()
{
    sf::String title = "Highway Hurry";

    print(title);

    int width = 1920;
    int height = 1080;
    unsigned int framerateLimit = 320;
    int timestep = 64;
    int maxLives = 5;

    // https://www.reddit.com/r/sfml/comments/oyms57/how_t
    // https://youtu.be/lFzpkvrscs4?si=9lYiXu4090IKJ1o1
    sf::RenderWindow window(sf::VideoMode(width, height), title,
        sf::Style::Fullscreen);

    window.setFramerateLimit(framerateLimit);

    //////////////////////////////////////////////////////

    sf::Font font;
    if (!font.loadFromFile("Gamer.ttf"))
    {
        print("Gamer.ttf not found!");
    }

    Time time{ timestep };
    Score score{ maxLives };
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

    Menu menu{ }; 
    
    quit = menu.open(true, score, scoreBoard, font, window, menuBackgroundSprite,
         quitButtonSprite, playButtonSprite);

    if (quit) { return 0; }

    Game game{ };

    // i think we have enough while loops here to make it work :^)
    while (!quit) {

        quit = game.play(window, playerSprite, gameBackgroundSprite,
            obstacleSprite, score, time, scoreBoard);

        if (quit) { return 0; }

        quit = menu.open(false, score, scoreBoard, font, window, menuBackgroundSprite,
            quitButtonSprite, playButtonSprite);
    }

    return 0;
}