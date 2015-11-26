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

const int Player::SPRITE_WIDTH = 32;
const int Player::SPRITE_HEIGHT = 32;

Player::Player()
{
    playerTex = new sf::Texture;
    playerSprite = new sf::Sprite;
    spriteCoord = new sf::Vector2i;
    
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