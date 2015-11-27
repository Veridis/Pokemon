#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Game.hpp"

int main(int, char const**)
{
    Game game;
    sf::Clock clock;
    
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
                case sf::Event::KeyPressed:
                    game.getPlayer().setIsAnimated(true);
                    break;
                case sf::Event::KeyReleased:
                    game.getPlayer().setIsAnimated(false);
            }
        }
        
        game.handlePlayerMovement(clock);
                
        game.getWindow().draw(game.getPlayer().getPlayerSprite());
        game.getWindow().display();
        game.getWindow().clear();

    }

    return EXIT_SUCCESS;
}
