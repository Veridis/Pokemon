//
//  Player.hpp
//  Pokemon
//
//  Created by Makdessi Alex on 26/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Player
{
public:
    //constants declarations
    static const int SPRITE_WIDTH;
    static const int SPRITE_HEIGHT;
    enum Directions { DOWN, LEFT, RIGHT, UP };
    
    //Constructors
    Player();
    ~Player();
    
    //Methods/Functions
    sf::Texture& getPlayerTex() const;
    sf::Sprite& getPlayerSprite() const;
    sf::Vector2i& getSpriteCoord() const;
    
    
private:
    sf::Texture *playerTex;
    sf::Sprite *playerSprite;
    sf::Vector2i *spriteCoord;
};


#endif /* Player_hpp */
