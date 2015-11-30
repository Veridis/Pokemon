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
    
    // Members
    sf::Vector2i back;
    sf::Vector2i middle;
    sf::Vector2i front;
    int type;
    
    //Functions/Methods
    
private:
    
    
};



#endif /* Tile_hpp */
