#include "../include/Tile.h"

using namespace std;

Tile::Tile(): type(VOID), id(""), visible(false), symbol('?'),upperLayer("")
{
}

Tile::Tile(const tile_t type): Tile()
{
    this->type = type;
    setSymbol();
}

Tile::Tile(const tile_t type, const bool visible): Tile(type) 
{
    this->visible = visible;
}

Tile::Tile(const tile_t type, const string id, const bool visible): Tile(type,visible)
{
    this->id = id;
}

tile_t Tile::getType() const
{
    return type;
}

string Tile::getId() const
{
    return id;
}

bool Tile::isVisible() const
{
    return visible;
}

char Tile::getSymbol() const
{
    return symbol;
}

void Tile::setVisible(const bool b)
{
    visible = b;
}

void Tile::setId(const string id)
{
    this->id = id;
} 

void Tile::setSymbol()
{
    switch(type)
    {
        case VOID:
            symbol = '&';
            break;
        case PAVEMENT:
            symbol = ' ';
            break;
        case WALL:
            symbol = '#';
            break;
        case ROOM_BORDER:
            symbol = '%';
            break;
        case UP_STAIRS:
            symbol = '/';
            break;
        case DOWN_STAIRS:
            symbol = '\\';
            break;
    }
}

void Tile::setType(const tile_t type)
{
    this->type = type;
    setSymbol();
}

std::string Tile::getUpperLayer() const
{
    return upperLayer;
}

void Tile::setUpperLayer(const std::string id)
{
    upperLayer = id;
}

bool Tile::isWalkable() const
{
    return (type == PAVEMENT || type == UP_STAIRS || type == DOWN_STAIRS) && (upperLayer == "" || upperLayer[0] != 'm');
}
