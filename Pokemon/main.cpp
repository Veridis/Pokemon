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
    map.loadColisionsMap();
    game.getPlayer().teleportTo(19, 22);
    
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "Musics/opening.ogg"))
        std::cout << "ERROR : Unable to load music";
    music.setLoop(true);
    music.play();
    
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
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Space) {
                        sf::Vector2i position = game.getPlayer().getCoord();
                        sf::Vector2i near = game.getPlayer().getNearCoord(game.getPlayer().getSpriteCoord().y);
                        int type = map.getColMap()[near.y][near.x];
                        std::cout<< "type : " << type << std::endl;
                    }
            }
        }

        game.handleCamera(sf::FloatRect(0,0, map.getWidth(), map.getHeight()));
        //Drawing the map (BG & FG)
        map.draw(game.getWindow());
        game.handlePlayerMovement(clock, map.getColMap());
        //Drawing the player
        game.getWindow().draw(game.getPlayer().getPlayerSprite());
        
        game.getWindow().display();
        game.getWindow().clear();
    }

    return EXIT_SUCCESS;
}
