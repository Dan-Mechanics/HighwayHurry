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

    //////////////////////////////////////////////////////

    sf::Texture menuBackgroundTexture;
    sf::Texture buttonTexture;

    if (!menuBackgroundTexture.loadFromFile("new_menu.png") ||
        !buttonTexture.loadFromFile("button.png")) {
        print("texture not found!");
    }

    //////////////////////////////////////////////////////

    bool quit = false;
    bool showMenu = true;

    Menu menu{ window, font, menuBackgroundTexture, buttonTexture };
    Game game{ window, score, time, gameBackgroundTexture, playerTexture, obstacleTexture };

    while (window.isOpen())
    {
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