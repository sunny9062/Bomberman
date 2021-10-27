#include "Player.h"
#include "Bomb.h"
#include "TileMap.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Player::Player(sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
    : Character(position, texture, imageCount, switchTime, speed), bomb(nullptr)
{
    bombTexture.loadFromFile("BombExplode.png");
    fireballMove.loadFromFile("fireballMove.png");
    fireballDie.loadFromFile("fireballDie.png");
    //direction = 0;
}

Player::~Player() {}

void Player::update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        movement.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        movement.x += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        movement.y -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        movement.y += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        if(bomb == nullptr){
            bomb = new Bomb(&bombTexture, &fireballMove, &fireballDie, sf::Vector2u(12,1)
                            , sf::Vector2u(1,6), sf::Vector2f(getWidthNum()*48.0f + 24.0f, getHeightNum()*48.0f + 24.0f), 0.1f, speed * 2);
        }
    }

    // Animation
    /*if (movement.x == 0.0f)
    {
        if (movement.y < 0)
        {
            row = 0;    // backward facing image
            direction = 4;

        }else if(movement.y > 0)
        {
            row = 0;    // forward facing image
            direction = 2;
        }else{
            direction = 0;
        }
    }
    else
    {
        row = 0;   // Right facing image
        if (movement.x > 0.0f)
        {
            faceRight = true;
            direction = 1;
        }
        else
        {
            faceRight = false;
            direction = 3;
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
    if(bomb != nullptr){
        bomb->Update(deltaTime);
        if(bomb->checkFinished()){
            bomb = nullptr;
        }
    }
    animation.UpdateVertical(row, deltaTime, false, false, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

void Player::draw(sf::RenderWindow& window)
{
    if(bomb != nullptr){
        bomb->Draw(window);
    }
    window.draw(body);
}

void Player::checkCollisionForMap(TileMap& map)
{
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            int tileNumber = map.getTileNumber(getWidthNum() + i, getHeightNum() + j);
            if(tileNumber == 0){
                Collider temp = map.getColliderConcrete(getWidthNum() + i, getHeightNum() + j);
                getCollider().checkCollision(temp, 0.0f);
            }else if(tileNumber == 1){
                Collider temp = map.getColliderBox(getWidthNum() + i, getHeightNum() + j);
                getCollider().checkCollision(temp, 0.0f);
            }
        }
    }
    if(bomb != nullptr){
        bomb->checkFireballCollision(map);
    }
}

bool Player::checkCollisionForFireball()
{
    if(bomb != nullptr){
        Collider bombCollider = bomb->getColliderBomb();
        if(getCollider().checkCollision(bombCollider) && bomb->checkExplosion()){
            std::cout << "You are Dead: bomb itself" << std::endl;
            return true;
        }
        if(bomb->checkCollisionWCharacter(*this) && bomb->checkExplosion()){
            std::cout << "You are Dead: fireball burning" << std::endl;
            return true;
        }
    }
    return false;
}

bool Player::checkCollisionForEnemies(Character& enemy)
{
    if(bomb != nullptr){
        Collider bombCollider = bomb->getColliderBomb();
        if(enemy.getCollider().checkCollision(bombCollider) && bomb->checkExplosion()){
            std::cout << "Enemy are Dead" << std::endl;
            enemy.setDead();
        }
        if(bomb->checkCollisionWCharacter(enemy) && bomb->checkExplosion()){
            std::cout << "Enemy are Dead" << std::endl;
            enemy.setDead();
        }
    }
    Collider temp = enemy.getCollider();
    if(getCollider().checkCollision(temp)){
        std::cout << "You are Dead: killed by enemy" << std::endl;
        return true;
    }
    return false;
}
