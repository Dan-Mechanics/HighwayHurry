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
	Menu(const sf::RenderWindow& window, const sf::Font& font, const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture);

	void refresh(const sf::RenderWindow& window, const Score& score, const Scoreboard& scoreboard, const sf::Font& font);
	int update(sf::RenderWindow& window);
	//bool open(bool start, Score& score, Scoreboard& scoreboard, sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sprite& quitButtonSprite, sf::Sprite& playButtonSprite) const;
private:
	Button playButton{};
	Button quitButton{};

	sf::Sprite playButtonSprite{};
	sf::Sprite quitButtonSprite{};
	sf::Sprite backgroundSprite{};

	sf::Text titleText{};
	sf::Text scoreText{};
	sf::Text debugInstructions{};

	bool firstMenuOpen{};
};