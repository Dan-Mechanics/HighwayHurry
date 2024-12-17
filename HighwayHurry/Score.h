#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Add time to score.
/// </summary>
class Score {
public:
	Score();
	//Score(const int maxLives);
	//virtual ~Score(); // does this need to be here because of Edwin convention ?

	bool Damage(const int amount);
	void AddScore(const int amount);

	void reset();
	int getLives() const;
	int getScore() const;
	int getMaxLives() const;
	float getTime() const;

private:
	int lives{};
	int score{};
	int maxLives = 5;
	sf::Clock clock{};
};

