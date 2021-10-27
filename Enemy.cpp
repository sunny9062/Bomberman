#include "Enemy.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy(sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : Character(position, texture, imageCount, switchTime, speed)
{
    srand(time(0));
    updateCount = 0;
    direction = rand()%4;
    dead = false;
}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (updateCount > 500)  // Delays the change in direction
    {
        direction = rand()%4;
        updateCount = 0;
    }
    updateCount++;

    if (direction == 0)
    {
        movement.x -= speed * deltaTime;
    }
    if (direction == 1)
    {
        movement.x += speed * deltaTime;
    }
    if (direction == 2)
    {
        movement.y -= speed * deltaTime;
    }
    if (direction == 3)
    {
        movement.y += speed * deltaTime;
    }

    // Animation
    /*if (movement.x == 0.0f)
    {
        if (movement.y < 0)
        {
            row = 3; // backeard image
        }
        else
        {
            row = 0; // forward image
        }
    }
    else
    {
        row = 2;  // Right movement image
        if (movement.x > 0.0f)
        {
            faceRight = true;
        }
        else
        {
            faceRight = false;
        }
    }*/
    if (movement.x > 0.0f)
    {
        faceRight = true;
    }
    else
    {
        faceRight = false;
    }
    animation.UpdateHorizontal(row, deltaTime, false, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

void Enemy::checkCollisionForMap(TileMap& map)
{
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            int tileNumber = map.getTileNumber(getWidthNum() + i, getHeightNum() + j);
            if(tileNumber == 0){
                Collider temp = map.getColliderConcrete(getWidthNum() + i, getHeightNum() + j);
                if(getCollider().checkCollision(temp, 0.0f)){
                    direction = rand()%4;
                }
            }else if(tileNumber == 1){
                Collider temp = map.getColliderBox(getWidthNum() + i, getHeightNum() + j);
                if(getCollider().checkCollision(temp, 0.0f)){
                    direction = rand()%4;
                }
            }
        }
    }
}
