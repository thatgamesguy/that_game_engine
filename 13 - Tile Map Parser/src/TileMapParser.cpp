#include "TileMapParser.hpp"

TileMapParser::TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator) : textureAllocator(textureAllocator){}

std::shared_ptr<MapData> TileMapParser::Parse(const std::string &file)
{
    MapData data;
    
    char* cstr = new char[file.size() + 1];
    //TODO: make multi format version of string copy
    strlcpy(cstr, file.c_str(), file.size() + 1); // Delete this line and uncomment the line below if you are using windows.
    //strcpy_s(cstr, file.size() + 1, file.c_str());
    
    //TODO: error checking - check file exists before attempting open.
    rapidxml::file<> xmlFile(cstr);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    
    xml_node<>* rootNode = doc.first_node("map");
    data.tileSize.x = std::atoi(rootNode->first_attribute("tilewidth")->value());
    data.tileSize.y = std::atoi(rootNode->first_attribute("tileheight")->value());
    data.size.x = std::atoi(rootNode->first_attribute("width")->value());
    data.size.y = std::atoi(rootNode->first_attribute("height")->value());
    
    std::shared_ptr<TileSheetData> tileSheetData = BuildTileSheetData(rootNode);
    data.tiles = BuildMapTiles(rootNode, tileSheetData);
    
    return std::make_shared<MapData>(data);
}

std::shared_ptr<TileSheetData> TileMapParser::BuildTileSheetData(xml_node<> *rootNode)
{
    TileSheetData tileSheetData;
    
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
    //TODO: add error checking - we want to output a message if the texture is not found:
    /*
    if(tileSheetData.textureId < 0)
    {
        // Texture not found.
    }
    */
    
    tileSheetData.imageSize.x = std::atoi(imageNode->first_attribute("width")->value());
    tileSheetData.imageSize.y = std::atoi(imageNode->first_attribute("height")->value());
    
    return std::make_shared<TileSheetData>(tileSheetData);
}

std::shared_ptr<MapTiles> TileMapParser::BuildMapTiles(xml_node<>* rootNode, std::shared_ptr<TileSheetData> tileSheetData)
{
    std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();
    
    for (xml_node<> * node = rootNode->first_node("layer"); node; node = node->next_sibling())
    {
        std::pair<std::string, std::shared_ptr<Layer>> mapLayer = BuildLayer(node, tileSheetData);
        map->emplace(mapLayer);
    }
    
    return map;
}

std::pair<std::string, std::shared_ptr<Layer>> TileMapParser::BuildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheetData> tileSheetData)
{
    TileSet tileSet;
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
            
            //TODO: add additional check to confirm that the character removals have worked:
            /*
            if(!Utilities::IsInteger(substr))
            {
                //String is still not integer.
            }
            */
        }
        
        int tileId = std::stoi(substr);
        
        if (tileId != 0)
        {
            auto itr = tileSet.find(tileId);
            if (itr == tileSet.end())
            {
                int textureX = tileId % tileSheetData->columns - 1;
                int textureY = tileId / tileSheetData->columns;
                
                std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(textureAllocator.Get(tileSheetData->textureId), tileId, textureX, textureY, tileSheetData->tileSize.x, tileSheetData->tileSize.y);
                
                itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
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

