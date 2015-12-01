//
//  TileMap.hpp
//  Pokemon
//
//  Created by Makdessi Alex on 27/11/2015.
//  Copyright © 2015 Makdessi Alex. All rights reserved.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Tile.hpp"
#include "Utils.hpp"

class TileMap
{
public:
    //constants declarations
    static const std::string MAPS_DIRECTORY;
    static const sf::Color ALPHA_COLOR;

    //Constructors
    TileMap(std::string const path);
    ~TileMap();
    
    //Functions/Methods
    int getWidth() const;
    int getHeight() const;
    std::vector<std::vector<Tile*>> getMap() const;
    std::vector<struct Warp> getWarpMap() const;
    
    
    void load();
    void loadColisionsMap();
    void loadWarpMap();
    void draw(std::string level,sf::RenderWindow &window);
private:
    sf::Texture m_tileTex;
    sf::Sprite m_tiles;
    
    std::vector<std::vector<Tile*>> m_map;
    //std::map<sf::Vector2i, std::string> m_warpMap;
    std::vector<struct Warp> m_warpMap;
    std::string m_path;

};

struct Warp {
    sf::Vector2i m_tile;
    int m_direction;
    std::string m_mapPath;
    sf::Vector2i m_destination;
};

#endif /* TileMap_hpp */
