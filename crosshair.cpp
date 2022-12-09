#include "crosshair.h"

CrossHair::CrossHair() {}

void CrossHair::draw(sf::RenderWindow& window, int x, int y) {
    vertices.clear();
    vertices.push_back(sf::Vertex(sf::Vector2f(x - size, y), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(x + size, y), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(x, y - size), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(x, y + size), color));
    window.draw(&vertices[0], vertices.size(), sf::Lines);
}