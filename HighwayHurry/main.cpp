//=============================================================================
// Tim de Smidt
// Dan-Mechanics
//
// Math for GDV - Calculate the Future
// Eindopdracht 
//
// Highway Hurry
//=============================================================================

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "ScoreHUD.h"
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
    window.setMouseCursorVisible(true);

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
    ScoreHUD scoreHUD{ font };

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
    
    auto currentScene = Scene::MENU_SCENE;

    Menu menu{ font, menuBackgroundTexture, buttonTexture };

    Game game{ score, time, gameBackgroundTexture, playerTexture,
        fastCarTexture, midCarTexture, slowCarTexture };

    while (window.isOpen()) {
        sf::Event event;

        if (checkExitCondition(event, window) || quit) {
            window.close();
            
            quit = true;

            // Close early because we don't have to render on the frame we close.
            return 0;
        }

        // Background color so we can clearly see transparent glitches etc.
        window.clear(sf::Color::Magenta);

        // Scene.draw(); --> not possible because each scene.draw() needs differents params.
        // Future, use switch again maybe.
        auto frameResult = currentScene == Scene::MENU_SCENE ?
            menu.draw(window) : game.draw(window, score, time, scoreHUD);

        window.display();

        /// <summary>
        /// https://www.w3schools.com/cpp/cpp_switch.asp
        /// </summary>
        switch (frameResult) {
            case FrameResult::NEXT_FRAME:
                break;
            case FrameResult::NEXT_SCENE:
                // Toggle.
                currentScene = (Scene)!(bool)currentScene;

                // Depending on the new scene, we refresh it.
                if (currentScene == Scene::MENU_SCENE) {
                    menu.refresh(score, scoreHUD, font, window);
                }
                else {
                    game.refresh(score, time, window);
                }

                break;
            case FrameResult::CLOSE_GAME:
                quit = true;

                break;
            default:
                break;
        }
    }

    return 0;
}