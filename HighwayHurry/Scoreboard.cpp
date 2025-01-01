#include "Scoreboard.h"
#include "Utils.h"

Scoreboard::Scoreboard() = default;

Scoreboard::Scoreboard(const sf::Font& font) {
    applyTextBranding(text, font);

    text.setPosition(15, -40);
}

void Scoreboard::draw(sf::RenderWindow& window, const Score& score) {
    menuString = getGameString(score);
    
    text.setString(menuString);

    window.draw(text);
}

/// <summary>
/// https://stackoverflow.com/questions/2462951/c-equivalent-of-stringbuffer-stringbuilder :
/// "The C++ way would be to use std::stringstream or just plain string concatenations. C++ strings are mutable so the performance considerations of concatenation are less of a concern."
/// </summary>
sf::String Scoreboard::getGameString(const Score& score) const {

    // we do this because this fucntion is const.
    // maybe pre-alocate this ?
    sf::String result;
    result.clear();

    result += std::to_string(score.getScore());
    result += " | ";
    result += "( ";
    result += std::to_string(score.getLives());
    result += " / ";
    result += std::to_string(score.getMaxLives());
    result += " )";
    result += " | ";
    result += std::to_string(score.getTime());

    return result;  
}

/// <summary>
/// https://stackoverflow.com/questions/2462951/c-equivalent-of-stringbuffer-stringbuilder
/// </summary>
sf::String Scoreboard::getMenuString(const Score& score) const {
    sf::String result;
    result.clear();

    result += "SCORE : ";
    result += std::to_string(score.getScore());
    result += " | ";
    result += "TIME : ";
    result += std::to_string(score.getTime());

    return result;
}