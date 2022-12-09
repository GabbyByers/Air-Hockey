#include "handle.h"

Handle::Handle(bool is_left, int _screen_width, int _screen_height, int _margin) {
    screen_width = _screen_width;
    screen_height = _screen_height;
    margin = _margin;
    left = is_left;
    cache_xy();
}

Handle::~Handle() {
    delete[] x_pos_hist;
    delete[] y_pos_hist;
}

void Handle::cache_xy() {
    for (int i = 0; i < num_vert; i++) {
        float radian = i * ((2 * pi) / (num_vert - 1));
        cached_x.push_back(cos(radian) * radius);
        cached_y.push_back(sin(radian) * radius);
    }
}

void Handle::set_position(int x, int y) {
    if (left) {
        if (x > ((2 * screen_width / 5) - radius)) {
            x = (2 * screen_width / 5) - radius;
        }
        if (x < radius + margin) {
            x = radius + margin;
        }
        if (y > (screen_height - radius - margin)) {
            y = screen_height - radius - margin;
        }
        if (y < radius + margin) {
            y = radius + margin;
        }
    }
    else {
        if (x < (3 * screen_width / 5) + radius) {
            x = (3 * screen_width / 5) + radius;
        }
        if (x > screen_width - radius - margin) {
            x = screen_width - radius - margin;
        }
        if (y > (screen_height - radius - margin)) {
            y = screen_height - radius - margin;
        }
        if (y < radius + margin) {
            y = radius + margin;
        }
    }
    x_pos = static_cast<float>(x);
    y_pos = static_cast<float>(y);
    for (int i = 0; i < history - 1; i++) {
        x_pos_hist[i] = x_pos_hist[i + 1];
        y_pos_hist[i] = y_pos_hist[i + 1];
    }
    x_pos_hist[history - 1] = x_pos;
    y_pos_hist[history - 1] = y_pos;
}

void Handle::draw(sf::RenderWindow& window) {
    vertices.clear();
    for (int i = 0; i < num_vert; i++) {
        sf::Vector2f vect = sf::Vector2f(x_pos + cached_x[i], y_pos + cached_y[i]);
        vertices.push_back(sf::Vertex(vect, color));
    }
    window.draw(&vertices[0], vertices.size(), sf::LineStrip);
}