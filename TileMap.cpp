//
//  Map.cpp
//  Pokemon
//
//  Created by Makdessi Alex on 27/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#include "TileMap.hpp"

const int TileMap::TILE_WIDTH = 32;
const int TileMap::TILE_HEIGHT = 32;

TileMap::TileMap()
{
    
}
TileMap::TileMap(const std::string& pTileSet, unsigned int pWidth, unsigned int pHeight, const std::vector<int>& pMap)
{
    tileSet = pTileSet;
    width = pWidth;
    height = pHeight;
    map = pMap;
}
TileMap::~TileMap()
{
    
}