#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <cmath>

class Collider
{
private:
    sf::RectangleShape& body;

public:
    Collider(sf::RectangleShape& body);
    Collider() = default;
    ~Collider();

    void move(float dx, float dy) { body.move(dx, dy); }
    bool checkCollision(Collider& other);
    bool checkCollision(Collider& other, float push);
    sf::Vector2f getPosition() { return body.getPosition(); }
    sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }
};


#endif // COLLIDER_H
