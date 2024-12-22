#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Scoreboard.h"

extern const sf::String TITLE;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Game {
public:
	Game();
	Game(const sf::RenderWindow& window, Score& score, Time& time, sf::Texture& backgroundTexture, const sf::Texture& playerTexture, 
		const sf::Texture& fast, const sf::Texture& mid, const sf::Texture& slow);

	void refresh(Score& score, Time& time);
	int update(sf::RenderWindow& window, Score& score, Time& time, Scoreboard& scoreboard);

	sf::Sprite obstacleSprites[3]{};
	Obstacle obstacles[8]{};
	// add memory managmentsi n the future: 
	// deload method or destructor thing if you wanna have crazy amount of enemies increasing.

private:
	Player player{};
	Environment environment{};

	// i dont think this will work.
	//std::vector<Obstacle> obstacles{};

	//std::vector<Obstacle> obstacles{};
	sf::Sprite backgroundSprite{};
	sf::Sprite playerSprite{};
	int obstacleCount{};
};