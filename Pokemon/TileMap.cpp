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
    std::vector<Tile*> tmpMap;
    mapFileName = pMapFileName;
    //initialization of the map with empty tiles
    std::ifstream backfile(resourcePath() + "Maps/" + mapFileName + "/" + mapFileName + "-back.txt");
    if (backfile.is_open()) {
        std::string tileLocation;
        std::getline(backfile, tileLocation);
        
        sf::Image image;
        image.loadFromFile(resourcePath() + tileLocation);
        image.createMaskFromColor(ALPHA_COLOR);
        tileTex.loadFromImage(image);
        tiles.setTexture(tileTex);
        
        while (!backfile.eof()) {
            std::string line, value;
            std::getline(backfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
            Tile *tile = new Tile();
                tmpMap.push_back(tile);
            }
            map.push_back(tmpMap);
            tmpMap.clear();
        }
    } else
        std::cout << "ERROR : Unable to load the tilemap " + mapFileName << std::endl;
    
}
TileMap::~TileMap()
{
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            delete map[i][j];
        }
    }
}

int TileMap::getWidth() const
{
    return map[0].size();
}
int TileMap::getHeight() const
{
    return map.size();
}

std::vector<std::vector<Tile*>> TileMap::getMap() const
{
    return map;
}

void TileMap::load()
{
    std::vector<Tile> tmpMap;
    
    //Loading back map
    std::ifstream backfile(resourcePath() + "Maps/" + mapFileName + "/" + mapFileName + "-back.txt");
    if (backfile.is_open()) {
        std::string tileLocation;
        std::getline(backfile, tileLocation);
        
        sf::Image image;
        image.loadFromFile(resourcePath() + tileLocation);
        image.createMaskFromColor(ALPHA_COLOR);
        tileTex.loadFromImage(image);
        tiles.setTexture(tileTex);
        
        int i = 0;
        while (!backfile.eof()) {
            int j = 0;
            std::string line, value;
            std::getline(backfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                int x = (atoi(value.c_str())-1) % (tileTex.getSize().x / TILE_WIDTH);
                int y = (atoi(value.c_str())-1) / (tileTex.getSize().x / TILE_HEIGHT);
                map[i][j]->back.x = x;
                map[i][j]->back.y = y;
                j++;
            }
            i++;
        }
    } else
        std::cout << "ERROR : Unable to load the tilemap " + mapFileName << std::endl;
    
    //Loading middle map
    std::ifstream middlefile(resourcePath() + "Maps/" + mapFileName + "/" + mapFileName + "-middle.txt");
    if (middlefile.is_open()) {
        std::string tileLocation;
        std::getline(middlefile, tileLocation);
        
        sf::Image image;
        image.loadFromFile(resourcePath() + tileLocation);
        image.createMaskFromColor(ALPHA_COLOR);
        tileTex.loadFromImage(image);
        tiles.setTexture(tileTex);
        
        int i = 0;
        while (!middlefile.eof()) {
            int j = 0;
            std::string line, value;
            std::getline(middlefile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                int x = (atoi(value.c_str())-1) % (tileTex.getSize().x / TILE_WIDTH);
                int y = (atoi(value.c_str())-1) / (tileTex.getSize().x / TILE_HEIGHT);
                map[i][j]->middle.x = x;
                map[i][j]->middle.y = y;
                j++;
            }
            i++;
        }

    } else
        std::cout << "ERROR : Unable to load the tilemap " + mapFileName << std::endl;
    
    //Loading front map
    std::ifstream frontfile(resourcePath() + "Maps/" + mapFileName + "/" + mapFileName + "-front.txt");
    if (frontfile.is_open()) {
        std::string tileLocation;
        std::getline(frontfile, tileLocation);
        
        sf::Image image;
        image.loadFromFile(resourcePath() + tileLocation);
        image.createMaskFromColor(ALPHA_COLOR);
        tileTex.loadFromImage(image);
        tiles.setTexture(tileTex);
        
        int i = 0;
        while (!frontfile.eof()) {
            int j = 0;
            std::string line, value;
            std::getline(frontfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                int x = (atoi(value.c_str())-1) % (tileTex.getSize().x / TILE_WIDTH);
                int y = (atoi(value.c_str())-1) / (tileTex.getSize().x / TILE_HEIGHT);
                map[i][j]->front.x = x;
                map[i][j]->front.y = y;
                j++;
            }
            i++;
        }
    } else
        std::cout << "ERROR : Unable to load the tilemap " + mapFileName << std::endl;
}

void TileMap::loadColisionsMap()
{
    std::ifstream openfile(resourcePath() + MAPS_DIRECTORY + mapFileName + "/" + mapFileName + "-col.txt");
    if (openfile.is_open()) {
        int i = 0;
        while (!openfile.eof()) {
            int j = 0;
            std::string line, value;
            std::getline(openfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                map[i][j]->type = atoi(value.c_str());
                j++;
            }
            i++;
        }
    } else
        std::cout << "ERROR : Unable to load the colMap " + mapFileName << std::endl;
}

void TileMap::draw(std::string level, sf::RenderWindow &window)
{
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            tiles.setPosition(j * TILE_HEIGHT, i * TILE_WIDTH);
            if("back" == level) {
                tiles.setTextureRect(sf::IntRect(map[i][j]->back.x * Tile::TILE_WIDTH, map[i][j]->back.y * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
            } else if ("middle" == level) {
                tiles.setTextureRect(sf::IntRect(map[i][j]->middle.x * Tile::TILE_WIDTH, map[i][j]->middle.y * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
            } else if ("front" == level) {
                tiles.setTextureRect(sf::IntRect(map[i][j]->front.x * Tile::TILE_WIDTH, map[i][j]->front.y * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
            }
            window.draw(tiles);
        }
    }
}