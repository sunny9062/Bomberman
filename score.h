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

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <map>

class Score
{
private:
    sf::Text myText;
    sf::Font myFont;
    static int points;
    static std::list<std::pair<int, std::string>> scoreboard;
    
public:
    Score();
    ~Score();
    
    void openScoreboardFile();
    void saveScoreboard();
    int getScore();
    void resetScore();
    bool checkHighScore();
    void addToScore(int points);
    void addToScoreboard(std::string name);
    void update();
    void draw(sf::RenderWindow& window);
    friend std::ostream& operator<<(std::ostream&, const Score&);
};
