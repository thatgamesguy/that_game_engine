#include "TileMapParser.hpp"

TileMapParser::TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator) : textureAllocator(textureAllocator){}

std::shared_ptr<Map> TileMapParser::Parse(const std::string &file)
{
    //TODO: we should clear any map data accumulated from last parse.
    
    char* cstr = new char[file.size() + 1];
    //TODO: make multi format version of string copy (windows version commented out)
    strlcpy(cstr, file.c_str(), file.size() + 1);
    //strcpy_s(cstr, file.size() + 1, file.c_str());
    
    //TODO: error checking - check file exists before attempting open
    rapidxml::file<> xmlFile(cstr);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    
    xml_node<>* rootNode = doc.first_node("map");
    
    BuildTileSheetData(rootNode);
    
    std::shared_ptr<Map> map = BuildMap(rootNode);
    
    return map;
}

void TileMapParser::BuildTileSheetData(xml_node<> *rootNode)
{
    xml_node<>* tilesheetNode = rootNode->first_node("tileset");
    
    //TODO: add error checking to ensure these values actually exist.
    //TODO: add support for multiple tile sets.
    int firstid = std::atoi(tilesheetNode->first_attribute("firstgid")->value()); //TODO: implement this.
    tileSheetData.tileSize.x = std::atoi(tilesheetNode->first_attribute("tilewidth")->value());
    tileSheetData.tileSize.y = std::atoi(tilesheetNode->first_attribute("tileheight")->value());
    tileSheetData.tileCount = std::atoi(tilesheetNode->first_attribute("tilecount")->value());
    tileSheetData.columns = std::atoi(tilesheetNode->first_attribute("columns")->value());
    tileSheetData.rows = tileSheetData.tileCount / tileSheetData.columns;
    
    xml_node<>* imageNode = tilesheetNode->first_node("image");
    tileSheetData.textureId = textureAllocator.Add(std::string(imageNode->first_attribute("source")->value()));
    //TODO: add error checking - we want to output a message if the texture is not found.
    
    tileSheetData.imageSize.x = std::atoi(imageNode->first_attribute("width")->value());
    tileSheetData.imageSize.y = std::atoi(imageNode->first_attribute("height")->value());
}

std::shared_ptr<Map> TileMapParser::BuildMap(xml_node<>* rootNode)
{
    std::shared_ptr<Map> map = std::make_shared<Map>();
    
    for (xml_node<> * node = rootNode->first_node("layer"); node; node = node->next_sibling())
    {
        std::pair<std::string, std::shared_ptr<Layer>> mapLayer = BuildLayer(node);
        map->emplace(mapLayer);
    }
    
    return map;
}

std::pair<std::string, std::shared_ptr<Layer>> TileMapParser::BuildLayer(xml_node<>* layerNode)
{
    std::shared_ptr<Layer> layer = std::make_shared<Layer>();
    
    int width = std::atoi(layerNode->first_attribute("width")->value());
    int height = std::atoi(layerNode->first_attribute("height")->value());
    
    xml_node<>* dataNode = layerNode->first_node("data");
    char* mapIndices = dataNode->value();
    
    std::stringstream fileStream(mapIndices);
    
    int count = 0;
    
    std::string line;
    while (fileStream.good())
    {
        std::string substr;
        std::getline(fileStream, substr, ',');
        
        if (!Utilities::IsInteger(substr))
        {
            substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());
            substr.erase(std::remove(substr.begin(), substr.end(), '\n'), substr.end());
            
            //TODO: add additional check to confirm that the character removals have worked.
        }
        
        int tileId = std::stoi(substr);
        
        if (tileId != 0)
        {
            auto itr = tileSet.find(tileId);
            if (itr == tileSet.end())
            {
                int textureX = tileId % tileSheetData.columns - 1;
                int textureY = tileId / tileSheetData.columns;
                
                std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(textureAllocator.Get(tileSheetData.textureId), tileId, textureX, textureY,
                                           tileSheetData.tileSize.x, tileSheetData.tileSize.y);
                
                tileSet.emplace(tileId, tileInfo);
                
                itr = tileSet.find(tileId); //TODO: can we return an iterator from a insert/emplace method.
            }
            
            std::shared_ptr<Tile> tile = std::make_shared<Tile>();
            // Bind properties of a tile from a set.
            tile->properties = itr->second;
            
            int tileX = count % width - 1;
            int tileY = count / width;
            
            if (!layer->emplace(Utilities::To1DIndex(tileX, tileY, width), tile).second)
            {
                // TODO: add output warning/error here.
            }
        }
        
        count++;
    }
    
    const std::string layerName = layerNode->first_attribute("name")->value();
    return std::make_pair(layerName, layer);
}

