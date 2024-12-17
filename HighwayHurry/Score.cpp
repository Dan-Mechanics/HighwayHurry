#include "Score.h"

Score::Score() = default;

//Score::Score(int maxLives) : maxLives{ maxLives } { }

//Score::~Score() = default;

/// <summary>
/// Deal damage.
/// </summary>
bool Score::Damage(const int amount) {
	// we are already dead.
	if (lives <= 0) { return false; }
	
	lives -= amount;

	// we have been killed.
	if (lives > 0) { return false; }

	lives = 0;

	// game over.

	return true;
}

/// <summary>
/// Todo: add checks
/// </summary>
void Score::AddScore(const int amount) {
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
