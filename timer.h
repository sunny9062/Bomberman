//
// CIS 29
// Group Project
//
// Chris Williams
// Ashley Hu
// Sheng Horng
//
// timer.h
//

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class Timer
{
private:
    float time;
    sf::Text myText;
    sf::Font myFont;
    
public:
    Timer();
    ~Timer();
    
    void resetTime();
    void update(float sec);
    bool outOfTime();
    void draw(sf::RenderWindow& window);
};
