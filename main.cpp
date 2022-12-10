#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "client.h"
#include "server.h"
#include "game.h"
using std::cout;
using std::cin;
using std::vector;
using std::string;

int main()
{
    cout << "Server (s) or Client (c)?: ";
    char type;
    cin >> type;
    
    string name;
    if (type == 's') {
        name = " SERVER";
    }
    if (type == 'c') {
        name = " CLIENT";
    }

    Game game;
    sf::RenderWindow window(sf::VideoMode(game.screen_width, game.screen_height), "Multiplayer Proof of Concept: 'Air Hockey'" + name, sf::Style::Close);
    window.clear(sf::Color(0, 0, 0));
    window.display();

    if (type == 's') {
        Server server(window);
    }
    if (type == 'c') {
        Client client(window);
    }
    return 0;
}




