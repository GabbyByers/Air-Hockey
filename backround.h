#include <SFML\Graphics.hpp>
#include <vector>
using std::vector;
#pragma once

class Backround {
public:

    int margin = 0;
    int width = 0;
    int height = 0;

    vector<sf::Vertex> dots;
    vector<sf::Vertex> vertices;
    sf::Color color = sf::Color(80, 80, 80);

    Backround(int init_margin, int init_width, int init_height);

    void initialize_vertices();

    void draw(sf::RenderWindow& window);
};