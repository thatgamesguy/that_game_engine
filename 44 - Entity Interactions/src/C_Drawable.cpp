#include "C_Drawable.hpp"

C_Drawable::C_Drawable() : sortOrder(0), layer(DrawLayer::Default){}

C_Drawable::~C_Drawable(){}

void C_Drawable::SetSortOrder(int order)
{
    sortOrder = order;
}

int C_Drawable::GetSortOrder() const
{
    return sortOrder;
}

void C_Drawable::SetDrawLayer(DrawLayer drawLayer)
{
    layer = drawLayer;
}

DrawLayer C_Drawable::GetDrawLayer() const
{
    return layer;
}
