//
//  Tile.hpp
//  Pokemon
//
//  Created by Makdessi Alex on 29/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


class Tile{
public:
    //constants declarations
    static const int TILE_WIDTH;
    static const int TILE_HEIGHT;
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
    Tile();
    ~Tile();

    //Functions/Methods
    sf::Vector2i getBack() const;
    void setBack(sf::Vector2i const &back);
    sf::Vector2i getMiddle() const;
    void setMiddle(sf::Vector2i const &middle);
    sf::Vector2i getFront() const;
    void setFront(sf::Vector2i const &front);
    int getType() const;
    void setType(int const &type);
    
private:
    // Members
    sf::Vector2i m_back;
    sf::Vector2i m_middle;
    sf::Vector2i m_front;
    int m_type;
    
};



#endif /* Tile_hpp */
