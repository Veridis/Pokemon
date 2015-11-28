#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Game.hpp"
#include "TileMap.hpp"

int main(int, char const**)
{
    Game game;
    sf::Clock clock;
    
    TileMap map("bourg-palette.txt");
    map.load();
    
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
                    if (event.key.code == sf::Keyboard::Up
                        || event.key.code == sf::Keyboard::Right
                        || event.key.code == sf::Keyboard::Down
                        || event.key.code == sf::Keyboard::Left) {
                        game.getPlayer().animate(false);
                    }                
                    break;
            }
        }
        
        map.draw(game.getWindow());
        
        game.handlePlayerMovement(clock);
        game.getWindow().draw(game.getPlayer().getPlayerSprite());
        
        game.getWindow().display();
        game.getWindow().clear();

    }

    return EXIT_SUCCESS;
}
