#ifndef Tile_h
#define Tile_h

#include "ResourceAllocator.hpp"

// Stores common tile data.
struct TileInfo
{
    TileInfo() : tileID(-1)
    {
    }
    
    TileInfo(int textureID, unsigned int tileID, sf::IntRect textureRect) : textureID(textureID), tileID(tileID), textureRect(textureRect) { }
    
    int tileID;
    int textureID;
    sf::IntRect textureRect;
};

struct Tile
{
    std::shared_ptr<TileInfo> properties;
    int x;
    int y;
};

#endif /* Tile_h */
