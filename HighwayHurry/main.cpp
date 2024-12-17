#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Button.h"

// next stuff :
// menu width and height so no canvas send
// make it so that you dont have to send sprite because collision is yeet.
// then dont send canvas and sprtiei n construcutro. only set no get methdos for better yeet.
// more const vars.
// make relative velocities make more sense ish.
// ask rosa if it makes sense.
// 
// implement global vars for window so drawalbe no refernec.e
// everytinh looks pretty aight to him, 
// mass makes sense for movement, make the "friction" and "forces" make more sense
// what you could do is make a thing where the relative veloity makes snes.e
// make the enemies do forces a little bit better. make it with drag and everything. the physics for the player makes sense.

// make the enemies bounce back and forth.

/// <summary>
/// Make sprite conform to playersize and dont use getsize on sprite and window ??.
/// </summary>
int main() {
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
    // enum, 
    Menu menu{ window, font, menuBackgroundTexture, buttonTexture };
    Game game{ window, score, time, gameBackgroundTexture, playerTexture, fastCarTexture, midCarTexture, slowCarTexture };

    while (window.isOpen()) {
        sf::Event event;

        if (checkExitCondition(event, window) || quit) {
            window.close();
            
            quit = true;

            // close early because we don't have to render on the frame we close.
            return 0;
        }

        // background color so we can clearly see transparent glitches etc.
        window.clear(sf::Color::Magenta);

        // scene.draw();
        unsigned int returnCode = showMenu ? menu.update(window) : game.update(window, score, time, scoreBoard);

        window.display();

        switch (returnCode) {
        case 2:
            // retrun code 2 = quit game.
            quit = true;
            break;

        case 1:
            // return code 1 = next scene = toggle the current scene.
            showMenu = !showMenu;

            // depending on the new scene, we refresh it.
            if (showMenu) {
                menu.refresh(window, score, scoreBoard, font);
            }
            else {
                game.refresh(score, time);
            }

        default:
            // return code 0 = next frame.
            break;
        }
    }

    return 0;
}