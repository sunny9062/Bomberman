//
// CIS 29
// Group Project
//
// Chris Williams
// Ashley Hu
// Sheng Horng
//
// score.h
//

#include "timer.h"

Timer::Timer() : time(100.0f)
{
    if (!myFont.loadFromFile("chbbc.ttf"))
    {
        std::cout << "Font failed to load" << std::endl;
    }
    myText.setFont(myFont);
    myText.setCharacterSize(25);
    myText.setFillColor(sf::Color::White);
    myText.setPosition(600, 10);
}

Timer::~Timer() {}

void Timer::resetTime()
{
    time = 100.0f;
}

void Timer::update(float sec)
{
    time -= sec;
    if (time < 0.0f)
    {
        time = 0.0f;
    }
    
    // Time reset backdoor
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        resetTime();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        time = 5.0;
    }
}

bool Timer::outOfTime()
{
    return time == 0.0f;
}

void Timer::draw(sf::RenderWindow& window)
{
    std::stringstream ss;
    ss << "Time: " << (int)time;
    myText.setString( ss.str().c_str() );
    window.draw(myText);
}
