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

int TileMap::getWidth() const
{
    return bgMap[0].size();
}
int TileMap::getHeight() const
{
    return bgMap.size();
}

std::vector<std::vector<int>> TileMap::getColMap() const
{
    return colMap;
}


std::vector<std::vector<sf::Vector2i>> TileMap::load(const std::string &path)
{
    std::vector<sf::Vector2i> tmpMap;
    std::vector<std::vector<sf::Vector2i>> map;
    
    std::ifstream openfile(path);
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
    
    return map;

}

void TileMap::loadColisionsMap()
{
    std::vector<int> tmpMap;
    std::ifstream openfile(resourcePath() + MAPS_DIRECTORY + mapFileName + "-col.txt");
    
    if (openfile.is_open()) {
        while (!openfile.eof()) {
            std::string line, value;
            std::getline(openfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                tmpMap.push_back(atoi(value.c_str()));
            }
            colMap.push_back(tmpMap);
            tmpMap.clear();
        }
    } else
        std::cout << "ERROR : Unable to load the colMap " + mapFileName << std::endl;
}

void TileMap::loadMaps()
{
    bgMap = load(resourcePath() + MAPS_DIRECTORY + mapFileName + "-bg.txt");
    fgMap = load(resourcePath() + MAPS_DIRECTORY + mapFileName + "-fg.txt");
}

void TileMap::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < bgMap.size(); i++) {
        for(int j = 0; j < bgMap[i].size(); j++) {
            tiles.setPosition(j * TILE_HEIGHT, i * TILE_WIDTH);
            tiles.setTextureRect(sf::IntRect(bgMap[i][j].x * TILE_WIDTH, bgMap[i][j].y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
            window.draw(tiles);
            tiles.setTextureRect(sf::IntRect(fgMap[i][j].x * TILE_WIDTH, fgMap[i][j].y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
            window.draw(tiles);
        }
    }
}