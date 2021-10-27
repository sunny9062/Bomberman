//
// CIS 29
// Group Project
//
// Chris Williams
// Ashley Hu
// Sheng Horng
//
// score.cpp
//

#include "score.h"

int Score::points = 0;
std::list<std::pair<int, std::string>> Score::scoreboard = {};

Score::Score()
{
    // Initialize text
    if (!myFont.loadFromFile("chbbc.ttf"))
    {
        std::cout << "Font failed to load" << std::endl;
    }
    myText.setFont(myFont);
    myText.setCharacterSize(25);
    myText.setFillColor(sf::Color::White);
    myText.setPosition(20, 10);
}

Score::~Score() {}

void Score::openScoreboardFile()
{
    std::string fileName = "scoreboard.txt";
    std::ifstream inFile(fileName);
    if (!inFile)
    {
        throw fileName;
    }
    else
    {
        while(!inFile.eof())
        {
            char name[16];
            char score[16];
            inFile.getline(score,15);
            inFile.getline(name,15);
            Score::points = atoi(score);
            Score::scoreboard.push_back(std::pair<int, std::string>(Score::points, std::string(name)));
            Score::scoreboard.sort();
            Score::scoreboard.reverse();
        }
    }
    inFile.close();
}

void Score::saveScoreboard()
{
    std::string fileName = "scoreboard.txt";
    std::ofstream outFile(fileName);
    if (!outFile)
    {
        throw fileName;
    }
    else
    {
        for (auto s : Score::scoreboard)
        {
            outFile << s.first << std::endl << s.second << std::endl;
        }
    }
    outFile.close();
}

int Score::getScore()
{
    return Score::points;
}

void Score::resetScore()
{
    Score::points = 0;
}

bool Score::checkHighScore()
{
    if (Score::scoreboard.size() < 10 || Score::points > Score::scoreboard.back().first)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Score::addToScore(int points)
{
    Score::points += points;
}


void Score::addToScoreboard(std::string name)
{
    while (Score::scoreboard.size() >= 10)
    {
        Score::scoreboard.pop_back();
    }
    Score::scoreboard.push_back(std::pair<int, std::string>(Score::points, name));
    Score::scoreboard.sort();
    Score::scoreboard.reverse();
}

void Score::update()
{
    // Update scoreboard
    while (Score::scoreboard.size() > 10)
    {
        Score::scoreboard.pop_back();
    }
    // Score Backdoor
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
    {
        addToScore(1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
        {
            resetScore();
        }
    }
}

void Score::draw(sf::RenderWindow& window)
{
    std::stringstream ss;
    ss << "Score: " << Score::points;
    myText.setString( ss.str().c_str() );
    window.draw(myText);
}

std::ostream& operator<<(std::ostream& out, const Score& s)
{
    int rank = 0;
    for (auto s : Score::scoreboard)
    {
        rank++;
        out << std::setw(2) << rank << ": " << std::setw(15) << std::left << s.second << " " << s.first << std::endl;
    }
    return out;
}
