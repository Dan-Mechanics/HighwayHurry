#include "Game.h"
#include "Time.h"
#include "Player.h"
#include "Environment.h"
#include "Utils.h"
#include "MathUtils.h"
#include "Scoreboard.h"
#include "Button.h"
#include "Obstacle.h"
#include <random>

const sf::String TITLE = "Highway Hurry";

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

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

Game::Game(const sf::RenderWindow& const window, Score& const score, Time& const time, sf::Texture& const backgroundTexture, const sf::Texture& const playerTexture,
    const sf::Texture& const fast, const sf::Texture& const mid, const sf::Texture& const slow) {

    playerSprite.setTexture(playerTexture);
    backgroundSprite.setTexture(backgroundTexture);

    //midSprite.setTexture(mid);
    //slowSprite .setTexture(slow);
    //fastSprite.setTexture(fast);

    //sf::Sprite _obstacleSprites[3];

    obstacleSprites[0].setTexture(mid);
    obstacleSprites[1].setTexture(slow);
    obstacleSprites[2].setTexture(fast);

    backgroundSprite.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y * 2));

    backgroundTexture.setRepeated(true);

    // smoothe ?

    applyGlobalScale(playerSprite);
    applyGlobalScale(backgroundSprite);

    // we love cPP!!
    // https://www.youtube.com/watch?v=a4P4ial8OgQ

    for (int i = 0; i < sizeof(obstacleSprites) / sizeof(sf::Sprite); i++) {
        applyGlobalScale(obstacleSprites[i]);
    }

    // this makes the random fixed ? yep.

    player = { playerSprite };
    environment = { backgroundSprite };

    obstacleCount = sizeof(obstacles) / sizeof(Obstacle);

    for (int i = 0; i < obstacleCount; i++) {
        obstacles[i] = { obstacleSprites[0], score };
        //obstacles.emplace_back( window, obstacleSprites[0], score );
    }

    refresh(score, time);
}

void Game::refresh(Score& const score, Time& const time) {
    print("Opening game.");
    
    // bomboclat.
    // srand(std::time(0));
    srand(std::time(NULL));

    player.reset();
    score.reset();
    time.reset();

    for (int i = 0; i < obstacleCount; i++) {
        obstacles[i].reset(time);
    }
}

int Game::update(sf::RenderWindow& const window, Score& const score, Time& const time, Scoreboard& const scoreboard) {
    unsigned int result = 0;
    
    // we have FixedUpdate() at home :
    for (int i = 0; i < time.processFrame(); i++) {
        environment.move(time);
        player.move(time);

        for (int j = 0; j < obstacleCount; j++) {
            obstacles[j].move(time, score);

            if (player.checkCollision(score, obstacles[j], time)) {
                // temp fix:
                //window.clear(sf::Color::Black);

                // otherwise we would need to have an int result which is possible but a little annoying thb.

                result = 1;
            }
        }
    }

    environment.draw(window, backgroundSprite);

    for (int i = 0; i < obstacleCount; i++) {
        obstacles[i].draw(window, obstacleSprites[obstacles[i].getSprite()]);
    }

    player.draw(window, playerSprite);

    scoreboard.draw(window, score);

    // next frame.
    //return 0;
    return result;
}