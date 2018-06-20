#ifndef Tile_h
#define Tile_h

#include "ResourceAllocator.hpp"

// Stores common tile data.
struct TileInfo
{
    TileInfo() : tileID(-1)
    {
    }
    
    TileInfo(std::shared_ptr<sf::Texture> spriteTexture, unsigned int tileID, int x, int y, int width, int height) : tileID(tileID)
    {
        sprite.setTexture(*spriteTexture);
        sf::IntRect tileBoundaries(x * width, y * width, width, height);
        sprite.setTextureRect(tileBoundaries);
    }
    
    sf::Sprite sprite;
    int tileID;
};

struct Tile
{
    // Currently a tile only has properties that are common to all tiles.
    std::shared_ptr<TileInfo> properties;
};

#endif /* Tile_h */
