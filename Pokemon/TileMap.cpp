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


TileMap::TileMap(std::string const pMapFileName)
{
    std::vector<Tile*> tmpMap;
    m_mapFileName = pMapFileName;
    //initialization of the map with empty tiles
    std::ifstream backfile(resourcePath() + "Maps/" + m_mapFileName + "/" + m_mapFileName + "-back.txt");
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
        std::cout << "ERROR : Unable to load the tilemap " + m_mapFileName << std::endl;
    
}
TileMap::~TileMap()
{
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            delete m_map[i][j];
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

void TileMap::load()
{
    std::string filenames [3] = {"-back.txt", "-middle.txt", "-front.txt"};
    std::vector<Tile> tmpMap;
    
    //Loading back map
    for(int f = 0; f < 3; f++) {
        std::ifstream backfile(resourcePath() + "Maps/" + m_mapFileName + "/" + m_mapFileName + filenames[f]);
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
            std::cout << "ERROR : Unable to load the tilemap " + m_mapFileName + filenames[f] << std::endl;
    }
}

void TileMap::loadColisionsMap()
{
    std::ifstream openfile(resourcePath() + MAPS_DIRECTORY + m_mapFileName + "/" + m_mapFileName + "-col.txt");
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
        std::cout << "ERROR : Unable to load the colMap " + m_mapFileName << std::endl;
}

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