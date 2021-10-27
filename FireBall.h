#ifndef FIREBALL_H
#define FIREBALL_H
#include "Animation.h"
#include "Collider.h"
#include <vector>
#include <SFML/Graphics.hpp>


class FireBall
{
    public:
        FireBall(sf::Texture* moveTexture, sf::Texture* dieTexture, sf::Vector2u imageCount, float switchTime, float speed);
        ~FireBall() = default;

        void Update(float deltaTime);
        void setPosition(sf::Vector2f bornPosition);
        void Draw(sf::RenderWindow& window);
        bool checkBurnt(){ return this->phase >= 13; }
        int getWidthNum(int index);
        int getHeightNum(int index);
        Collider getCollider(int index) { return Collider(body.at(index)); }
    private:
        std::vector<sf::RectangleShape> body;
        Animation animation;
        unsigned int row;
        int phase;
        float speed;
        sf::Texture* fireballDie;
        sf::Texture* fireballmove;
};

#endif // FIREBALL_H
