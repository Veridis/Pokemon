//
//  Game.cpp
//  Pokemon
//
//  Created by Makdessi Alex on 26/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "Utils.hpp"

const int Game::WINDOW_WIDTH = 800;
const int Game::WINDOW_HEIGHT = 600;

Game::Game()
{
    frameCounter = 0;
    switchFrame = 100;
    frameSpeed = 1000;
    
    //Window Initialisation
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pokemon !", sf::Style::Close | sf::Style::Titlebar);
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "pokeball_icon.png")) {
        return EXIT_FAILURE;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //Player Initialisation
    player = new Player();

}

Game::~Game()
{
    delete window;
    delete player;
}

int Game::getFrameCounter() const
{
    return frameCounter;
}

void Game::incrementFrameCounter(int i)
{
    frameCounter += i;
}

void Game::resetFrameCounter()
{
    frameCounter = 0;
}

int Game::getSwitchFrame() const
{
    return switchFrame;
}

int Game::getFrameSpeed() const
{
    return frameSpeed;
}

sf::RenderWindow& Game::getWindow() const
{
    return *window;
}


Player& Game::getPlayer() const
{
    return *player;
}

void Game::handlePlayerMovement(sf::Clock &clock)
{
    sf::Vector2i spriteCoord(0, Player::Directions::DOWN);
    
    //Directions
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player->getSpriteCoord().y = Player::Directions::UP;
        player->getPlayerSprite().move(0, -.5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player->getSpriteCoord().y = Player::Directions::RIGHT;
        player->getPlayerSprite().move(.5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player->getSpriteCoord().y = Player::Directions::DOWN;
        player->getPlayerSprite().move(0, .5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player->getSpriteCoord().y = Player::Directions::LEFT;
        player->getPlayerSprite().move(-.5, 0);
    }
    
    //Boundary
    // Right edge
    if (player->getPlayerSprite().getPosition().x > Game::WINDOW_WIDTH - Player::SPRITE_WIDTH)
        player->getPlayerSprite().setPosition(Game::WINDOW_WIDTH - Player::SPRITE_WIDTH, player->getPlayerSprite().getPosition().y);
    //Top edge
    if (player->getPlayerSprite().getPosition().y < 0)
        player->getPlayerSprite().setPosition(player->getPlayerSprite().getPosition().x, 0);
    //Left edge
    if (player->getPlayerSprite().getPosition().x < 0)
        player->getPlayerSprite().setPosition(0, player->getPlayerSprite().getPosition().y);
    //Bottom edge
    if (player->getPlayerSprite().getPosition().y > Game::WINDOW_HEIGHT - Player::SPRITE_HEIGHT)
        player->getPlayerSprite().setPosition(player->getPlayerSprite().getPosition().x, Game::WINDOW_HEIGHT - Player::SPRITE_HEIGHT);
    
    
    //Animation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        frameCounter += frameSpeed * clock.restart().asSeconds();
        if (frameCounter >= switchFrame) {
            frameCounter = 0;
            player->getSpriteCoord().x++;
            if (player->getSpriteCoord().x * Player::SPRITE_WIDTH >= player->getPlayerTex().getSize().x) {
                player->getSpriteCoord().x = 0;
            }
        }
    } else {
        player->getSpriteCoord().x = 1;
    }
    
    player->getPlayerSprite().setTextureRect(sf::IntRect(
        player->getSpriteCoord().x * Player::SPRITE_WIDTH,
        player->getSpriteCoord().y * Player::SPRITE_HEIGHT,
        Player::SPRITE_WIDTH,
        Player::SPRITE_HEIGHT
    ));
}
