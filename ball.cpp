#include "ball.h"

Ball::Ball(Game& game) {
    screen_width = game.screen_width;
    screen_height = game.screen_height;
    margin = game.margin;
    cache_xy();
}

void Ball::cache_xy() {
    for (int i = 0; i < num_vert; i++) {
        float radian = i * ((2 * pi) / (num_vert - 1));
        cached_x.push_back(cos(radian) * radius);
        cached_y.push_back(sin(radian) * radius);
    }
}

void Ball::update_position() {
    x_pos += x_vel;
    y_pos += y_vel;
    x_vel *= friction;
    y_vel *= friction;
}

void Ball::bounce_off_walls(int& host_score, int& client_score) {
    if ((x_pos + radius) > screen_width - margin) {
        if (right_goal(host_score)) {
            return;
        }
        x_pos = screen_width - margin - radius;
        x_vel = -x_vel;
    }
    if ((x_pos - radius) < margin) {
        if (left_goal(client_score)) {
            return;
        }
        x_pos = radius + margin;
        x_vel = -x_vel;
    }
    if ((y_pos + radius) > screen_height - margin) {
        y_pos = screen_height - margin - radius;
        y_vel = -y_vel;
    }
    if ((y_pos - radius) < margin) {
        y_pos = radius + margin;
        y_vel = -y_vel;
    }
}

bool Ball::left_goal(int& client_score) {
    if (((screen_height / 3) < y_pos) && (y_pos < (2 * screen_height / 3))) {
        client_score++;
        respawn(false);
        return true;
    }
    return false;
}

bool Ball::right_goal(int& host_score) {
    if (((screen_height / 3) < y_pos) && (y_pos < (2 * screen_height / 3))) {
        host_score++;
        respawn(true);
        return true;
    }
    return false;
}

void Ball::respawn(bool left) {
    x_pos = static_cast<float>(screen_width / 2);
    y_pos = static_cast<float>(screen_height / 2);
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

void Ball::bounce_off_handle(Handle& handle) {
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

void Ball::tie() {
    if (((2 * screen_width / 5) + radius < x_pos) && (x_pos < (3 * screen_width / 5) - radius)) {
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

void Ball::draw(sf::RenderWindow& window) {
    vertices.clear();
    for (int i = 0; i < num_vert; i++) {
        sf::Vector2f vect = sf::Vector2f(x_pos + cached_x[i], y_pos + cached_y[i]);
        vertices.push_back(sf::Vertex(vect, color));
    }
    window.draw(&vertices[0], vertices.size(), sf::LineStrip);
}