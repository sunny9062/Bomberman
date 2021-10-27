#include "Character.h"
#include <SFML/Graphics.hpp>

Character::Character(sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
    body.setPosition(position);
    body.setTexture(texture);
}

Character::~Character() {}

void Character::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

int Character::getWidthNum()
{
    int widthNum = body.getPosition().x / 48;
    return widthNum;
}

int Character::getHeightNum()
{
    int heightNum = body.getPosition().y / 48;
    return heightNum;
}
