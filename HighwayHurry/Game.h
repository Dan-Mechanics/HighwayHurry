#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Scoreboard.h"

class Game {
public:
	Game();
	Game(sf::RenderWindow& window, Score& score, Time& time, sf::Sprite& playerSprite, sf::Sprite& backgroundSprite, sf::Sprite& obstacleSprite, const sf::Font& const font);

	Scoreboard scoreboard;
	Player player;
	Environment environment;
	std::vector<Obstacle*> obstacles;

	sf::Sprite backgroundSprite;
	sf::Sprite obstacleSprite;
	sf::Sprite playerSprite;

	void refresh(Score& score, Time& time);
	std::string update(sf::RenderWindow& window, Score& score, Time& time);

	// add memory managmentsi n the future: 
	// deload method or destructor thing if you wanna have crazy amount of enemies increasing.
};