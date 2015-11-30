//
//  Tile.cpp
//  Pokemon
//
//  Created by Makdessi Alex on 29/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#include "Tile.hpp"

const int Tile::TILE_WIDTH = 32;
const int Tile::TILE_HEIGHT = 32;

Tile::Tile()
{ 
    m_back = sf::Vector2i(0,0);
    m_middle = sf::Vector2i(0,0);
    m_front = sf::Vector2i(0,0);
}

Tile::~Tile()
{
    
}

sf::Vector2i Tile::getBack() const
{
    return m_back;
}
void Tile::setBack(sf::Vector2i const &back)
{
    m_back = back;
}
sf::Vector2i Tile::getMiddle() const
{
    return m_middle;
}
void Tile::setMiddle(sf::Vector2i const &middle)
{
    m_middle = middle;
}
sf::Vector2i Tile::getFront() const
{
    return m_front;
}
void Tile::setFront(sf::Vector2i const &front)
{
    m_front = front;
}
sf::Vector2i Tile::getMapPosition() const
{
    return m_mapPosition;
}
void Tile::setMapPosition(sf::Vector2i const &mapPosition)
{
    m_mapPosition = mapPosition;
}
int Tile::getType() const
{
    return m_type;
}
void Tile::setType(int const &type)
{
    m_type = type;
}