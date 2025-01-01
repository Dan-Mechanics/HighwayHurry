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

Game::Game() = default;

Game::Game(Score& score, Time& time, sf::Texture& backgroundTexture, const sf::Texture& playerTexture,
 const sf::Texture& fast,
    const sf::Texture& mid, const sf::Texture& slow) {

    print("Opening game.");

    playerSprite.setTexture(playerTexture);
    backgroundSprite.setTexture(backgroundTexture);

    obstacleSprites[0].setTexture(slow);
    obstacleSprites[1].setTexture(mid);
    obstacleSprites[2].setTexture(fast);

    backgroundSprite.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y * 2));

    backgroundTexture.setRepeated(true);

    // possible: smooth texture.

    applyGlobalScale(playerSprite);
    applyGlobalScale(backgroundSprite);

    // https://www.youtube.com/watch?v=a4P4ial8OgQ
    for (int i = 0; i < sizeof(obstacleSprites) / sizeof(sf::Sprite); i++) {
        applyGlobalScale(obstacleSprites[i]);
    }

    player = { 160, 160 };
    environment = { 1920, 2160 };

    obstacleCount = sizeof(obstacles) / sizeof(Obstacle);

    for (auto i = 0; i < obstacleCount; i++) {
        obstacles[i] = { 160, 160, score };
    }

    refresh(score, time);
}

void Game::refresh(Score& score, Time& time) {
    print("Refresh @ game.");
    
    srand(std::time(NULL));

    player.reset();
    score.reset();
    time.reset();

    for (int i = 0; i < obstacleCount; i++) {
        obstacles[i].reset(time);
    }
}

FrameResult Game::draw(sf::RenderWindow& window, Score& score, Time& time, Scoreboard& scoreboard) {
    auto result = FrameResult::NEXT_FRAME;
    
    // add fixedupdate.
    for (int i = 0; i < time.processFrame(); i++) {
        environment.move(time);
        player.move(time);

        for (int j = 0; j < obstacleCount; j++) {
            if (processObstacle(obstacles[j], score, time)) {
                result = FrameResult::NEXT_SCENE;
            }
        }
    }

    environment.draw(window, backgroundSprite);

    for (int i = 0; i < obstacleCount; i++) {
        obstacles[i].draw(window, obstacleSprites[obstacles[i].getSpriteIndex()]);
    }

    player.draw(window, playerSprite);

    scoreboard.draw(window, score);

    return result;
}

bool Game::processObstacle(Obstacle& obstacle, Score& score, const Time& time) const {
    obstacle.move(time);
    obstacle.constrain(time, score);

    auto hasCollision = player.checkCollision(obstacle);

    if (hasCollision) {
        obstacle.reset(time);
        return score.Damage(1);
    }
}
