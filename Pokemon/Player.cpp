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
    m_playerTex = new sf::Texture;
    m_playerSprite = new sf::Sprite;
    m_spriteCoord = new sf::Vector2i;
    
    if (!m_playerTex->loadFromFile(resourcePath() + "Characters/male_player_walk.png"))
        std::cout << "ERROR : could not load player Texture" << std::endl;

    m_playerSprite->setTexture(*m_playerTex);
    m_playerSprite->setTextureRect(sf::IntRect(
        m_spriteCoord->x * SPRITE_WIDTH,
        m_spriteCoord->y * SPRITE_HEIGHT,
        SPRITE_WIDTH,
        SPRITE_HEIGHT
    ));

    m_isMoving = false;
    m_playerSpeed = .25f;
}
Player::~Player()
{
    delete m_playerTex;
    delete m_playerSprite;
    delete m_spriteCoord;
}

sf::Texture& Player::getPlayerTex() const
{
    return *m_playerTex;
}
sf::Sprite& Player::getPlayerSprite() const
{
    return *m_playerSprite;
}
sf::Vector2i& Player::getSpriteCoord() const
{
    return *m_spriteCoord;
}

sf::Vector2i Player::getCoord() const
{
    return sf::Vector2i(m_playerSprite->getPosition().x / SPRITE_WIDTH, m_playerSprite->getPosition().y / SPRITE_HEIGHT);
}
sf::Vector2i Player::getNearCoord(int const &direction) const
{
    sf::Vector2i position = getCoord();
    switch (direction) {
        case UP:
            position.y--;
            break;
        case RIGHT:
            position.x++;
            break;
        case DOWN:
            position.y++;
            break;
        case LEFT:
            position.x--;
            break;
    }
    
    return position;
}

/*
 Check for top edge boundary. Move up if OK
 */
void Player::moveUp()
{
    //Setting up the direction
    if (!m_isMoving) {
        m_spriteCoord->y = Directions::UP;
        m_isMoving = true;
        m_destination_y -= SPRITE_HEIGHT;
    }
    
    //Moving the sprite
    if (m_destination_y < m_playerSprite->getPosition().y)
        m_playerSprite->move(0, -m_playerSpeed);
    
    if (m_destination_x == m_playerSprite->getPosition().x && m_destination_y == m_playerSprite->getPosition().y)
        m_isMoving = false;
}
/*
 Check for left edge boundary. Move left if OK
 */
void Player::moveLeft()
{
    //Setting up the direction
    if (!m_isMoving) {
        m_spriteCoord->y = Directions::LEFT;
        m_isMoving = true;
        m_destination_x -= SPRITE_WIDTH;
    }
    
    //Moving the sprite
    if (m_destination_x < m_playerSprite->getPosition().x)
        m_playerSprite->move(-m_playerSpeed, 0);
    
    if (m_destination_x == m_playerSprite->getPosition().x && m_destination_y == m_playerSprite->getPosition().y)
        m_isMoving = false;
}
/*
 Check for bottom edge boundary. Move down if OK
 */
void Player::moveDown()
{
    //Setting up the direction
    if (!m_isMoving) {
        m_spriteCoord->y = Directions::DOWN;
        m_isMoving = true;
        m_destination_y += SPRITE_HEIGHT;
    }
    
    //Moving the sprite
    if (m_destination_y > m_playerSprite->getPosition().y)
        m_playerSprite->move(0, m_playerSpeed);
    
    if (m_destination_x == m_playerSprite->getPosition().x && m_destination_y == m_playerSprite->getPosition().y)
        m_isMoving = false;
}
/*
 Check for right edge boundary. Move right if OK
 */
void Player::moveRight()
{
    //Setting up the direction
    if (!m_isMoving) {
        m_spriteCoord->y = Directions::RIGHT;
        m_isMoving = true;
        m_destination_x += SPRITE_WIDTH;
    }
    
    //Moving the sprite
    if (m_destination_x > m_playerSprite->getPosition().x)
        m_playerSprite->move(m_playerSpeed, 0);
    
    if (m_destination_x == m_playerSprite->getPosition().x && m_destination_y == m_playerSprite->getPosition().y)
        m_isMoving = false;
}
void Player::teleportTo(int const &x, int const &y)
{
    m_playerSprite->setPosition(x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
    m_destination_x = m_playerSprite->getPosition().x;
    m_destination_y = m_playerSprite->getPosition().y;
}
/*
 return if the sprite is animated
 */
bool Player::isInMovement(int const &direction) const
{
    return m_spriteCoord->y == direction && m_isMoving;
}
bool Player::isInMovement() const
{
    return m_isMoving;
}
/*
 Animate the sprite if animate is equal to true.
 If animate is equal to false, reset the sprite position
 */
void Player::animate()
{
    if(!m_isMoving) {
        m_spriteCoord->x = 1;
    } else {
        m_spriteCoord->x++;
        if (m_spriteCoord->x * SPRITE_WIDTH >= m_playerTex->getSize().x) {
            m_spriteCoord->x = 0;
        }
    }
    
    m_playerSprite->setTextureRect(sf::IntRect(
        m_spriteCoord->x * SPRITE_WIDTH,
        m_spriteCoord->y * SPRITE_HEIGHT,
        SPRITE_WIDTH,
        SPRITE_HEIGHT
    ));
}

/*
 Return true if there is collision
 blockType : Current position block type
 nearBlockType : block type of the destination block
 */
bool Player::checkColision(int const &blockType, int const &nearBlockType, int const &walkingDirection) const
{
    switch (nearBlockType) {
        case BLOCK_BLOCK: {
            return true;
        }
        case BLOCK_EMPTY: {
            return false;
        }
        case BLOCK_WATER: {
            /* TODO : if swimming : return false */
            return true;
        }
        case BLOCK_GRASS: {
            /* TODO check for battle*/
            return false;
        }
        case BLOCK_DOWN: {
            if (walkingDirection == DOWN)
                return false;
            else
                return true;
            return false;
        }
        case BLOCK_RIGHT: {
            // TODO : check if already on block
            if (walkingDirection == RIGHT)
                return false;
            else
                return true;
            return false;
        }
        case BLOCK_UP: {
            // TODO : check if already on block
            if (walkingDirection == UP)
                return false;
            else
                return true;
        }
        case BLOCK_LEFT: {
            // TODO : check if already on block
            if (walkingDirection == LEFT)
                return false;
            else
                return true;
        }
        case BLOCK_HORIZONTAL: {
            if (blockType == BLOCK_HORIZONTAL) {
                return false;
            } else {
                if (walkingDirection == LEFT || walkingDirection == RIGHT)
                    return false;
                else
                    return true;
                return false;
            }
        }
        case BLOCK_VERTICAL: {
            if (blockType == BLOCK_VERTICAL) {
                return false;
            } else {
                if (walkingDirection == UP || walkingDirection == DOWN)
                    return false;
                else
                    return true;
            }
        }
        case BLOCK_WARP: {
            /* TODO */
            return false;
        }
    }
}