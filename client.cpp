#include <iostream>
#include "client.h"
using std::cout;
using std::cin;

Client::Client(sf::RenderWindow& window) {
    cout << "IPv4: ";
    cin >> server_address;

    cout << "Port: ";
    cin >> server_port;
    play(window);
}

Client::~Client() {
    delete[] incoming_data;
    delete[] outgoing_data;
}

void Client::ping_server() {
    int index = 0;
    *(reinterpret_cast<int*>(&outgoing_data[index])) = mouse.x; index += sizeof(int);
    *(reinterpret_cast<int*>(&outgoing_data[index])) = mouse.y; index += sizeof(int);
    if (socket.send(outgoing_data, sizeof(outgoing_data), server_address, server_port) != sf::Socket::Done) {
        cout << "Failed to Send Packet to Sever\n";
    }
}

void Client::receive_response() {
    if (socket.receive(incoming_data, sizeof(incoming_data), bytes_received, return_address, return_port) != sf::Socket::Done) {
        cout << "Failed to Receive Packet\n";
    }
}

void Client::unpack_packet() {

}

void Client::play(sf::RenderWindow& window) {
    while (window.isOpen()) {
        control(window);
        ping_server();
        receive_response();
        unpack_packet();
        view(window);
    }
}

void Client::control(sf::RenderWindow& window) {
    mouse.setMouseProperties(sf::Mouse::getPosition(window));
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Client::view(sf::RenderWindow& window) {
    window.clear(sf::Color(0, 0, 0));
    backround.draw(window);
    host_handle.draw(window);
    client_handle.draw(window);
    ball.draw(window);
    host_cross.draw(window, host_mouse_x, host_mouse_y);
    client_cross.draw(window, mouse.x, mouse.y);
    scoreboard.draw(window, host_score, client_score);
    window.display();
}