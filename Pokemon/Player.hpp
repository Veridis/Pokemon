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
    enum blockTypes {BLOCK_BLOCK, BLOCK_EMPTY, BLOCK_HORIZONTAL, BLOCK_VERTICAL, BLOCK_DOWN, BLOCK_RIGHT, BLOCK_UP, BLOCK_LEFT};
    
    //Constructors
    Player();
    ~Player();
    
    //Methods/Functions
    sf::Texture& getPlayerTex() const;
    sf::Sprite& getPlayerSprite() const;
    sf::Vector2i& getSpriteCoord() const;
    sf::Vector2i getCoord() const;
    sf::Vector2i getNearCoord(int direction) const;
    
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void teleportTo(int x, int y);
    bool isInMovement() const;
    void animate(bool);
    
    
private:
    sf::Texture *playerTex;
    sf::Sprite *playerSprite;
    sf::Vector2i *spriteCoord;
    
    bool isMoving;
    int destination_x;
    int destination_y;
    
    float playerSpeed;
};


#endif /* Player_hpp */
