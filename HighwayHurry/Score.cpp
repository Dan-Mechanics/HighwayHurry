#include "Score.h"

Score::Score() = default;

Score::Score(int maxLives) : maxLives{ maxLives } { }

//Score::~Score() = default;

/// <summary>
/// Deal damage.
/// </summary>
/// <returns>Did we die?</returns>
bool Score::Damage(int amount)
{
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
void Score::AddScore(int amount)
{
	score += amount;
}

void Score::reset()
{
	clock.restart();
	lives = maxLives;
	score = 0;
}

int Score::getLives()
{
	return lives;
}

int Score::getScore()
{
	return score;
}

int Score::getMaxLives()
{
	return maxLives;
}

float Score::getTime()
{
	return clock.getElapsedTime().asSeconds();
}
