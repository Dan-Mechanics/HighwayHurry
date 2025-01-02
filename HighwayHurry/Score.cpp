#include "Score.h"

Score::Score() = default;

/// <summary>
/// Deal damage to player, which will eventually end game.
/// </summary>
void Score::damage(const int amount) {
	lives -= amount;

	if (lives < 0) {
		lives = 0;
	}
}

void Score::addScore(const int amount) {
	if (amount <= 0) { return; }
	
	score += amount;
}

void Score::reset() {
	clock.restart();
	lives = maxLives;
	score = 0;
}

int Score::getLives() const {
	return lives;
}

int Score::getScore() const {
	return score;
}

int Score::getMaxLives() const {
	return maxLives;
}

float Score::getTime() const {
	return clock.getElapsedTime().asSeconds();
}

bool Score::checkGameOver() const {
	return lives <= 0;
}