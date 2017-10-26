#include "../include/Tile.h"

using namespace std;

Tile::Tile(): type(VOID), id(""), visible(false), symbol('?'),upperLayer("")
{
}

Tile::Tile(tile_t type): Tile()
{
    this->type = type;
    setSymbol();
}

Tile::Tile(tile_t type,bool visible): Tile(type) 
{
    this->visible = visible;
}

Tile::Tile(tile_t type, string id, bool visible): Tile(type,visible)
{
    this->id = id;
}

tile_t Tile::getType()
{
    return type;
}

string Tile::getId()
{
    return id;
}

bool Tile::isVisible()
{
    return visible;
}

char Tile::getSymbol()
{
    return symbol;
}

void Tile::setVisible(bool b)
{
    visible = b;
}

void Tile::setId(string id)
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

void Tile::setType(tile_t type)
{
    this->type = type;
    setSymbol();
}

std::string Tile::getUpperLayer()
{
    return upperLayer;
}

void Tile::setUpperLayer(std::string id)
{
    upperLayer = id;
}

bool Tile::isWalkable()
{
    return (type == PAVEMENT || type == UP_STAIRS || type == DOWN_STAIRS) && (upperLayer == "" || upperLayer[0] != 'm');
}
