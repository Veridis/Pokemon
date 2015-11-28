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
    
    TileMap map("palet-town");
    map.loadMaps();
    game.getPlayer().teleportTo(5, 5);
    
    /**/
    sf::View camera;
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
                    if (event.key.code == sf::Keyboard::Up
                        || event.key.code == sf::Keyboard::Right
                        || event.key.code == sf::Keyboard::Down
                        || event.key.code == sf::Keyboard::Left) {
                        game.getPlayer().animate(false);
                    }                
                    break;
            }
        }
        
        /**/
        camera.reset(sf::FloatRect(0,0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
        sf::Vector2f position(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
        position.x = game.getPlayer().getPlayerSprite().getPosition().x + 16 - Game::WINDOW_WIDTH / 2;
        position.y = game.getPlayer().getPlayerSprite().getPosition().y + 16 - Game::WINDOW_HEIGHT / 2;
        if (position.x < 0)
            position.x = 0;
        if (position.x > (map.getWidth() * TileMap::TILE_WIDTH) - Game::WINDOW_WIDTH)
            position.x = (map.getWidth() * TileMap::TILE_WIDTH) - Game::WINDOW_WIDTH;
        if (position.y < 0)
            position.y = 0;
        if (position.y > (map.getHeight() * TileMap::TILE_HEIGHT) - Game::WINDOW_HEIGHT)
            position.y = (map.getHeight() * TileMap::TILE_HEIGHT) - Game::WINDOW_HEIGHT;
        
        camera.reset(sf::FloatRect(position.x, position.y, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
        game.getWindow().setView(camera);
        /**/
        
        
        map.draw(game.getWindow());
        
        game.handlePlayerMovement(clock);
        game.getWindow().draw(game.getPlayer().getPlayerSprite());
        
        game.getWindow().display();
        game.getWindow().clear();

    }

    return EXIT_SUCCESS;
}
