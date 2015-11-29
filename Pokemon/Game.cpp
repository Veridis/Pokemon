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
void Game::handlePlayerMovement(sf::Clock &clock, std::vector<std::vector<Tile*>> const &map)
{
    //Directions
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  || player->isInMovement(Player::UP)) {
        if(!player->isInMovement()) {
            sf::Vector2i nextBlockPosition = player->getNearCoord(Player::UP);
            sf::Vector2i playerPosition = player->getCoord();
            if(nextBlockPosition.y < 0) {
                return;
            }
            int blockType = map[playerPosition.y][playerPosition.x]->type;
            int nearBlockType = map[nextBlockPosition.y][nextBlockPosition.x]->type;
            if (player->checkColision(blockType, nearBlockType, Player::UP)) {
                return;
            }
        }
        
        player->moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || player->isInMovement(Player::RIGHT)) {
        if(!player->isInMovement()) {
            sf::Vector2i nextBlockPosition = player->getNearCoord(Player::RIGHT);
            sf::Vector2i playerPosition = player->getCoord();
            if(nextBlockPosition.x > map[0].size() - 1) {
                return;
            }
            int blockType = map[playerPosition.y][playerPosition.x]->type;
            int nearBlockType = map[nextBlockPosition.y][nextBlockPosition.x]->type;
            if (player->checkColision(blockType, nearBlockType, Player::RIGHT)) {
                return;
            }
        }
        player->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || player->isInMovement(Player::DOWN)) {
        if(!player->isInMovement()) {
            sf::Vector2i nextBlockPosition = player->getNearCoord(Player::DOWN);
            sf::Vector2i playerPosition = player->getCoord();
            if(nextBlockPosition.y > map.size() -1) {
                return;
            }
            int blockType = map[playerPosition.y][playerPosition.x]->type;
            int nearBlockType = map[nextBlockPosition.y][nextBlockPosition.x]->type;
            if (player->checkColision(blockType, nearBlockType, Player::DOWN)) {
                return;
            }
        }
        player->moveDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || player->isInMovement(Player::LEFT)) {
        if(!player->isInMovement()) {
            sf::Vector2i nextBlockPosition = player->getNearCoord(Player::LEFT);
            sf::Vector2i playerPosition = player->getCoord();
            if(nextBlockPosition.x < 0) {
                return;
            }
            int blockType = map[playerPosition.y][playerPosition.x]->type;
            int nearBlockType = map[nextBlockPosition.y][nextBlockPosition.x]->type;
            if (player->checkColision(blockType, nearBlockType, Player::LEFT)) {
                return;
            }
        }
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
    position.x = player->getPlayerSprite().getPosition().x + Tile::TILE_WIDTH/2 - WINDOW_WIDTH / 2;
    position.y = player->getPlayerSprite().getPosition().y + Tile::TILE_HEIGHT/2 - WINDOW_HEIGHT / 2;
    if (position.x < 0)
        position.x = 0;
    if (position.x > (mapRect.width * Tile::TILE_WIDTH) - Game::WINDOW_WIDTH)
        position.x = (mapRect.width * Tile::TILE_WIDTH) - Game::WINDOW_WIDTH;
    if (position.y < 0)
        position.y = 0;
    if (position.y > (mapRect.height * Tile::TILE_HEIGHT) - Game::WINDOW_HEIGHT)
        position.y = (mapRect.height * Tile::TILE_HEIGHT) - Game::WINDOW_HEIGHT;
    
    camera->reset(sf::FloatRect(position.x, position.y, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
    window->setView(*camera);
}
