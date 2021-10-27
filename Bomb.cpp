#include "Bomb.h"
#include "Animation.h"
#include "FireBall.h"
#include "Collider.h"
#include "TileMap.h"
#include "Character.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Bomb::Bomb(sf::Texture* bombTexture, sf::Texture* fireballMove, sf::Texture* fireballDie, sf::Vector2u bombImageCount
           , sf::Vector2u fireballImageCount, sf::Vector2f position, float switchTime, float speed)
    : animation(bombTexture, bombImageCount, switchTime), fireball(fireballMove, fireballDie, fireballImageCount, switchTime, speed)
{
    phase = 0;
    row = 0;
    countDown = 1.0f;
    body.setSize(sf::Vector2f(48.0f, 48.0f));
    body.setOrigin(body.getSize().x / 2, body.getSize().y - 24.0f);
    body.setPosition(position);
    fireball.setPosition(body.getPosition());
    body.setTexture(bombTexture);
}

void Bomb::Update(float deltaTime){
    if(countDown <= 0){
        if(animation.UpdateHorizontal(row, deltaTime, true, true)){
            phase ++;
        }
        fireball.Update(deltaTime);
    }else{
        countDown -= deltaTime;
    }
    //fireball.Update(deltaTime);
    body.setTextureRect(animation.uvRect);
}

void Bomb::Draw(sf::RenderWindow& window){
    if(countDown <= 0){
        fireball.Draw(window);
    }
    window.draw(body);
}

bool Bomb::checkFinished()
{
    return phase >= 14 && fireball.checkBurnt();
}

bool Bomb::checkExplosion()
{
    return countDown <= 0 && phase >= 5;
}

void Bomb::checkFireballCollision(TileMap& map)
{
    for(auto n  = 0; n < 4; n++){
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                int tileNumber = map.getTileNumber(fireball.getWidthNum(n) + i, fireball.getHeightNum(n) + j);
                if(tileNumber == 0){
                    Collider temp = map.getColliderConcrete(fireball.getWidthNum(n) + i, fireball.getHeightNum(n) + j);
                    fireball.getCollider(n).checkCollision(temp, 0.0f);
                }else if(tileNumber == 1){
                    Collider temp = map.getColliderBox(fireball.getWidthNum(n) + i, fireball.getHeightNum(n) + j);
                    if(fireball.getCollider(n).checkCollision(temp)){
                        std::cout << "Collision with box" << std::endl;
                        map.breakBox(fireball.getWidthNum(n) + i, fireball.getHeightNum(n) + j);
                    }
                }
            }
        }
    }
}

bool Bomb::checkCollisionWCharacter(Character& c)
{
    for(auto n  = 0; n < 4; n++){
        Collider temp = c.getCollider();
        if(fireball.getCollider(n).checkCollision(temp)){
            return true;
        }
    }
    return false;
}
