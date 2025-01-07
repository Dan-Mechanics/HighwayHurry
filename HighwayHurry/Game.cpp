#include "Game.h"
#include "Time.h"
#include "Player.h"
#include "Environment.h"
#include "Utils.h"
#include "MathUtils.h"
#include "ScoreHUD.h"
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

    print("Constructing game.");

    playerSprite.setTexture(playerTexture);
    backgroundSprite.setTexture(backgroundTexture);

    obstacleSprites[0].setTexture(slow);
    obstacleSprites[1].setTexture(mid);
    obstacleSprites[2].setTexture(fast);

    backgroundSprite.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y * 2));

    backgroundTexture.setRepeated(true);

    // POSSIBLE: smoothe texture.
    // But I think it looks better pixelated.

    applyGlobalScale(playerSprite);
    applyGlobalScale(backgroundSprite);

    for (int i = 0; i < sizeof(obstacleSprites) / sizeof(sf::Sprite); i++) {
        applyGlobalScale(obstacleSprites[i]);
    }

    // Now we can dynamically add or remove enemies if we wanted to.
    for (int i = 0; i < obstacleCount; i++) {
        obstacles.emplace_back(160, 160, score);
    }

    player = { 160, 160 };
    environment = { 1920, 2160 };
}

void Game::refresh(Score& score, Time& time, sf::RenderWindow& window) {
    print("Refresh @ game.");
    
    // https://en.sfml-dev.org/forums/index.php?topic=16298.msg116988#msg116988
    window.setMouseCursorVisible(false);

    // Do this so that the random is different each time.
    srand(std::time(NULL));

    player.reset();
    score.reset();
    time.reset();

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].reset();
    }
}

FrameResult Game::draw(sf::RenderWindow& window, Score& score, Time& time, ScoreHUD& scoreHUD) {
    auto frameResult = FrameResult::NEXT_FRAME;
    
    // Similar to FixedUpdate().
    // This returns the amount of ticks we have to process
    // in order to be independant of framerate.
    int fixedTicks = time.processFrame();

    for (int i = 0; i < fixedTicks; i++) {
        environment.move(time);
        player.move(time);

        for (int j = 0; j < obstacles.size(); j++) {
            obstacles[j].move(time);
            obstacles[j].constrain(time, score);

            player.checkCollisionWithObstacle(obstacles[j], score);
        }

        if (score.checkGameOver()) {
            frameResult = FrameResult::NEXT_SCENE;
        }
    }

    environment.draw(window, backgroundSprite);

    for (int i = 0; i < obstacles.size(); i++) {
        // Loop over obstacles and give them their sprite.
        obstacles[i].draw(window, obstacleSprites[obstacles[i].getSpriteIndex()]);
    }

    player.draw(window, playerSprite);

    scoreHUD.draw(window, score);

    return frameResult;
}