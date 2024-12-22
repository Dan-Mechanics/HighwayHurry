#include "Scoreboard.h"
#include "Utils.h"

Scoreboard::Scoreboard() = default;

Scoreboard::Scoreboard(const sf::Font& font) {
    applyTextBranding(text, font);

    text.setPosition(15, -40);
}

void Scoreboard::draw(sf::RenderWindow& window, Score& score) {
    setGameString(string, score);
    
    text.setString(string);
    //text.setPosition(15, -40); // ??

    window.draw(text);
}

void Scoreboard::setGameString(sf::String& string, const Score& score) const {
    string.clear();

    // is there a cpp stringbuilder ??
    string += std::to_string(score.getScore());
    string += " | ";
    string += "( ";
    string += std::to_string(score.getLives());
    string += " / ";
    string += std::to_string(score.getMaxLives());
    string += " )";
    string += " | ";
    string += std::to_string(score.getTime());
}

sf::String Scoreboard::getMenuString(const Score& score) const {
    // sf::String menuString = "";
    
    sf::String menuString;
    menuString.clear();

    menuString += "SCORE : ";
    menuString += std::to_string(score.getScore());
    menuString += " | ";
    menuString += "TIME : ";
    menuString += std::to_string(score.getTime());

    return menuString;
}
