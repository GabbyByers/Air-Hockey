#include <SFML\Network.hpp>
#include "backround.h"
#include "ball.h"
#include "crosshair.h"
#include "game.h"
#include "handle.h"
#include "mouse.h"
#include "scoreboard.h"
#pragma once

class Client {
public:
    Game game;
    Mouse mouse = Mouse(game);

    int host_score = 0;
    int client_score = 0;
    int host_mouse_x = 0;
    int host_mouse_y = 0;
    ScoreBoard scoreboard = ScoreBoard(game);
    Backround backround = Backround(game);
    Handle host_handle = Handle(true, game);
    Handle client_handle = Handle(false, game);
    CrossHair host_cross;
    CrossHair client_cross;
    Ball ball = Ball(game);

    sf::UdpSocket socket;
    int outgoing_data_size = 8;
    uint8_t* outgoing_data = new uint8_t[outgoing_data_size];
    int incoming_data_size = 40;
    uint8_t* incoming_data = new uint8_t[incoming_data_size];

    sf::IpAddress server_address;
    unsigned short server_port = 0;
    size_t bytes_received;
    sf::IpAddress return_address;
    unsigned short return_port = 0;

    Client(sf::RenderWindow& window);

    ~Client();

    void ping_server();

    void receive_response();

    void play(sf::RenderWindow& window);

    void control(sf::RenderWindow& window);

    void view(sf::RenderWindow& window);
};