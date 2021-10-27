#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <ctime>

class Enemy : public Character
{
private:
    int direction;
    int updateCount;
    bool dead;

public:
    Enemy(sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    Enemy() = default;
    ~Enemy();

    void update(float deltaTime) override;
    void checkCollisionForMap(TileMap& map) override;
    void setDead() override { dead = true; }
    bool isDead() override { return dead; }

};

#endif // ENEMY_H
