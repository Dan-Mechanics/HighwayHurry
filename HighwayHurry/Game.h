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

	bool play(sf::RenderWindow& window, sf::Sprite& playerSprite, sf::Sprite& backgroundSprite, sf::Sprite& obstacleSprite, Score& score, Time& time, Scoreboard& scoreboard);
};