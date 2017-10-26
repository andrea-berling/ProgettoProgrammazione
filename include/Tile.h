#ifndef TILE_H
#define TILE_H
#include <string>

enum tile_t { VOID, PAVEMENT, WALL, ROOM_BORDER, UP_STAIRS, DOWN_STAIRS};

class Tile
{
    private:

        tile_t type;
        std::string id;     // The id of the room
        std::string upperLayer;    // The id of the item/monster on the tile
        bool visible;
        char symbol;

        void setSymbol();
        // Sets the symbol of the tile given its type

    public:

        Tile();
        // Default constructor

        Tile(tile_t type);
        // Given a type, it creates a new tile (not visible)

        Tile(tile_t type, bool visible);
        // Given a type and a visible state, it creates a new tile

        Tile(tile_t type, std::string id, bool visible);
        // Given a type, a visible state and an id it creates a new tile

        tile_t getType();
        // Returns the type of the tile

        std::string getId();
        // Returns the id of the tile
        
        std::string getUpperLayer();
        // Returns the id of the item/monster on the tile, if present

        bool isVisible();
        // Returns true if the tile is visible

        char getSymbol();
        // Returns the symbol of the tile

        void setVisible(bool b);
        // Sets the visible state of the tile

        void setType(tile_t type);
        // Sets the type of the tile

        void setId(std::string id);
        // Sets the id of the tile

        void setUpperLayer(std::string id);
        // Sets the id of the tile

        bool isWalkable();
        // Returns true if the tile is walkable
};

#endif
