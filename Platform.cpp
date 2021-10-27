#include "Platform.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>

Platform::Platform(sf::Texture* texture, sf::Vector2f tileSize, sf::Vector2f position, int widthNum, int heightNum)
{
    body.setSize(tileSize);
    body.setOrigin(tileSize.x / 2, tileSize.y / 2);
    body.setTexture(texture);
    body.setPosition(position);
    this->widthNum = widthNum;
    this->heightNum = heightNum;
    broken = false;
}
