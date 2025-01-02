#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Maybe refactor to ScoreManager ??
/// Manages score and gameover but not the scoreboard.
/// </summary>
class Score {
public:
	Score();

	void damage(const int amount);
	void addScore(const int amount);

	void reset();
	int getLives() const;
	int getScore() const;
	int getMaxLives() const;
	float getTime() const;
	bool checkGameOver() const;

private:
	int lives{};
	int score{};
	int maxLives = 5;
	sf::Clock clock{};
};