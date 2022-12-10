#include <SFML\Graphics.hpp>
#include <vector>
#include "game.h"
#include "handle.h"
using std::vector;
#pragma once

class Ball {
public:
    float x_pos = 0.0;
    float y_pos = 0.0;
    float x_vel = 0.8;
    float y_vel = 0.8;
    float friction = 0.998;
    float serve_vel = 0.8;
    float trigger_respawn_vel = 0.02;
    bool last_serve = false;

    float pi = 3.14159265359;
    float radius = 30;
    int num_vert = 100;
    vector<sf::Vertex> vertices;
    vector<float> cached_x;
    vector<float> cached_y;
    sf::Color color = sf::Color(255, 255, 255);

    int screen_width = 0;
    int screen_height = 0;
    int margin = 0;

    Ball(Game& game);

    void cache_xy();

    void update_position();

    void bounce_off_walls(int& host_score, int& client_score);

    bool left_goal(int& client_score);

    bool right_goal(int& host_score);

    void respawn(bool left);

    void bounce_off_handle(Handle& handle);

    void tie();

    void draw(sf::RenderWindow& window);
};