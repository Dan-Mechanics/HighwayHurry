#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Button.h"
#include "Scoreboard.h"

class Menu {
public:
	Menu();
	Menu(Score& score, Scoreboard& scoreboard, sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sprite& quitButtonSprite, sf::Sprite& playButtonSprite);

	void setupForSecond(sf::RenderWindow& window, const Score& const score, const Scoreboard& const scoreboard, const sf::Font& const font);
	std::string update(sf::RenderWindow& window);
	//bool open(bool start, Score& score, Scoreboard& scoreboard, sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sprite& quitButtonSprite, sf::Sprite& playButtonSprite) const;
//private:
	Button playAgainButton{};
	Button quitButton{};

	sf::Sprite playAgainButtonSprite{};
	sf::Sprite quitButtonSprite{};
	sf::Sprite backgroundSprite{};

	sf::Text titleText{};
	sf::Text scoreText{};
	sf::Text failSafe{};

	bool first{};
};