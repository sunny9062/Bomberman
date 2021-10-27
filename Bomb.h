#ifndef BOMB_H
#define BOMB_H
#include "Animation.h"
#include "FireBall.h"
#include "Collider.h"
#include "TileMap.h"
#include "Character.h"
#include <SFML/Graphics.hpp>


class Bomb
{
    public:
        Bomb(sf::Texture* bombTexture, sf::Texture* fireballMove, sf::Texture* fireballDie
             , sf::Vector2u bombImageCount, sf::Vector2u fireballImageCount, sf::Vector2f position
             , float switchTime, float speed);
        ~Bomb() = default;

        void Update(float deltaTime);
        void checkFireballCollision(TileMap& map);
        bool checkFinished();
        bool checkExplosion();
        Collider getColliderBomb(){ return Collider(body); }
        Collider getColliderFireball(int index){ return fireball.getCollider(index); }
        bool checkCollisionWCharacter(Character& c);
        void Draw(sf::RenderWindow& window);
    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        int phase;
        float countDown;
        FireBall fireball;
};

#endif // BOMB_H
