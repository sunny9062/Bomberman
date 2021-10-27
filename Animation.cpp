#include "Animation.h"
#include <SFML/Graphics.hpp>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;

    uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
}

void Animation::changeTexture(sf::Texture* texture, sf::Vector2u imageCount){
    this->imageCount = imageCount;
    totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;

    uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
}

bool Animation::UpdateHorizontal(int row, float deltaTime, bool vanish, bool direction){
    currentImage.y = row;
    totalTime += deltaTime;
    bool change = false;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        currentImage.x++;
        change = true;

        if(!vanish){
            if(currentImage.x >= imageCount.x){
                currentImage.x = 0;
            }
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    if(direction){
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    return change;
}

bool Animation::UpdateVertical(int column, float deltaTime, bool goingUp, bool vanish, bool direction){
    currentImage.x = column;
    totalTime += deltaTime;
    bool change = false;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        currentImage.y++;
        change = true;

        if(!vanish){
            if(currentImage.y >= imageCount.y){
                currentImage.y = 0;
            }
        }
    }

    if(goingUp){
        uvRect.top = (imageCount.y - currentImage.y + 1) * uvRect.height;
    }else{
        uvRect.top = currentImage.y * uvRect.height;
    }
    if(direction){
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    return change;
}
