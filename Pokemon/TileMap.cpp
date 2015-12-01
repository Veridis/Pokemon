//
//  Map.cpp
//  Pokemon
//
//  Created by Makdessi Alex on 27/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#include "TileMap.hpp"

const std::string TileMap::MAPS_DIRECTORY = "Maps/";
const sf::Color TileMap::ALPHA_COLOR = sf::Color(0, 198, 198);

/*
 the 'path' parameter is the subfolder of the map.
 ex :
 "palet-town/palet-town" for palet-town-xxxx.txt
 "palet-town/red-house/red-house" for redhouse-xxxx.txt
 */
TileMap::TileMap(std::string const path)
{
    std::vector<Tile*> tmpMap;
    m_path = path;
    //initialization of the map with empty tiles
    std::ifstream backfile(resourcePath() + MAPS_DIRECTORY + m_path + "-back.txt");
    if (backfile.is_open()) {
        std::string tileLocation;
        std::getline(backfile, tileLocation);
        
        sf::Image image;
        image.loadFromFile(resourcePath() + tileLocation);
        image.createMaskFromColor(ALPHA_COLOR);
        m_tileTex.loadFromImage(image);
        m_tiles.setTexture(m_tileTex);
        
        while (!backfile.eof()) {
            std::string line, value;
            std::getline(backfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
            Tile *tile = new Tile();
                tmpMap.push_back(tile);
            }
            m_map.push_back(tmpMap);
            tmpMap.clear();
        }
    } else
        std::cout << "ERROR : Unable to load the tilemap " + m_path << std::endl;
    
}
TileMap::~TileMap()
{
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            delete m_map[j][i];
        }
    }
}

int TileMap::getWidth() const
{
    return m_map[0].size();
}
int TileMap::getHeight() const
{
    return m_map.size();
}

std::vector<std::vector<Tile*>> TileMap::getMap() const
{
    return m_map;
}

std::vector<struct Warp> TileMap::getWarpMap() const
{
    return m_warpMap;
}

/*
 Load the 3 layers of the map.
 The maps names must respect the following naming convention :
    Resources/Maps/{mapName}/{mapName}-[back|middle|front].txt
 back layer     : drawn first.
 middle layer   : drawn second and before the player. Handle alpha tiles.
 front layer    : draw third and after the player. Handle tiles that are supposed to be on the top of the player.
 */
void TileMap::load()
{
    std::string filenames [3] = {"-back.txt", "-middle.txt", "-front.txt"};
    std::vector<Tile> tmpMap;
    
    //Loading back map
    for(int f = 0; f < 3; f++) {
        std::ifstream backfile(resourcePath() + MAPS_DIRECTORY + m_path + filenames[f]);
        if (backfile.is_open()) {
            std::string tileLocation;
            std::getline(backfile, tileLocation);
            
            sf::Image image;
            image.loadFromFile(resourcePath() + tileLocation);
            image.createMaskFromColor(ALPHA_COLOR);
            m_tileTex.loadFromImage(image);
            m_tiles.setTexture(m_tileTex);
            
            int i = 0;
            while (!backfile.eof()) {
                int j = 0;
                std::string line, value;
                std::getline(backfile, line);
                std::stringstream stream(line);
                while (std::getline(stream, value, ',')) {
                    m_map[i][j]->setMapPosition(sf::Vector2i(j, i));
                    int x = (atoi(value.c_str())-1) % (m_tileTex.getSize().x / Tile::TILE_WIDTH);
                    int y = (atoi(value.c_str())-1) / (m_tileTex.getSize().x / Tile::TILE_HEIGHT);
                    if ("-back.txt" == filenames[f])
                        m_map[i][j]->setBack(sf::Vector2i(x, y));
                    else if ("-middle.txt" == filenames[f])
                        m_map[i][j]->setMiddle(sf::Vector2i(x, y));
                    else if ("-front.txt" == filenames[f])
                        m_map[i][j]->setFront(sf::Vector2i(x, y));
                    j++;
                }
                i++;
            }
        } else
            std::cout << "ERROR : Unable to load the tilemap " + m_path + filenames[f] << std::endl;
    }
}

/*
 Load the colision Map.
 The colision map must respect the following naming convention
 Resources/Maps/{mapName}/{mapName}-col.txt
 */
void TileMap::loadColisionsMap()
{
    std::ifstream openfile(resourcePath() + MAPS_DIRECTORY + m_path + "-col.txt");
    if (openfile.is_open()) {
        int i = 0;
        while (!openfile.eof()) {
            int j = 0;
            std::string line, value;
            std::getline(openfile, line);
            std::stringstream stream(line);
            while (std::getline(stream, value, ',')) {
                m_map[i][j]->setType(atoi(value.c_str()));
                j++;
            }
            i++;
        }
    } else
        std::cout << "ERROR : Unable to load the colision Map " + m_path << std::endl;
}

/*
 
 17|8|3|palet-town/red-house/red-house|11|2
 x_warpMap|y_warmMap|direction|path|x_dest|y_dest
 */
void TileMap::loadWarpMap()
{
    std::ifstream warpfile(resourcePath() + MAPS_DIRECTORY + m_path + "-warp.txt");
    if (warpfile.is_open()) {
        while (!warpfile.eof()) {
            std::string line, value;
            std::getline(warpfile, line);
            std::stringstream stream(line);
            
            std::getline(stream, value, '|'); int xtile = atoi(value.c_str());
            std::getline(stream, value, '|'); int ytile = atoi(value.c_str());
            std::getline(stream, value, '|'); int direction = atoi(value.c_str());
            std::getline(stream, value, '|'); std::string path = value;
            std::getline(stream, value, '|'); int xdest = atoi(value.c_str());
            std::getline(stream, value, '|'); int ydest = atoi(value.c_str());
            
            struct Warp warp;
            warp.m_tile = sf::Vector2i(xtile,ytile);
            warp.m_direction = direction;
            warp.m_mapPath = path;
            warp.m_destination = sf::Vector2i(xdest, ydest);
            m_warpMap.push_back(warp);
            
        }
    } else
        std::cout << "ERROR : Unable to load the warp Map " + m_path << std::endl;
}

/*
 draw the map according to the level layer.
 Available levels are "back", "middle", "front"
 */
void TileMap::draw(std::string level, sf::RenderWindow &window)
{
    for(int i = 0; i < m_map.size(); i++) {
        for(int j = 0; j < m_map[i].size(); j++) {
            m_tiles.setPosition(j * Tile::TILE_HEIGHT, i * Tile::TILE_WIDTH);
            if("back" == level) {
                m_tiles.setTextureRect(sf::IntRect(m_map[i][j]->getBack().x * Tile::TILE_WIDTH, m_map[i][j]->getBack().y * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
            } else if ("middle" == level) {
                m_tiles.setTextureRect(sf::IntRect(m_map[i][j]->getMiddle().x * Tile::TILE_WIDTH, m_map[i][j]->getMiddle().y * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
            } else if ("front" == level) {
                m_tiles.setTextureRect(sf::IntRect(m_map[i][j]->getFront().x * Tile::TILE_WIDTH, m_map[i][j]->getFront().y * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
            }
            window.draw(m_tiles);
        }
    }
}