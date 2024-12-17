#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Scoreboard.h"

extern const sf::String TITLE;

class Game {
public:
	Game();
	Game(const sf::RenderWindow& const window, Score& const score, Time& const time, sf::Texture& const backgroundTexture, const sf::Texture& const playerTexture, 
		const sf::Texture& const fast, const sf::Texture& const mid, const sf::Texture& const slow);

	void refresh(Score& score, Time& time);
	unsigned int update(sf::RenderWindow& const window, Score& const score, Time& const time, Scoreboard& const scoreboard);

	// add memory managmentsi n the future: 
	// deload method or destructor thing if you wanna have crazy amount of enemies increasing.

private:
	Player player{};
	Environment environment{};

	// i dont think this will work.
	std::vector<Obstacle> obstacles{};

	sf::Sprite backgroundSprite{};
	sf::Sprite playerSprite{};
	sf::Sprite obstacleSprites[3]{};
};