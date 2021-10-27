#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Animation.h"
#include "Collider.h"

class Character
{
protected:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;

public:
    Character(sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    Character() = default;
    virtual ~Character();

    virtual void draw(sf::RenderWindow& window);
    virtual void update(float deltaTime) = 0;
    int getWidthNum();
    int getHeightNum();
    sf::Vector2f getPosition() { return body.getPosition(); }
    virtual void checkCollisionForMap(TileMap& map) = 0;
    Collider getCollider() { return Collider(body); }
    virtual bool checkCollisionForFireball() {return false;}
    virtual bool checkCollisionForEnemies(Character& enemy) {return false;}
    virtual void setDead() {}
    virtual bool isDead() {return false;}
};

#endif // CHARACTER_H
