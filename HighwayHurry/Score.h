#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Maybe refactor to ScoreManager ??
/// Manages score and gameover but not the scoreboard.
/// I'm choosing to have the player lives here because otherwise we also have to give
/// the player to the scoreHUD and aslo the lives and score and related together.
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