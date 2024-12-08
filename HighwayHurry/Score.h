#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Add time to score.
/// </summary>
class Score {
public:
	Score();
	Score(int maxLives);
	//virtual ~Score(); // does this need to be here because of Edwin convention ?

	bool Damage(int amount);
	void AddScore(int amount);

	void reset();
	int getLives();
	int getScore();
	int getMaxLives();
	float getTime();

private:
	int lives{};
	int score{};
	int maxLives{};
	sf::Clock clock{};
};

