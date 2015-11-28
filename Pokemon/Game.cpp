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
#include "TileMap.hpp"
#include "Player.hpp"
#include "Utils.hpp"

const int Game::WINDOW_WIDTH = 800;
const int Game::WINDOW_HEIGHT = 600;
const float Game::ANIMATION_TIME = 100;

Game::Game()
{
    //Window Initialisation
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pokemon !", sf::Style::Close | sf::Style::Titlebar);
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "pokeball_icon.png")) {
        return EXIT_FAILURE;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    camera = new sf::View();
    
    //Player Initialisation
    player = new Player();

}
Game::~Game()
{
    delete window;
    delete player;
    delete camera;
}


sf::RenderWindow& Game::getWindow() const
{
    return *window;
}
Player& Game::getPlayer() const
{
    return *player;
}

/*
 Handle event and keyboards keys for player movements
 */
void Game::handlePlayerMovement(sf::Clock &clock)
{
    sf::Vector2i spriteCoord(0, Player::Directions::DOWN);
    
    //Directions
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  || player->isInMovement()) {
        player->moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || player->isInMovement()) {
        player->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || player->isInMovement()) {
        player->moveDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || player->isInMovement()) {
        player->moveLeft();
    }
    
    if (clock.getElapsedTime().asMilliseconds() > ANIMATION_TIME) {
        player->animate(true);
        clock.restart();
    }
}

void Game::handleCamera(sf::FloatRect mapRect)
{
    camera->reset(sf::FloatRect(0,0, WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::Vector2f position(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    position.x = player->getPlayerSprite().getPosition().x + TileMap::TILE_WIDTH/2 - WINDOW_WIDTH / 2;
    position.y = player->getPlayerSprite().getPosition().y + TileMap::TILE_HEIGHT/2 - WINDOW_HEIGHT / 2;
    if (position.x < 0)
        position.x = 0;
    if (position.x > (mapRect.width * TileMap::TILE_WIDTH) - Game::WINDOW_WIDTH)
        position.x = (mapRect.width * TileMap::TILE_WIDTH) - Game::WINDOW_WIDTH;
    if (position.y < 0)
        position.y = 0;
    if (position.y > (mapRect.height * TileMap::TILE_HEIGHT) - Game::WINDOW_HEIGHT)
        position.y = (mapRect.height * TileMap::TILE_HEIGHT) - Game::WINDOW_HEIGHT;
    
    camera->reset(sf::FloatRect(position.x, position.y, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
    window->setView(*camera);
}
