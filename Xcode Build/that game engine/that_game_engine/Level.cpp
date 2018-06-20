#include "Level.hpp"

Level::Level(ResourceAllocator<sf::Texture>& textureAllocator) : mapParser(textureAllocator) {}

void Level::LoadMap(const std::string &filePath, sf::Vector2f mapOffset)
{
    map = mapParser.Parse(filePath);
    this->mapOffset = mapOffset;
}

void Level::Draw(Window& window)
{
    const unsigned int scale = 2;
    const unsigned int tileSize = map->tileSize.x;
    
    // Set up culling space
    sf::FloatRect viewSpace = window.GetViewSpace();
    sf::Vector2i tileBegin(floor(viewSpace.left / tileSize * scale), floor(viewSpace.top / tileSize * scale));
    sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / tileSize * scale), ceil((viewSpace.top + viewSpace.height) / tileSize * scale));
    
   
    for (int x = tileBegin.x; x <= tileEnd.x; ++x)
    {
        for (int y = tileBegin.y; y <= tileEnd.y; ++y)
        {
            if (x < 0 || y < 0 ) { continue; }
            if (x > map->size.x || y > map->size.y) { break; }
            
            std::vector<std::shared_ptr<Tile>> tiles = GetTiles(x, y);
            
            if (tiles.size() == 0) { continue; }
            
            for (auto& tile : tiles)
            {
                sf::Sprite& sprite = tile->properties->sprite;
                sf::Vector2f pos(mapOffset.x + (x * (tileSize * scale)), mapOffset.y + (y * (tileSize * scale)));
                sprite.setPosition(pos);
                sprite.setScale(scale, scale);
                window.Draw(sprite);
            }
          
        }
    }
}

std::vector<std::shared_ptr<Tile>> Level::GetTiles(unsigned int x, unsigned int y)
{
    std::vector<std::shared_ptr<Tile>> tiles;
    
    /*
    for(auto rit = map->rbegin(); rit != map->rend(); ++rit)
    {
        auto itr = rit->second->find(Utilities::To1DIndex(x, y, 100));
        if(itr != rit->second->end())
        {
            tiles.emplace_back(itr->second);
        }
    }
     */
    
    
    for(const auto& layer : *map->tiles)
    {
        auto itr = layer.second->find(Utilities::To1DIndex(x, y, map->size.x));
        if(itr != layer.second->end())
        {
            tiles.emplace_back(itr->second);
        }
    }
     
    
    return tiles;
}

