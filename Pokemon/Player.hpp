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
    enum blockTypes {
        BLOCK_ERROR,
        BLOCK_BLOCK,
        BLOCK_EMPTY,
        BLOCK_WATER,
        BLOCK_GRASS,
        BLOCK_DOWN,
        BLOCK_RIGHT,
        BLOCK_UP,
        BLOCK_LEFT,
        BLOCK_HORIZONTAL,
        BLOCK_VERTICAL,
        BLOCK_WARP,
    };
    
    //Constructors
    Player();
    ~Player();
    
    //Methods/Functions
    sf::Texture& getPlayerTex() const;
    sf::Sprite& getPlayerSprite() const;
    sf::Vector2i& getSpriteCoord() const;
    sf::Vector2i getCoord() const;
    sf::Vector2i getNearCoord(int const &direction) const;
    
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void teleportTo(int const &x, int const &y);
    bool isInMovement(int const &direction) const;
    bool isInMovement() const;
    void animate();
    
    bool checkColision(int const &blockType, int const &nearBlockType, int const &walkingDirection) const;
    
private:
    sf::Texture *m_playerTex;
    sf::Sprite *m_playerSprite;
    sf::Vector2i *m_spriteCoord;
    
    bool m_isMoving;
    int m_destination_x;
    int m_destination_y;
    float m_playerSpeed;
};


#endif /* Player_hpp */
