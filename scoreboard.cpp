#include "scoreboard.h"

ScoreBoard::ScoreBoard(Game& game) {
    CourierPrime_Regular.loadFromFile("CourierPrime-Regular.ttf");
    text.setFont(CourierPrime_Regular);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color(255, 255, 255));
    text.setPosition(game.margin + 5, 0);
}

void ScoreBoard::draw(sf::RenderWindow& window, int h, int c) {
    text.setString("Score: " + std::to_string(h) + " : " + std::to_string(c));
    window.draw(text);
}