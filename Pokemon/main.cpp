#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Game.hpp"

#include <fstream>
#include <string>
#include <sstream>
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
    
    std::ifstream openfile(resourcePath() + "Maps/palette.txt");
    if (openfile.is_open()) {
        std::string tileLocation;
        std::getline(openfile, tileLocation);
        tileTex.loadFromFile(resourcePath() + tileLocation);
        tiles.setTexture(tileTex);
        while (!openfile.eof()) {
            std::string line, value;
            std::getline(openfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                int x = (atoi(value.c_str())-1) % (tileTex.getSize().x/32);
                int y = (atoi(value.c_str())-1) / (tileTex.getSize().x/32);
                
                tmpMap.push_back(sf::Vector2i(x, y));
            }
            map.push_back(tmpMap);
            tmpMap.clear();
        }
        /*
        while (!openfile.eof()) {
            std::string str, value;
            std::getline(openfile, str);
            std::stringstream stream(str);
            while (std::getline(stream, value, ' ')) {
                std::cout << value << std::endl;
                if(value.length() > 0) {
                    std::string xx = value.substr(0, value.find(','));
                    std::string yy = value.substr(value.find(',') + 1);
                    
                    int x, y, i, j;
                    for(i = 0; i < xx.length(); i++) {
                        if (!isdigit(xx[i]))
                            break;
                    }
                    for(j = 0; j < yy.length(); j++) {
                        if (!isdigit(yy[j]))
                            break;
                    }
                    
                    x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
                    y = (j == yy.length()) ? atoi(yy.c_str()) : -1;
                    
                    tmpMap.push_back(sf::Vector2i(x, y));
                }
            }
            
            map.push_back(tmpMap);
            tmpMap.clear();
        }*/
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
                tiles.setPosition(j*32, i*32);
                tiles.setTextureRect(sf::IntRect(map[i][j].x*32, map[i][j].y*32, 32, 32));
                game.getWindow().draw(tiles);
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
