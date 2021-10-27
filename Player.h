#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Character.h"
#include "Enemy.h"
//#include "score.h"

class Player : public Character
{
private:
    Bomb* bomb;
    sf::Texture bombTexture;
    sf::Texture fireballMove;
    sf::Texture fireballDie;
    //Score score;
public:
    Player(sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    Player() = default;
    ~Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void checkCollisionForMap(TileMap& map) override;
    bool checkCollisionForFireball() override;
    bool checkCollisionForEnemies(Character& enemy) override;

};

#endif // PLAYER_H
