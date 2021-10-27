#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Platform.h"
#include "Collider.h"
#include "TileMap.h"

TileMap::TileMap(sf::Vector2f tileSize)
{
    width = 15;
    height = 13;
    // load the tileset texture
    if (!m_tileset.loadFromFile("grass.png"))
        exit(1);
    if (!concrete.loadFromFile("concrete.png"))
        exit(1);
    if (!box.loadFromFile("box.png"))
        exit(1);
    if (!burntbox.loadFromFile("burnbox.png"))
        exit(1);

    // resize the vertex array to fit the level size
    grass_vertices.setPrimitiveType(sf::Quads);
    grass_vertices.resize(width * height * 4);
    concretes.resize(80);
    boxes.resize(80);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            if(tileNumber == 0){
                Platform newConcrete(&concrete, tileSize, sf::Vector2f(i*tileSize.x + tileSize.x / 2
                                , j*tileSize.y + tileSize.y / 2), i, j);
                concretes.push_back(newConcrete);
            }
            if(tileNumber == 1){
                Platform newBox(&box, tileSize, sf::Vector2f(i*tileSize.x + tileSize.x / 2
                                , j*tileSize.y + tileSize.y / 2), i, j);
                boxes.push_back(newBox);
            }

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &grass_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(0.0f, 0.0f);
            quad[1].texCoords = sf::Vector2f(m_tileset.getSize().x, 0.0f);
            quad[2].texCoords = sf::Vector2f(m_tileset.getSize().x, m_tileset.getSize().y);
            quad[3].texCoords = sf::Vector2f(0.0f, m_tileset.getSize().y);
        }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;
    // draw the vertex array
    target.draw(grass_vertices, states);
}

void TileMap::drawBricks(sf::RenderWindow& window)
{
    for(auto i = 0; i < concretes.size(); i++){
        concretes.at(i).Draw(window);
    }
    for(auto i = 0; i < boxes.size(); i++){
        boxes.at(i).Draw(window);
    }
}

int TileMap::getTileNumber(int widthNum, int heightNum)
{
    return tiles[widthNum + heightNum * width];
}

Collider TileMap::getColliderConcrete(int widthNum, int heightNum)
{
    for(auto i = 0; i < concretes.size(); i++){
        if(widthNum == concretes.at(i).getWidthNum() && heightNum == concretes.at(i).getHeightNum()){
            return concretes.at(i).getCollider();
        }
    }
}

Collider TileMap::getColliderBox(int widthNum, int heightNum)
{
    for(auto i = 0; i < boxes.size(); i++){
        if(widthNum == boxes.at(i).getWidthNum() && heightNum == boxes.at(i).getHeightNum()){
            return boxes.at(i).getCollider();
        }
    }
}

void TileMap::breakBox(int widthNum, int heightNum)
{
    for(auto i = 0; i < boxes.size(); i++){
        if(widthNum == boxes.at(i).getWidthNum() && heightNum == boxes.at(i).getHeightNum()){
            boxes.erase(boxes.begin() + i);
            tiles[widthNum + heightNum * width] = 2;
            Score score = Score();
            score.addToScore(20);
            /*boxes.at(i).changeTexture(&burntbox);
            boxes.at(i).update();*/
            break;
        }
    }
}

/*void TileMap::cleanBurnt()
{
    for(auto i = 0; i < boxes.size(); i++){
        if(boxes.at(i).checkBurnt()){
            boxes.erase(boxes.begin() + i);
        }
    }
}*/
