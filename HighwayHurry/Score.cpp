#include "Score.h"

Score::Score() = default;

/// <summary>
/// Deal damage to player, which will eventually end game.
/// </summary>
/// <returns>If has died from damage.</returns>
bool Score::Damage(const int amount) {
	// we are already dead.
	if (lives <= 0) { return true; }
	
	lives -= amount;

	// we have been killed.
	if (lives > 0) { return false; }

	lives = 0;

	// game over.

	return true;
}

void Score::AddScore(const int amount) {
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
