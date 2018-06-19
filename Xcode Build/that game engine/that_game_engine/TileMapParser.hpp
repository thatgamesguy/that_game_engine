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

/*
struct MapData
{
    sf::Vector2u mapSize;
    int gravity;
};
 */

struct TileMapSprite
{
    std::shared_ptr<TileSheetData> data;
    int tileSheetID;
};

using Layer = std::unordered_map<unsigned int, std::shared_ptr<Tile>>; // Stores tile index and tile.
using Map = std::unordered_map<std::string, std::shared_ptr<Layer>>; // Stores layer names with layer.
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>; // Stores different tile types that can be used.

class TileMapParser
{
public:
    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);
    
    std::shared_ptr<Map> Parse(const std::string& file);
    
private:
    void BuildTileSheetData(xml_node<>* rootNode);
    std::shared_ptr<Map>  BuildMap(xml_node<>* rootNode);
    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(xml_node<>* layerNode);
    
    ResourceAllocator<sf::Texture>& textureAllocator;
    TileSheetData tileSheetData;
    TileSet tileSet;
};


#endif /* TileMapParser_hpp */
