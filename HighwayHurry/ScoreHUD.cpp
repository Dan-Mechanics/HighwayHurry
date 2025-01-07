#include "ScoreHUD.h"
#include "Utils.h"
#include <iostream>
#include <sstream>

ScoreHUD::ScoreHUD() = default;

ScoreHUD::ScoreHUD(const sf::Font& font) {
    applyTextBranding(gameText, font);

    gameText.setPosition(15, -40);
}

void ScoreHUD::draw(sf::RenderWindow& window, const Score& score) {
    gameText.setString(getGameString(score));

    window.draw(gameText);
}

sf::String ScoreHUD::getGameString(const Score& score) const {
    std::stringstream result;

    result << std::to_string(score.getScore());
    result << " | ";
    result << "( ";
    result << std::to_string(score.getLives());
    result << " / ";
    result << std::to_string(score.getMaxLives());
    result << " )";
    result << " | ";
    result << std::to_string(score.getTime());

    return result.str();
}

sf::String ScoreHUD::getMenuString(const Score& score) const {
    std::stringstream result;

    result << "SCORE : ";
    result << std::to_string(score.getScore());
    result << " | ";
    result << "TIME : ";
    result << std::to_string(score.getTime());

    return result.str();
}