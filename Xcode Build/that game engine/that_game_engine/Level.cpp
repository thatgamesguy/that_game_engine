#include "Level.hpp"

Level::Level(ResourceAllocator<sf::Texture>& textureAllocator) : mapParser(textureAllocator) {}

void Level::LoadMap(const std::string &filePath, sf::Vector2f mapOffset)
{
    map = mapParser.Parse(filePath);
    this->mapOffset = mapOffset;
}

void Level::Draw(Window& window)
{
    const unsigned int tileSize = 32;
   // const float halfTilesize = tileSize * 0.5f;
    
    // Set up culling space
    sf::FloatRect viewSpace = window.GetViewSpace();
    sf::Vector2i tileBegin(floor(viewSpace.left / tileSize), floor(viewSpace.top / tileSize));
    sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / tileSize), ceil((viewSpace.top + viewSpace.height) / tileSize));
    
    const unsigned int xMax = 100;
    const unsigned int yMax = 40;
    
    for (int x = tileBegin.x; x <= tileEnd.x; ++x)
    {
        for (int y = tileBegin.y; y <= tileEnd.y; ++y)
        {
            if (x < 0 || y < 0 ) { continue; }
            if (x > xMax || y > yMax) { break; }
            
            std::vector<std::shared_ptr<Tile>> tiles = GetTiles(x, y);
            
            if (tiles.size() == 0) { continue; }
            
            for (auto& tile : tiles)
            {
                sf::Sprite& sprite = tile->properties->sprite;
                sprite.setPosition(mapOffset.x + (x * tileSize), mapOffset.y + (y * tileSize));
                sprite.setScale(1.f, 1.f);
                window.Draw(sprite);
            }
          
        }
    }
}

std::vector<std::shared_ptr<Tile>> Level::GetTiles(unsigned int x, unsigned int y)
{
    std::vector<std::shared_ptr<Tile>> tiles;
    
    for(const auto& layer : *map)
    {
        auto itr = layer.second->find(Utilities::To1DIndex(x, y, 100));
        if(itr != layer.second->end())
        {
            tiles.emplace_back(itr->second);
        }
    }
    
    return tiles;
}

