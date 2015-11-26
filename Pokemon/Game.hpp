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

class Game
{
public:
    //constants declarations
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    
    //Constructors
    Game();
    ~Game();
    
    //Functions/Methods
    sf::RenderWindow& getWindow() const;
    int getFrameCounter() const;
    void incrementFrameCounter(int i);
    void resetFrameCounter();
    int getFrameSpeed() const;
    int getSwitchFrame() const;
    
    Player& getPlayer() const;
    void handlePlayerMovement(sf::Clock &clock);
    
private:
    int frameCounter;
    int frameSpeed;
    int switchFrame;
    
    sf::RenderWindow *window;
    
    Player *player;
    
};

#endif /* Game_hpp */
