#ifndef Level_hpp
#define Level_hpp

#include "TileMapParser.hpp"
#include "Window.hpp"

class Level
{
public:
    Level(ResourceAllocator<sf::Texture>& textureAllocator);
    
    void LoadMap(const std::string& filePath, sf::Vector2f mapOffset);
    
    void Draw(Window& window);
    
private:
    TileMapParser mapParser;
    std::shared_ptr<MapData> map;
    sf::Vector2f mapOffset;
    
    std::vector<std::shared_ptr<Tile>> GetTiles(unsigned int x, unsigned int y);
};


#endif /* Level_hpp */
