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
    
    //TileMap *map = new TileMap("palet-town/red-house/red-house");
    TileMap *map = new TileMap("palet-town/palet-town");
    map->load();
    map->loadColisionsMap();
    map->loadWarpMap();
    //game.getPlayer().teleportTo(3, 3);
    game.getPlayer().teleportTo(19, 22);
    game.setMap(map);
    
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
                        game.getPlayer().animate();
                    }                
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Space) {
                        sf::Vector2i position = game.getPlayer().getCoord();
                        sf::Vector2i near = game.getPlayer().getNearCoord(game.getPlayer().getSpriteCoord().y);
                        int type = map->getMap()[near.y][near.x]->getType();
                        std::cout<< "front type : " << type << std::endl;
                        std::cout << "current pos : " << position.x << ";" << position.y << std::endl;
                    }
            }
        }

        game.handleCamera(sf::FloatRect(0,0, map->getWidth(), map->getHeight()));
        //Drawing the map (back & middle)
        map->draw("back", game.getWindow());
        map->draw("middle", game.getWindow());
        //Drawing the player
        game.handlePlayerMovement(clock, map->getMap());
        game.getWindow().draw(game.getPlayer().getPlayerSprite());
        //Drawing the front map
        map->draw("front", game.getWindow());
        
        game.getWindow().display();
        game.getWindow().clear();
    }

    return EXIT_SUCCESS;
}
