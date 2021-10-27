#include "FireBall.h"
#include "Animation.h"
#include <iostream>
#include "Collider.h"
#include <SFML/Graphics.hpp>

FireBall::FireBall(sf::Texture* moveTexture, sf::Texture* dieTexture, sf::Vector2u imageCount, float switchTime, float speed)
                : animation(dieTexture, imageCount, switchTime)
{
    row = 0;
    phase = 1;
    this->speed = speed;
    fireballDie = dieTexture;
    fireballmove = moveTexture;
    body.resize(4);
    for(auto i = 0; i < body.size(); i++){
        body.at(i).setSize(sf::Vector2f(48.0f, 48.0f));
        body.at(i).setOrigin(body.at(i).getSize().x / 2, body.at(i).getSize().y / 2);
        body.at(i).setRotation(i * 90);
        body.at(i).setTexture(fireballDie);
    }
}

void FireBall::setPosition(sf::Vector2f bornPosition){
    for(auto i = 0; i < body.size(); i++){
        body.at(i).setPosition(bornPosition.x, bornPosition.y);
    }
}

void FireBall::Update(float deltaTime){
    if(phase == 6){
        animation.changeTexture(fireballmove, sf::Vector2u(5, 1));
        for(auto i = 0; i < body.size(); i++){
            body.at(i).setTexture(fireballmove);
            body.at(i).setSize(sf::Vector2f(48.0f, 48.0f));
            body.at(i).setOrigin(body.at(i).getSize().x / 2, body.at(i).getSize().y / 2);
        }
        row = 0;
        phase++;

    }else if(phase == 9){
        animation.changeTexture(fireballDie, sf::Vector2u(1, 6));
        //body.at(0).move(24.0f, 0.0f);
        //body.at(1).move(0.0f, 24.0f);
        //body.at(2).move(-24.0f, 0.0f);
        //body.at(3).move(0.0f, -24.0f);
        for(auto i = 0; i < body.size(); i++){
            body.at(i).setTexture(fireballDie);
            body.at(i).setSize(sf::Vector2f(48.0f, 48.0f));
            body.at(i).setOrigin(body.at(i).getSize().x / 2, body.at(i).getSize().y / 2);
        }
        row = 0;
        phase++;
    }
    if(phase <= 6 || phase >= 9){
        bool goingUp = false;
        if(phase <= 6){
            goingUp = true;
        }
        if(animation.UpdateVertical(row, deltaTime, goingUp, true, false))
            phase++;
    }else{
        if(animation.UpdateHorizontal(row, deltaTime, false, false))
            phase++;
        float movement = speed * deltaTime;
        body.at(0).move(movement, 0.0f);
        body.at(1).move(0.0f, movement);
        body.at(2).move( 0 - movement, 0.0f);
        body.at(3).move(0.0f, 0 - movement);
    }
    for(auto i = 0; i < body.size(); i++){
        body.at(i).setTextureRect(animation.uvRect);
    }
}


int FireBall::getWidthNum(int index)
{
    int widthNum = body.at(index).getPosition().x / 48;
    return widthNum;
}

int FireBall::getHeightNum(int index)
{
    int heightNum = body.at(index).getPosition().y / 48;
    return heightNum;
}

void FireBall::Draw(sf::RenderWindow& window){
    for(auto i = 0; i < body.size(); i++){
        window.draw(body.at(i));
    }
}
