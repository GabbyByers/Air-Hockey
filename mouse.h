#include <SFML/Graphics.hpp>
#include "game.h"
#pragma once

class Mouse {
public:
    int x = 0;
    int y = 0;
    int prev_x = 0;
    int prev_y = 0;
    int rel_x = 0;
    int rel_y = 0;
    int width = 0;
    int height = 0;
    bool isOverScreen = false;

    Mouse(Game& game);

    void setMouseProperties(sf::Vector2i vect);

    void checkMouseOverScreen(sf::Vector2i vect);

    void setMousePosition(sf::Vector2i vect);

    void getRelativeMouseMovement(sf::Vector2i vect);
};