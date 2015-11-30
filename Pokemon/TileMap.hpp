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
    TileMap(std::string const pMapFileName);
    ~TileMap();
    
    //Functions/Methods
    int getWidth() const;
    int getHeight() const;
    std::vector<std::vector<Tile*>> getMap() const;
    
    
    void load();
    void loadColisionsMap();
    void draw(std::string level,sf::RenderWindow &window);
private:
    sf::Texture m_tileTex;
    sf::Sprite m_tiles;
    
    std::vector<std::vector<Tile*>> m_map;
    std::string m_mapFileName;

};

#endif /* TileMap_hpp */
