#include "Game.h"
#include "Time.h"
#include "Player.h"
#include "Environment.h"
#include "Utils.h"
#include "Scoreboard.h"
#include "Button.h"
#include "Obstacle.h"
#include <random>

//use this->more !
//use{} with initilzaer list
//use default
//always virtual destructor
//    {
//}
//public
//protected
//private

// pointer is like int? in c# and references are handy because then you have
// a contract saying you must give me a value, pointers is acceptable behaviour no value.

//Game::Game(sf::RenderWindow& window, sf::Font& font, Time& time, Score& score) :
//    window{ window }, font{ font }, time{ time }, score{ score } { }

Game::Game() = default;

Game::Game(const sf::RenderWindow& const window, Score& const score, Time& const time, sf::Texture& const backgroundTexture, const sf::Texture& const playerTexture, const sf::Texture& const obstacleTexture) {
    print("Opening game.");

    playerSprite.setTexture(playerTexture);
    backgroundSprite.setTexture(backgroundTexture);
    obstacleSprite.setTexture(obstacleTexture);

    backgroundSprite.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y * 2));

    backgroundTexture.setRepeated(true);

    // smoothe ?

    applyGlobalScale(playerSprite);
    applyGlobalScale(backgroundSprite);
    applyGlobalScale(obstacleSprite);

    // this makes the random fixed ? yep.

    player = { window, playerSprite };
    environment = { window, backgroundSprite };
    //scoreboard = { font };
    //std::vector<Obstacle*> obstacles;

    // i basically want this to be dynaically allocated in this heap scope, 
    // and i also want to add more cars so progresllively more difficult.
    // i have no idea how im gonna add friction and or collison !!!
    for (int i = 0; i < 8; i++) {
        // DNAGER DANGER ZONE.
        Obstacle* car = new Obstacle(window, obstacleSprite, score);

        obstacles.push_back(car);

        // ?? entities.emplace_back(window, playerSprite);
    }

    refresh(score, time);
}

void Game::refresh(Score& const score, Time& const time) {
    srand(std::time(0));

    player.reset();
    score.reset();
    time.reset();

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->reset();
    }
}

std::string Game::update(sf::RenderWindow& const window, Score& const score, Time& const time, Scoreboard& const scoreboard) {
    for (int i = 0; i < time.processFrame(); i++) {
        environment.move(time);
        player.move(time);

        for (int j = 0; j < obstacles.size(); j++) {
            obstacles[j]->move(time);

            if (player.checkCollision(score, *obstacles[j])) {
                /*for (int i = 0; i < obstacles.size(); i++) {
                    delete obstacles[i];
                }*/

                return "next scene";
            }
        }
    }

    environment.draw(window, backgroundSprite);

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->draw(window, obstacleSprite);
    }

    player.draw(window, playerSprite);

    scoreboard.draw(window, score);

    return "next frame";
}