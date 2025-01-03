#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "ScoreHUD.h"
#include "Utils.h"

extern const sf::String TITLE;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Game {
public:
	Game();
	Game(Score& score, Time& time, sf::Texture& backgroundTexture, const sf::Texture& playerTexture,
		const sf::Texture& fast, const sf::Texture& mid, const sf::Texture& slow);

	void refresh(Score& score, Time& time, sf::RenderWindow& window);
	FrameResult draw(sf::RenderWindow& window, Score& score, Time& time, ScoreHUD& scoreboard);

	// why does this need to be public again ?
	sf::Sprite obstacleSprites[3]{};
	std::vector<Obstacle> obstacles{};
	//Obstacle obstacles[10]{};
private:
	Player player{};
	Environment environment{};

	//int count{};
	sf::Sprite backgroundSprite{};
	sf::Sprite playerSprite{};
};