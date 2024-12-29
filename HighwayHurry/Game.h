#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Scoreboard.h"
#include "Utils.h"

extern const sf::String TITLE;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Game {
public:
	Game();
	Game(Score& score, Time& time, sf::Texture& backgroundTexture, const sf::Texture& playerTexture,
		const sf::Texture& fast, const sf::Texture& mid, const sf::Texture& slow);

	void refresh(Score& score, Time& time);
	FrameResult update(sf::RenderWindow& window, Score& score, Time& time, Scoreboard& scoreboard);

	sf::Sprite obstacleSprites[3]{};

	/// <summary>
	/// We do this because the fixed amount of enemies never changes.
	/// It also saves heap new and delete.
	/// <summary>
	Obstacle obstacles[10]{};

private:
	Player player{};
	Environment environment{};

	sf::Sprite backgroundSprite{};
	sf::Sprite playerSprite{};

	/// <summary>
	/// Because apparently the size of an array has a complex equation.
	/// </summary>
	int obstacleCount{};
};