//
//  Game.hpp
//  Pokemon
//
//  Created by Makdessi Alex on 26/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Tile.hpp"

class Game
{
public:
    //constants declarations
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const float ANIMATION_TIME;
    
    //Constructors
    Game();
    ~Game();
    
    //Functions/Methods
    sf::RenderWindow& getWindow() const;
    
    Player& getPlayer() const;
    void handlePlayerMovement(sf::Clock &clock, std::vector<std::vector<Tile*>> const &map) const;
    void handleCamera(sf::FloatRect const &boundaries) const;
    
private:
    sf::RenderWindow *m_window;
    sf::View *m_camera;
    
    Player *m_player;
    
};

#endif /* Game_hpp */
