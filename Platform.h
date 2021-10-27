#ifndef PLATFORM_H
#define PLATFORM_H
#include "Collider.h"
#include <SFML/Graphics.hpp>


class Platform
{
    private:
        sf::RectangleShape body;
        int widthNum;
        int heightNum;
        bool broken;
    public:
        Platform() = default;
        Platform(sf::Texture* texture, sf::Vector2f tileSize, sf::Vector2f position, int widthNum, int heightNum);
        virtual ~Platform() = default;
        int getWidthNum() const{ return widthNum; }
        int getHeightNum() const{ return heightNum; }
        void Draw(sf::RenderWindow& window){ window.draw(body); }
        void changeTexture(sf::Texture* texture){ body.setTexture(texture); }
        bool checkBurnt(){ return broken; }
        void update() { broken = !broken; }
        Collider getCollider(){ return Collider(body);}
};

#endif // PLATFORM_H
