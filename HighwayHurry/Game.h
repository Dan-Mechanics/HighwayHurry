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

private:
	Player player{};
	Environment environment{};

	sf::Sprite obstacleSprites[3]{};
	std::vector<Obstacle> obstacles{};

	sf::Sprite backgroundSprite{};
	sf::Sprite playerSprite{};
};