#include <SFML\Graphics.hpp>
#include <vector>
using std::vector;
#pragma once

class Handle {
public:
    float x_pos = 0.0;
    float y_pos = 0.0;

    int history = 30;
    float* x_pos_hist = new float[history];
    float* y_pos_hist = new float[history];

    sf::Color color = sf::Color(255, 255, 255);

    float pi = 3.14159265359;
    float radius = 80;

    int num_vert = 100;
    vector<sf::Vertex> vertices;
    vector<float> cached_x;
    vector<float> cached_y;

    bool left = false;

    int screen_width = 0;
    int screen_height = 0;
    int margin = 0;

    Handle(bool is_left, int _screen_width, int _screen_height, int _margin);

    ~Handle();

    void cache_xy();

    void set_position(int x, int y);

    void draw(sf::RenderWindow& window);
};