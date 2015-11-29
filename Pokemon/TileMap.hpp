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
    static const int TILE_WIDTH;
    static const int TILE_HEIGHT;
    static const std::string MAPS_DIRECTORY;
    static const sf::Color ALPHA_COLOR;

    //Constructors
    TileMap(std::string pMapFileName);
    ~TileMap();
    
    //Functions/Methods
    int getWidth() const;
    int getHeight() const;
    std::vector<std::vector<int>> getColMap() const;
    
    
    void load();
    void loadColisionsMap();
    void draw(std::string level,sf::RenderWindow &window);
    
    std::vector<std::vector<Tile*>> map;
    
private:
    sf::Texture tileTex;
    sf::Sprite tiles;
    
    std::vector<std::vector<sf::Vector2i>> bgMap;
    std::vector<std::vector<sf::Vector2i>> fgMap;
    std::vector<std::vector<int>> colMap;
    std::string mapFileName;

};

#endif /* TileMap_hpp */
