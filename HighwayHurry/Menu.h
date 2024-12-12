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
	Menu(const sf::RenderWindow& const window, const sf::Font& const font, const sf::Texture& const backgroundTexture, const sf::Texture& const buttonTexture);

	void refresh(const sf::RenderWindow& const window, const Score& const score, const Scoreboard& const scoreboard, const sf::Font& const font);
	std::string update(sf::RenderWindow& const window);
	//bool open(bool start, Score& score, Scoreboard& scoreboard, sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sprite& quitButtonSprite, sf::Sprite& playButtonSprite) const;
private:
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