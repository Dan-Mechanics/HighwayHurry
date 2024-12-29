#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Button.h"


int main() {
    print(TITLE);

    const auto FPS_CAP = 320;
    const auto TIMESTEP = 64;

    // https://www.reddit.com/r/sfml/comments/oyms57/how_t
    // https://youtu.be/lFzpkvrscs4?si=9lYiXu4090IKJ1o1
    sf::RenderWindow window{ sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE,
        sf::Style::Fullscreen };

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
    Score score{ };
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

    auto quit = false;
    
    // enum.
    auto currentScene = Scene::MENU_SCENE;

    Menu menu{ font, menuBackgroundTexture, buttonTexture };
    Game game{ score, time, gameBackgroundTexture, playerTexture, fastCarTexture, midCarTexture, slowCarTexture };

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
        // future, use switch again maybe.
        auto frameResult = currentScene == Scene::MENU_SCENE ?
            menu.update(window) : game.update(window, score, time, scoreBoard);

        // !nesting.
        window.display();

        //switch (frameResult) {
        //case 2:
        //    // retrun code 2 = quit game.
        //    quit = true;
        //    break;

        //case 1:
        //    // toggle.
        //    currentScene = (Scene)!(bool)currentScene;

        //    // depending on the new scene, we refresh it.
        //    if (currentScene == Scene::MENU_SCENE) {
        //        menu.refresh(score, scoreBoard, font);
        //    }
        //    else {
        //        game.refresh(score, time);
        //    }

        //    break;
        //default:
        //    break;
        //}

        switch (frameResult) {
        case FrameResult::NEXT_FRAME:
            break;

        case FrameResult::NEXT_SCENE:
            // toggle.
            currentScene = (Scene)!(bool)currentScene;

            // depending on the new scene, we refresh it.
            if (currentScene == Scene::MENU_SCENE) {
                menu.refresh(score, scoreBoard, font);
            }
            else {
                game.refresh(score, time);
            }

            break;

        case FrameResult::CLOSE_GAME:
            // retrun code 2 = quit game.
            quit = true;
            break;

        default:
            break;
        }
    }

    return 0;
}