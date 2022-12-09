#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "mouse.h"
#include "crosshair.h"
#include "backround.h"
#include "handle.h"
using std::vector;
using std::cout;

class Game {
public:
    int screen_width = 1400;
    int screen_height = 700;
    int margin = 25;

    Game() {}
};
Game game;

class Ball {
public:
    float x_pos = 0.0;
    float y_pos = 0.0;
    float x_vel = 0.8;
    float y_vel = 0.8;
    float friction = 0.9995;
    float serve_vel = 0.8;
    float trigger_respawn_vel = 0.01;
    bool last_serve = false;

    float pi = 3.14159265359;
    float radius = 30;
    int num_vert = 100;
    vector<sf::Vertex> vertices;
    vector<float> cached_x;
    vector<float> cached_y;
    sf::Color color = sf::Color(255, 255, 255);

    int* p_host_score = nullptr;
    int* p_client_score = nullptr;

    Ball(int* _p_host_score, int* _p_client_score) {
        p_host_score = _p_host_score;
        p_client_score = _p_client_score;
        cache_xy();
    }

    void cache_xy() {
        for (int i = 0; i < num_vert; i++) {
            float radian = i * ((2 * pi) / (num_vert - 1));
            cached_x.push_back(cos(radian) * radius);
            cached_y.push_back(sin(radian) * radius);
        }
    }

    void update_position() {
        x_pos += x_vel;
        y_pos += y_vel;
        x_vel *= friction;
        y_vel *= friction;
    }

    void bounce_off_walls() {
        if ((x_pos + radius) > game.screen_width - game.margin) {
            if (right_goal()) {
                return;
            }
            x_pos = game.screen_width - game.margin - radius;
            x_vel = -x_vel;
        }
        if ((x_pos - radius) < game.margin) {
            if (left_goal()) {
                return;
            }
            x_pos = radius + game.margin;
            x_vel = -x_vel;
        }
        if ((y_pos + radius) > game.screen_height - game.margin) {
            y_pos = game.screen_height - game.margin - radius;
            y_vel = -y_vel;
        }
        if ((y_pos - radius) < game.margin) {
            y_pos = radius + game.margin;
            y_vel = -y_vel;
        }
    }

    bool left_goal() {
        if (((game.screen_height / 3) < y_pos) && (y_pos < (2 * game.screen_height / 3))) {
            (*p_client_score)++;
            respawn(false);
            return true;
        }
        return false;
    }

    bool right_goal() {
        if (((game.screen_height / 3) < y_pos) && (y_pos < (2 * game.screen_height / 3))) {
            (*p_host_score)++;
            respawn(true);
            return true;
        }
        return false;
    }

    void respawn(bool left) {
        x_pos = static_cast<float>(game.screen_width / 2);
        y_pos = static_cast<float>(game.screen_height / 2);
        y_vel = 0.0;
        if (left) {
            x_vel = serve_vel;
            last_serve = true;
        }
        else {
            x_vel = -serve_vel;
            last_serve = false;
        }
    }

    void bounce_off_handle(Handle& handle, int prev_x, int prev_y) {
        float dist = sqrt((handle.x_pos - x_pos) * (handle.x_pos - x_pos) + (handle.y_pos - y_pos) * (handle.y_pos - y_pos));
        if (dist > (handle.radius + radius)) { return; }

        float x = x_pos - handle.x_pos;
        float y = y_pos - handle.y_pos;
        float ratio = (handle.radius + radius) / dist;
        x_pos = handle.x_pos + (x * ratio);
        y_pos = handle.y_pos + (y * ratio);

        float nx = x_pos - handle.x_pos;
        float ny = y_pos - handle.y_pos;
        float len = sqrt(nx * nx + ny * ny);
        nx = nx / len;
        ny = ny / len;
        float new_x_vel = x_vel - 2 * (x_vel * nx + y_vel * ny) * nx;
        float new_y_vel = y_vel - 2 * (x_vel * nx + y_vel * ny) * ny;
        x_vel = new_x_vel;
        y_vel = new_y_vel;

        float handle_x_vel = (handle.x_pos - handle.x_pos_hist[0]) / handle.history;
        float handle_y_vel = (handle.y_pos - handle.y_pos_hist[0]) / handle.history;
        x_vel += handle_x_vel;
        y_vel += handle_y_vel;
    }

    void tie() {
        if (((2 * game.screen_width / 5) + radius < x_pos) && (x_pos < (3 * game.screen_width / 5) - radius)) {
            float vel = sqrt(x_vel * x_vel + y_vel * y_vel);
            if (vel < trigger_respawn_vel) {
                respawn(last_serve);
            }
            color = sf::Color(255, 0, 0);
        }
        else {
            color = sf::Color(255, 255, 255);
        }
    }

    void draw(sf::RenderWindow& window) {
        vertices.clear();
        for (int i = 0; i < num_vert; i++) {
            sf::Vector2f vect = sf::Vector2f(x_pos + cached_x[i], y_pos + cached_y[i]);
            vertices.push_back(sf::Vertex(vect, color));
        }
        window.draw(&vertices[0], vertices.size(), sf::LineStrip);
    }
};

class ScoreBoard {
public:
    sf::Text text;
    sf::Font CourierPrime_Regular;

    ScoreBoard() {
        CourierPrime_Regular.loadFromFile("CourierPrime-Regular.ttf");
        text.setFont(CourierPrime_Regular);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color(255, 255, 255));
        text.setPosition(game.margin + 5, 0);
    }

    void draw(sf::RenderWindow& window, int h, int c) {
        text.setString("Score: " + std::to_string(h) + " : " + std::to_string(c));
        window.draw(text);
    }
};

int main()
{
    Mouse mouse(game.screen_width, game.screen_height);
    sf::RenderWindow window(sf::VideoMode(game.screen_width, game.screen_height), "Multiplayer Proof of Concept: 'Air Hockey'", sf::Style::Close);
    
    int host_score = 0;
    int client_score = 0;

    ScoreBoard scoreboard;
    Backround backround(game.margin, game.screen_width, game.screen_height);
    Handle host_handle(true, game.screen_width, game.screen_height, game.margin);
    Handle client_handle(false, game.screen_width, game.screen_height, game.margin);
    CrossHair cross;
    Ball ball(&host_score, &client_score);

    ball.respawn(true);

    while (window.isOpen()) {
        mouse.setMouseProperties(sf::Mouse::getPosition(window));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        /* receive packet from client */

        // model
        host_handle.set_position(mouse.x, mouse.y);
        client_handle.set_position(mouse.x, mouse.y);

        ball.update_position();
        ball.bounce_off_walls();
        ball.bounce_off_handle(host_handle, mouse.prev_x, mouse.prev_y);
        ball.bounce_off_handle(client_handle, mouse.prev_x, mouse.prev_y);
        ball.tie();
        
        /* send a response */

        // view
        window.clear(sf::Color(0, 0, 0));
        backround.draw(window);
        host_handle.draw(window);
        client_handle.draw(window);
        ball.draw(window);
        cross.draw(window, mouse.x, mouse.y);
        scoreboard.draw(window, host_score, client_score);
        window.display();
    }
    return 0;
}




