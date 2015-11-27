#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Game.hpp"

#include <fstream>
#include <string>
#include <vector>

int main(int, char const**)
{
    Game game;
    sf::Clock clock;
    sf::Texture tileTex;
    sf::Sprite tiles;
    std::vector<std::vector<sf::Vector2i>> map;
    std::vector<sf::Vector2i> tmpMap;
    
    /**/
    
    std::ifstream openfile(resourcePath() + "Maps/bourg-palette.map");
    if (openfile.is_open()) {
        std::string tileLocation;
        openfile >> tileLocation;
        tileTex.loadFromFile(resourcePath() + tileLocation);
        tiles.setTexture(tileTex);
        
        while (!openfile.eof()) {
            std::string str;
            openfile >> str;
            char x = str[0], y = str[2];
            if(!isdigit(x) || !isdigit(y))
                tmpMap.push_back(sf::Vector2i(-1, -1));
            else
                tmpMap.push_back(sf::Vector2i(x - '0', y - '0'));
            
            if (openfile.peek() == '\n') {
                map.push_back(tmpMap);
                tmpMap.clear();
            }
        }
        map.push_back(tmpMap);
    } else
        std::cout << "ERROR" << std::endl;
    
    /**/
    
    
    // Start the game loop
    while (game.getWindow().isOpen())
    {
        // Process events
        sf::Event event;
        while (game.getWindow().pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    game.getWindow().close();
                    break;
                case sf::Event::KeyReleased:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        game.getPlayer().animate(false);
                    }
                    
                    break;
            }
        }
        
        /**/
        for(int i = 0; i < map.size(); i++) {
            for(int j = 0; j < map[i].size(); j++) {
                if (map[i][j].x != -1 && map[i][j].y != -1) {
                    tiles.setPosition(j*32, i*32);
                    tiles.setTextureRect(sf::IntRect(map[i][j].x*32, map[i][j].y*32, 32, 32));
                    game.getWindow().draw(tiles);
                }
            }
        }
        /**/
        
        game.handlePlayerMovement(clock);
        game.getWindow().draw(game.getPlayer().getPlayerSprite());
        
        game.getWindow().display();
        game.getWindow().clear();

    }

    return EXIT_SUCCESS;
}
