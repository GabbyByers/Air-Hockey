#include "backround.h"

Backround::Backround(int init_margin, int init_width, int init_height) {
    margin = init_margin;
    width = init_width;
    height = init_height;
    initialize_vertices();
}

void Backround::initialize_vertices() {
    vertices.push_back(sf::Vertex(sf::Vector2f(2 * width / 5, height - margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(2 * width / 5, margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(3 * width / 5, height - margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(3 * width / 5, margin), color));

    vertices.push_back(sf::Vertex(sf::Vector2f(margin, margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(margin, height - margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, height - margin), color));

    vertices.push_back(sf::Vertex(sf::Vector2f(margin, margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(margin, height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(margin, height - margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(margin, 2 * height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, height - margin), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, 2 * height / 3), color));

    vertices.push_back(sf::Vertex(sf::Vector2f(0, height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(margin, height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(0, 2 * height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(margin, 2 * height / 3), color));

    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width, height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width - margin, 2 * height / 3), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(width, 2 * height / 3), color));

    int width_dots = ((width - 4 * margin) / margin) + 1;
    int height_dots = ((height - 4 * margin) / margin) + 1;
    for (int i = 0; i < width_dots; i++) {
        for (int j = 0; j < height_dots; j++) {
            dots.push_back(sf::Vertex(sf::Vector2f(i * margin + 2 * margin, j * margin + 2 * margin), color));
        }
    }
}

void Backround::draw(sf::RenderWindow& window) {
    window.draw(&vertices[0], vertices.size(), sf::Lines);
    window.draw(&dots[0], dots.size(), sf::Points);
}