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
	Game(const sf::RenderWindow& const window, Score& const score, Time& const time, sf::Texture& const backgroundTexture, const sf::Texture& const playerTexture, const sf::Texture& const obstacleTexture);

	void refresh(Score& score, Time& time);
	std::string update(sf::RenderWindow& const window, Score& const score, Time& const time, Scoreboard& const scoreboard);

	// add memory managmentsi n the future: 
	// deload method or destructor thing if you wanna have crazy amount of enemies increasing.

private:
	//Scoreboard scoreboard;
	Player player;
	Environment environment;
	std::vector<Obstacle*> obstacles;

	sf::Sprite backgroundSprite;
	sf::Sprite obstacleSprite;
	sf::Sprite playerSprite;
};