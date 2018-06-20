#ifndef TileMapParser_hpp
#define TileMapParser_hpp

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>

#include "rapidxml.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Tile.h"
#include "Utilities.h"

using namespace rapidxml;

struct TileSheetData
{
    int textureId;
    sf::Vector2u imageSize;
    int columns;
    int rows;
    sf::Vector2u tileSize;
    int tileCount;
};

struct TileMapSprite
{
    std::shared_ptr<TileSheetData> data;
    int tileSheetID;
};

using Layer = std::unordered_map<unsigned int, std::shared_ptr<Tile>>; // Stores tile index and tile.
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>; // Stores layer names with layer.
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>; // Stores the different tile types that can be used.


struct MapData
{
    sf::Vector2u tileSize;
    sf::Vector2u size;
    std::shared_ptr<MapTiles> tiles;
};

class TileMapParser
{
public:
    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);
    
    std::shared_ptr<MapData> Parse(const std::string& file);
    
private:
    std::shared_ptr<TileSheetData> BuildTileSheetData(xml_node<>* rootNode);
    std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* rootNode, std::shared_ptr<TileSheetData> tileSheetData);
    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheetData> tileSheetData);
    
    ResourceAllocator<sf::Texture>& textureAllocator;
};


#endif /* TileMapParser_hpp */
