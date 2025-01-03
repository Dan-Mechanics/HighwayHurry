#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"
#include "Environment.h"
#include "Player.h"
#include "Score.h"
#include "Button.h"
#include "ScoreHUD.h"
#include "Utils.h"

class Menu {
public:
	Menu();
	Menu(const sf::Font& font, const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture);

	void refresh(const Score& score, const ScoreHUD& scoreHUD, const sf::Font& font, sf::RenderWindow& window);
	FrameResult draw(sf::RenderWindow& window);

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