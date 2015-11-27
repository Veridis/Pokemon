//
//  Player.cpp
//  Pokemon
//
//  Created by Makdessi Alex on 26/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#include <iostream>

#include "Player.hpp"
#include "Utils.hpp"
#include "Game.hpp"

const int Player::SPRITE_WIDTH = 32;
const int Player::SPRITE_HEIGHT = 32;

Player::Player()
{
    playerTex = new sf::Texture;
    playerSprite = new sf::Sprite;
    spriteCoord = new sf::Vector2i;
    
    isAnimated = false;
    
    if (!playerTex->loadFromFile(resourcePath() + "male_player_walk.png"))
        std::cout << "ERROR : could not load player Texture" << std::endl;

    playerSprite->setTexture(*playerTex);
}
Player::~Player()
{
    delete playerTex;
    delete playerSprite;
    delete spriteCoord;
}

sf::Texture& Player::getPlayerTex() const
{
    return *playerTex;
}
sf::Sprite& Player::getPlayerSprite() const
{
    return *playerSprite;
}
sf::Vector2i& Player::getSpriteCoord() const
{
    return *spriteCoord;
}

/*
 Check for top edge boundary. Move up if OK
 */
void Player::moveUp()
{
    if (playerSprite->getPosition().y < 0) {
        playerSprite->setPosition(playerSprite->getPosition().x, 0);
        
        return;
    }
    
    spriteCoord->y = Directions::UP;
    playerSprite->move(0, -.5);
}
/*
 Check for left edge boundary. Move left if OK
 */
void Player::moveLeft()
{
    if (playerSprite->getPosition().x < 0) {
        playerSprite->setPosition(0, playerSprite->getPosition().y);
        
        return;
    }
    
    spriteCoord->y = Directions::LEFT;
    playerSprite->move(-.5, 0);
}
/*
 Check for bottom edge boundary. Move down if OK
 */
void Player::moveDown()
{
    if (playerSprite->getPosition().y > Game::WINDOW_HEIGHT - SPRITE_HEIGHT) {
        playerSprite->setPosition(playerSprite->getPosition().x, Game::WINDOW_HEIGHT - SPRITE_HEIGHT);
        
        return;
    }
    
    spriteCoord->y = Directions::DOWN;
    playerSprite->move(0, .5);
}
/*
 Check for right edge boundary. Move right if OK
 */
void Player::moveRight()
{
    if (playerSprite->getPosition().x > Game::WINDOW_WIDTH - SPRITE_WIDTH) {
        playerSprite->setPosition(Game::WINDOW_WIDTH - SPRITE_WIDTH, playerSprite->getPosition().y);
        
        return;
    }
    
    spriteCoord->y = Directions::RIGHT;
    playerSprite->move(.5, 0);
}
/*
 set if the sprite must be animated
 */
void Player::setIsAnimated(bool b)
{
    isAnimated = b;
}
/*
 return if the sprite is animated
 */
bool Player::isAnimate() const
{
    return isAnimated;
}
/*
 Animate the sprite if animate is equal to true.
 If animate is equal to false, reset the sprite position
 */
void Player::animate(bool animate = true)
{
    if (animate) {
        spriteCoord->x++;
        if (spriteCoord->x * SPRITE_WIDTH >= playerTex->getSize().x) {
            spriteCoord->x = 0;
        }
    } else {
        spriteCoord->x = 1;
    }
    
    playerSprite->setTextureRect(sf::IntRect(
        spriteCoord->x * SPRITE_WIDTH,
        spriteCoord->y * SPRITE_HEIGHT,
        SPRITE_WIDTH,
        SPRITE_HEIGHT
    ));
    
}