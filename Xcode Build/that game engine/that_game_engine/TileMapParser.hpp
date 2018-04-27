#ifndef TileMapParser_hpp
#define TileMapParser_hpp

#include <SFML/Graphics.hpp>

#include "rapidxml.hpp"

struct TileSheetData
{
    int textureId;
    sf::Vector2u imageSize;
    int columns;
    int rows;
    sf::Vector2u tileSize;
    int tileCount;
};

struct MapData
{
    sf::Vector2u mapSize;
    int gravity;
};

struct TileMapSprite
{
    std::shared_ptr<TileSheetData> data;
    int tileSheetID;
};


#endif /* TileMapParser_hpp */
