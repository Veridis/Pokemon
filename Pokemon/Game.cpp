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
    
    //Player Initialisation
    player = new Player();

}
Game::~Game()
{
    delete window;
    delete player;
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
