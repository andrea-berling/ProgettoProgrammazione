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

        Tile(const tile_t type);
        // Given a type, it creates a new tile (not visible)

        Tile(const tile_t type, const bool visible);
        // Given a type and a visible state, it creates a new tile

        Tile(const tile_t type, const std::string id, const bool visible);
        // Given a type, a visible state and an id it creates a new tile

        tile_t getType() const;
        // Returns the type of the tile

        std::string getId() const;
        // Returns the id of the tile
        
        std::string getUpperLayer() const;
        // Returns the id of the item/monster on the tile, if present

        bool isVisible() const;
        // Returns true if the tile is visible

        char getSymbol() const;
        // Returns the symbol of the tile

        void setVisible(const bool b);
        // Sets the visible state of the tile

        void setType(const tile_t type);
        // Sets the type of the tile

        void setId(const std::string id);
        // Sets the id of the tile

        void setUpperLayer(const std::string id);
        // Sets the id of the tile

        bool isWalkable() const;
        // Returns true if the tile is walkable
};

#endif
