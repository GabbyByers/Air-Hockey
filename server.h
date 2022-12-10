#include <SFML\Network.hpp>
#include "backround.h"
#include "ball.h"
#include "crosshair.h"
#include "game.h"
#include "handle.h"
#include "mouse.h"
#include "scoreboard.h"
#pragma once

class Server {
public:
    Game game;
    Mouse mouse = Mouse(game);

    int host_score = 0;
    int client_score = 0;
    ScoreBoard scoreboard = ScoreBoard(game);
    Backround backround = Backround(game);
    Handle host_handle = Handle(true, game);
    Handle client_handle = Handle(false, game);
    CrossHair host_cross;
    CrossHair client_cross;
    Ball ball = Ball(game);

    sf::UdpSocket socket;
    sf::IpAddress address = sf::IpAddress::getLocalAddress();
    unsigned short port = 0;

    int incoming_data_size = sizeof(int) * 2;
    uint8_t* incoming_data = new uint8_t[incoming_data_size];
    int client_mouse_x = 0;
    int client_mouse_y = 0;

    int outgoing_data_size = sizeof(float) * 8;
    uint8_t* outgoing_data = new uint8_t[outgoing_data_size];

    unsigned long long bytes_received = 0;
    sf::IpAddress return_address;
    unsigned short return_port = 0;

    Server(sf::RenderWindow& window);

    ~Server();

    void bind();

    void receive_client_packet();

    void server_reponse_to_client();

    void run(sf::RenderWindow& window);

    void model();

    void view(sf::RenderWindow& window);

    void control(sf::RenderWindow& window);
};