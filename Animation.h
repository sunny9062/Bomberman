#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>


class Animation
{
    public:
        Animation() = default;
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        ~Animation() = default;
        bool UpdateHorizontal(int row, float deltaTime, bool vanish, bool direction);
        bool UpdateVertical(int column, float deltaTime, bool goingUp, bool vanish, bool direction);
        void changeTexture(sf::Texture* texture, sf::Vector2u imageCount);
    public:
        sf::IntRect uvRect;
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;
};

#endif // ANIMATION_H
