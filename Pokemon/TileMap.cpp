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
const std::string TileMap::MAPS_DIRECTORY = "Maps/";
const sf::Color TileMap::ALPHA_COLOR = sf::Color(0, 198, 198);


TileMap::TileMap(std::string pMapFileName)
{
    mapFileName = pMapFileName;
}
TileMap::~TileMap()
{
    
}

int TileMap::getWidth()
{
    return map[0].size();
}
int TileMap::getHeight()
{
    return map.size();
}

void TileMap::load()
{
    std::vector<sf::Vector2i> tmpMap;
    
    std::ifstream openfile(resourcePath() + MAPS_DIRECTORY + mapFileName);
    if (openfile.is_open()) {
        std::string tileLocation;
        std::getline(openfile, tileLocation);
        
        sf::Image image;
        image.loadFromFile(resourcePath() + tileLocation);
        image.createMaskFromColor(ALPHA_COLOR);
        
        tileTex.loadFromImage(image);
        tiles.setTexture(tileTex);
        while (!openfile.eof()) {
            std::string line, value;
            std::getline(openfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                int x = (atoi(value.c_str())-1) % (tileTex.getSize().x / TILE_WIDTH);
                int y = (atoi(value.c_str())-1) / (tileTex.getSize().x / TILE_HEIGHT);
                
                tmpMap.push_back(sf::Vector2i(x, y));
            }
            map.push_back(tmpMap);
            tmpMap.clear();
        }
    } else
        std::cout << "ERROR : Unable to load the tilemap " + mapFileName << std::endl;

}

void TileMap::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            tiles.setPosition(j * TILE_HEIGHT, i * TILE_WIDTH);
            tiles.setTextureRect(sf::IntRect(map[i][j].x * TILE_WIDTH, map[i][j].y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
            window.draw(tiles);
        }
    }
}