//
//  TileMap.hpp
//  Pokemon
//
//  Created by Makdessi Alex on 27/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>

class TileMap
{
public:
    //constants declarations
    static const int TILE_WIDTH;
    static const int TILE_HEIGHT;

    //Constructors
    TileMap();
    TileMap(const std::string& pTileSet, unsigned int pWidth, unsigned int pHeight, const std::vector<int>& pMap);
    ~TileMap();
    
    //Functions/Methods
    
private:
    unsigned int width;
    unsigned int height;
    std::string tileSet;
    sf::Vector2u tileSize;
    std::vector<int> map;

};

#endif /* TileMap_hpp */
