#include <iostream>
#include "server.h"
using std::cout;

Server::Server(sf::RenderWindow& window) {
    bind();
    run(window);
}

Server::~Server() {
    delete[] incoming_data;
    delete[] outgoing_data;
}

void Server::bind() {
    if (socket.bind(port) != sf::Socket::Done) { cout << "Socket Bind Failed\n"; return; } // port 0 - error
    port = socket.getLocalPort();
    if (socket.bind(port) != sf::Socket::Done) { cout << "Socket Bind Failed\n"; return; } // normal port
    port = socket.getLocalPort();

    cout << "IPv4: " << address << "\n";
    cout << "Port: " << port << "\n";
}

void Server::receive_client_packet() {
    if (socket.receive(incoming_data, sizeof(incoming_data), bytes_received, return_address, return_port) == sf::Socket::Done) {
        client_mouse_x = *(reinterpret_cast<int*>(&incoming_data[0]));
        client_mouse_y = *(reinterpret_cast<int*>(&incoming_data[4]));
    }
    else { cout << "Failed to Receive Packet\n"; }
}

void Server::server_reponse_to_client() {
    int index = 0;
    *(reinterpret_cast<int*>(&outgoing_data[index])) = host_score; index += sizeof(int);
    *(reinterpret_cast<int*>(&outgoing_data[index])) = client_score; index += sizeof(int);
    *(reinterpret_cast<float*>(&outgoing_data[index])) = host_handle.x_pos; index += sizeof(float);
    *(reinterpret_cast<float*>(&outgoing_data[index])) = host_handle.y_pos; index += sizeof(float);
    *(reinterpret_cast<float*>(&outgoing_data[index])) = client_handle.x_pos; index += sizeof(float);
    *(reinterpret_cast<float*>(&outgoing_data[index])) = client_handle.y_pos; index += sizeof(float);
    cout << "HX = " << host_handle.x_pos << ", HY = " << host_handle.y_pos << ", CX = " << client_handle.x_pos << ", CY = " << client_handle.y_pos << "\n";
    
    if (socket.send(outgoing_data, sizeof(outgoing_data), return_address, return_port) != sf::Socket::Done) {
        cout << "Failed to Send Response\n";
    }
}

void Server::run(sf::RenderWindow& window) {
    ball.respawn(true);
    while (window.isOpen()) {
        control(window);
        receive_client_packet();
        model();
        server_reponse_to_client();
        view(window);
    }
}

void Server::model() {
    host_handle.set_position(mouse.x, mouse.y);
    client_handle.set_position(client_mouse_x, client_mouse_y);
    ball.update_position();
    ball.bounce_off_walls(host_score, client_score);
    ball.bounce_off_handle(host_handle);
    ball.bounce_off_handle(client_handle);
    ball.tie();
}

void Server::view(sf::RenderWindow& window) {
    window.clear(sf::Color(0, 0, 0));
    backround.draw(window);
    host_handle.draw(window);
    client_handle.draw(window);
    ball.draw(window);
    host_cross.draw(window, mouse.x, mouse.y);
    client_cross.draw(window, client_mouse_x, client_mouse_y);
    scoreboard.draw(window, host_score, client_score);
    window.display();
}

void Server::control(sf::RenderWindow& window) {
    mouse.setMouseProperties(sf::Mouse::getPosition(window));
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}