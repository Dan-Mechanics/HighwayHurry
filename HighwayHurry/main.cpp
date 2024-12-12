#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Button.h"

/// <summary>
/// Make sprite conform to playersize and dont use getsize on sprite and window ??.
/// Do we have to upper method  for strings ?
/// also add vector operands and better math utils library ish.
/// </summary>
/// <returns></returns>
int main() {
    //const sf::String TITLE = "Highway Hurry";

    print(TITLE);

    // THIS THIS THIS
    // could make this global consts so we dont have to read from canvas and sprite
    // and besides we need to make the sprite adjust to player and not player adjust to sprite but whatever.

    const int WIDTH = 1920;
    const int HEIGHT = 1080; // --> make this global ?
    const unsigned int FPS_CAP = 320;
    const int TIMESTEP = 64;
    const int MAX_LIVES = 5;

    // https://www.reddit.com/r/sfml/comments/oyms57/how_t
    // https://youtu.be/lFzpkvrscs4?si=9lYiXu4090IKJ1o1
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE,
        sf::Style::Fullscreen);

    window.setFramerateLimit(FPS_CAP);

    //////////////////////////////////////////////////////

    /// <summary>
    /// https://www.dafont.com/gamer-2.font
    /// </summary>
    sf::Font font;

    if (!font.loadFromFile("Gamer.ttf")) {
        print("Gamer.ttf not found!");
    }

    Time time{ TIMESTEP };
    Score score{ MAX_LIVES };
    Scoreboard scoreBoard{ font };

    //////////////////////////////////////////////////////

    sf::Texture playerTexture;
    sf::Texture gameBackgroundTexture;

    sf::Texture fastCarTexture;
    sf::Texture midCarTexture;
    sf::Texture slowCarTexture;
    
    if (!playerTexture.loadFromFile("player.png") ||
        !gameBackgroundTexture.loadFromFile("game.png")) {

        print("Game texture(s) not found!");
    }

    if (!fastCarTexture.loadFromFile("fast_car.png") ||
        !midCarTexture.loadFromFile("mid_car.png") ||
        !slowCarTexture.loadFromFile("slow_Car.png")) {

        print("Car texture(s) not found!");
    }

    //////////////////////////////////////////////////////

    sf::Texture menuBackgroundTexture;
    sf::Texture buttonTexture;

    if (!menuBackgroundTexture.loadFromFile("menu.png") ||
        !buttonTexture.loadFromFile("button.png")) {

        print("Menu texture(s) not found!");
    }

    //////////////////////////////////////////////////////

    bool quit = false;
    bool showMenu = true;

    Menu menu{ window, font, menuBackgroundTexture, buttonTexture };
    Game game{ window, score, time, gameBackgroundTexture, playerTexture, midCarTexture };

    while (window.isOpen()) {
        sf::Event event;

        if (checkExitCondition(event, window) || quit) {
            window.close();
            // quit().
            return 0;
        }

        window.clear(sf::Color::Magenta);

        std::string output = showMenu ? menu.update(window) : game.update(window, score, time, scoreBoard);

        window.display();

        if (output == "quit") { quit = true; }
        else if (output == "next scene") {
            showMenu = !showMenu;

            if (showMenu) {
                menu.refresh(window, score, scoreBoard, font);
            }
            else {
                // we cant reset the score and time here because the menu need it .
                game.refresh(score, time);
            }
        }
    }

    return 0;
}