#include <SFML\Graphics.hpp>
#include <vector>
using std::vector;
#pragma once

class CrossHair {
public:

    int size = 20;
    vector<sf::Vertex> vertices;
    sf::Color color = sf::Color(255, 255, 255);

    CrossHair();

    void draw(sf::RenderWindow& window, int x, int y);
};