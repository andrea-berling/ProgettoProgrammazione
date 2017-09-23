#include "../include/Tile.h"

using namespace std;

Tile::Tile(): type(VOID), id(""), visible(false), symbol('?')
{
}

Tile::Tile(tile_t type): type(type), id(""), visible(false)
{
    setSymbol();
}

Tile::Tile(tile_t type,bool visible): type(type), id(""), visible(visible)
{
    setSymbol();
}

Tile::Tile(tile_t type, string id, bool visible): type(type), id(id), visible(visible)
{
    setSymbol();
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
            symbol = ' ';
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
        case HALLWAY:
            symbol = ' ';
            break;
    }
}

void Tile::setType(tile_t type)
{
    this->type = type;
    setSymbol();
}
