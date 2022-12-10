#include <SFML\Graphics.hpp>
#include "game.h"
#pragma once

class ScoreBoard {
public:
    sf::Text text;
    sf::Font CourierPrime_Regular;

    ScoreBoard(Game& game);

    void draw(sf::RenderWindow& window, int h, int c);
};