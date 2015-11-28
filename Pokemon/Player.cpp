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
    
    if (!playerTex->loadFromFile(resourcePath() + "Characters/male_player_walk.png"))
        std::cout << "ERROR : could not load player Texture" << std::endl;

    playerSprite->setTexture(*playerTex);
    playerSprite->setTextureRect(sf::IntRect(
        spriteCoord->x * SPRITE_WIDTH,
        spriteCoord->y * SPRITE_HEIGHT,
        SPRITE_WIDTH,
        SPRITE_HEIGHT
    ));

    isMoving = false;
    playerSpeed = .25;
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
    if (!isMoving) {
        spriteCoord->y = Directions::UP;
        isMoving = true;
        destination_y -= SPRITE_HEIGHT;
    }
    
    if (destination_y < playerSprite->getPosition().y)
        playerSprite->move(0, -playerSpeed);
    
    if (destination_x == playerSprite->getPosition().x && destination_y == playerSprite->getPosition().y)
        isMoving = false;
}
/*
 Check for left edge boundary. Move left if OK
 */
void Player::moveLeft()
{
    if (!isMoving) {
        spriteCoord->y = Directions::LEFT;
        isMoving = true;
        destination_x -= SPRITE_WIDTH;
    }
    
    if (destination_x < playerSprite->getPosition().x)
        playerSprite->move(-playerSpeed, 0);
    
    if (destination_x == playerSprite->getPosition().x && destination_y == playerSprite->getPosition().y)
        isMoving = false;
}
/*
 Check for bottom edge boundary. Move down if OK
 */
void Player::moveDown()
{
    if (!isMoving) {
        spriteCoord->y = Directions::DOWN;
        isMoving = true;
        destination_y += SPRITE_HEIGHT;
    }
    
    if (destination_y > playerSprite->getPosition().y)
        playerSprite->move(0, playerSpeed);
    
    if (destination_x == playerSprite->getPosition().x && destination_y == playerSprite->getPosition().y)
        isMoving = false;
}
/*
 Check for right edge boundary. Move right if OK
 */
void Player::moveRight()
{
    if (!isMoving) {
        spriteCoord->y = Directions::RIGHT;
        isMoving = true;
        destination_x += SPRITE_WIDTH;
    }
    
    if (destination_x > playerSprite->getPosition().x)
        playerSprite->move(playerSpeed, 0);
    
    if (destination_x == playerSprite->getPosition().x && destination_y == playerSprite->getPosition().y)
        isMoving = false;
}
void Player::teleportTo(int x, int y)
{
    playerSprite->setPosition(x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
    destination_x = playerSprite->getPosition().x;
    destination_y = playerSprite->getPosition().y;
}
/*
 return if the sprite is animated
 */
bool Player::isInMovement() const
{
    return isMoving;
}
/*
 Animate the sprite if animate is equal to true.
 If animate is equal to false, reset the sprite position
 */
void Player::animate(bool)
{
    if(!isMoving) {
        spriteCoord->x = 1;
    } else {
        spriteCoord->x++;
        if (spriteCoord->x * SPRITE_WIDTH >= playerTex->getSize().x) {
            spriteCoord->x = 0;
        }
    }
    
    playerSprite->setTextureRect(sf::IntRect(
        spriteCoord->x * SPRITE_WIDTH,
        spriteCoord->y * SPRITE_HEIGHT,
        SPRITE_WIDTH,
        SPRITE_HEIGHT
    ));
    
}