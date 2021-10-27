#ifndef TILEMAP_H
#define TILEMAP_H
#include <vector>
#include "Platform.h"
#include "Collider.h"
#include "score.h"
#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap() = default;
        TileMap(sf::Vector2f tileSize);
        virtual ~TileMap()= default;
        int getTileNumber(int widthNum, int heightNum);
        Collider getColliderConcrete(int widthNum, int heightNum);
        Collider getColliderBox(int widthNum, int heightNum);
        void breakBox(int widthNum, int heightNum);
        void cleanBurnt();
        void drawBricks(sf::RenderWindow& window);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::VertexArray grass_vertices;
        sf::Texture m_tileset;
        sf::Texture concrete;
        sf::Texture box;
        sf::Texture burntbox;
        std::vector<Platform> concretes;
        std::vector<Platform> boxes;
        // define the level with an array of tile indices
        int tiles[15 * 13] =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
            0, 2, 0, 1, 0, 2, 0, 1, 0, 1, 0, 1, 0, 2, 0,
            0, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 0,
            0, 1, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0, 1, 0,
            0, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 1, 0,
            0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0, 2, 0, 1, 0,
            0, 1, 1, 1, 2, 2, 2, 1, 2, 2, 1, 1, 1, 2, 0,
            0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0,
            0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 0,
            0, 2, 0, 1, 0, 1, 0, 2, 0, 1, 0, 1, 0, 2, 0,
            0, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        };

        unsigned int width;
        unsigned int height;
};

#endif // TILEMAP_H
