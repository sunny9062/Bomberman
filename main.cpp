//
// CIS 29
// Group Project
//
// Chris Williams
// Ashley Hu
// Sheng Horng
//
// Main.cpp
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <string>
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "score.h"
#include "timer.h"

using namespace std;

//static const float VIEW_HEIGHT = 512.0f;
//void ResizedView(const sf::RenderWindow&, sf::View&);


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(720, 624), "Group 4 - Game");
    //sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    
    // Create scoreboard
    Score score = Score();
    try
    {
        score.openScoreboardFile();
    }
    catch(string e)
    {
        cout << "Error. '" << e << "' failed to open." << endl;
    }
    
    // End Game texts
    sf::Text gameOverText;
    sf::Font myFont;
    if (!myFont.loadFromFile("chbbc.ttf"))
    {
        cout << "Font failed to load" << endl;
    }
    gameOverText.setFont(myFont);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::White);
    string go {"GAME OVER"};
    gameOverText.setString( go.c_str() );
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    gameOverText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 3.0f);
    sf::Text pausedText;
    pausedText.setFont(myFont);
    pausedText.setCharacterSize(150);
    pausedText.setFillColor(sf::Color::White);
    string p {"PAUSE"};
    pausedText.setString( p.c_str() );
    textRect = pausedText.getLocalBounds();
    pausedText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    pausedText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 3.0f);
    sf::Text scoreboardText;
    scoreboardText.setFont(myFont);
    scoreboardText.setCharacterSize(25);
    scoreboardText.setFillColor(sf::Color::White);
    
    // Character textures
    sf::Texture playerTexture;
    playerTexture.loadFromFile("robotMove.png");
    sf::Texture badguyTexture;
    badguyTexture.loadFromFile("robotMove.png");
    
    // Main Loop
    while(window.isOpen())
    {
        // Menu Loop
        bool menuOpen = true;
        while (menuOpen)
        {
            // Menu Object
            menuOpen = false; // Remove after code is written for this loop
        }
        
        // Start Game
        
        // create the tilemap from the level definition
        TileMap map(sf::Vector2f(48.0f, 48.0f));
        
        // Initialize player and badguys in array
        vector<Character*> characters {
            new Player(sf::Vector2f(72.0f, 72.0f), &playerTexture, sf::Vector2u(1, 2), 0.1f, 220.0f),
            new Enemy(sf::Vector2f(408.0f, 168.0f), &playerTexture, sf::Vector2u(1, 2), 0.1f, 110.0f),
            new Enemy(sf::Vector2f(72.0f, 11 * 48 + 24), &playerTexture, sf::Vector2u(1, 2), 0.1f, 110.0f),
            new Enemy(sf::Vector2f(48 * 6 + 24, 48 * 7 + 24), &playerTexture, sf::Vector2u(1, 2), 0.1f, 110.0f),
            new Enemy(sf::Vector2f(48 * 13 + 24, 11 * 48 + 24), &playerTexture, sf::Vector2u(1, 2), 0.1f, 110.0f)
        };

        // set time
        float deltaTime = 0.0f;
        sf::Clock clock;
        Timer time = Timer();
        score.resetScore();
        
        // Game Event Loop
        int numEnemies = 4;
        float regenerateTime = 0;
        bool gameEnd = false;
        bool paused = false;
        while (window.isOpen() && gameEnd == false)
        {
            deltaTime = clock.restart().asSeconds();
            
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                if (evnt.type == sf::Event::TextEntered)
                {
                    // Pause
                    if (evnt.text.unicode == 32)
                    {
                        if (paused == false)
                        {
                            paused = true;
                        }
                        else
                        {
                            paused = false;
                        }
                    }
                    // End game backdoor
                    if (evnt.text.unicode == 81)
                    {
                        gameEnd = true;
                    }
                }
                if (evnt.type == sf::Event::Closed) // Close window
                {
                    window.close();
                }
//                if (evnt.type == sf::Event::Resized) // Close window
//                {
//                    ResizedView(window, view);
//                }
            }
            if (paused)
            {
                window.draw(pausedText);
                window.display();
            }
            else
            {
                // Check for enemy deaths
                for(auto i = 1; i < characters.size(); i++)
                {
                    if(characters[i]->isDead())
                    {
                        delete characters[i];
                        characters[i] = nullptr;
                        characters.erase(characters.begin() + i);
                        score.addToScore(100);
                        numEnemies--;
                        regenerateTime = 0;
                    }
                }
                
                // Regenerate Enemies
                regenerateTime += deltaTime;
                if(numEnemies < 4 && regenerateTime > 3)
                {
                    int x = 0;
                    int y = 0;
                    while (map.getTileNumber(x, y) != 2 || abs((characters[0]->getPosition().x/48)-x)<3 || abs((characters[0]->getPosition().y/48)-x)<3)
                    {
                        x = 1 + (rand() % 13);
                        y = 1 + (rand() % 11);
                    }
                    characters.push_back(new Enemy(sf::Vector2f(24 + (x * 48), 24 + (y * 48)), &playerTexture, sf::Vector2u(1, 2), 0.1f, 110.0f));
                    numEnemies++;
                    regenerateTime = 0;
                }
                
                // Update Characters
                if(!gameEnd)
                {
                    for (auto c : characters)
                    {
                        c->update(deltaTime);
                        c->checkCollisionForMap(map);
                    }
        
                    if(characters[0]->checkCollisionForFireball()){
                        gameEnd = true;
                    }
        
                    for(auto i = 1; i < characters.size(); i++){
                        if(characters[0]->checkCollisionForEnemies(*characters[i])){
                            gameEnd = true;
                            break;
                        }
                    }
                }
                
                // update Time and Score
                score.update();
                time.update(deltaTime);
                if (time.outOfTime())
                {
                    gameEnd = true;
                }
                
                //view.setCenter(characters[0]->getPosition());
                
                // Draw and display
                window.clear();
                //window.setView(view);
                window.draw(map);
                map.drawBricks(window);
                for (auto c : characters)
                {
                    c->draw(window);
                }
                score.draw(window);
                time.draw(window);
                window.display();
            }
        }
        
        // Game End
        // Check high score or Pause at end
        if (score.checkHighScore() && window.isOpen())
        {
            std::string name {""};
            std::string prompt {"High Score!!\n\nEnter Name: "};
            scoreboardText.setString( prompt.c_str() );
            sf::FloatRect textRect = scoreboardText.getLocalBounds();
            scoreboardText.setOrigin(textRect.left, textRect.top + textRect.height/2.0f);
            scoreboardText.setPosition(30, window.getSize().y / 1.5f);
            window.draw(scoreboardText);
            window.draw(gameOverText);
            window.display();
            
            // Prompt for high score name
            sf::Event evnt;
            bool pressedKey = false;
            bool endLoop = false;
            while (!endLoop && window.isOpen())
            {
                window.pollEvent(evnt);
                if (evnt.type == sf::Event::TextEntered && pressedKey == false)
                {
                    // 'Enter'
                    if (evnt.text.unicode == '\n')
                    {
                        endLoop = true;
                    }
                    // Delete
                    else if (evnt.text.unicode == 8 )
                    {
                        name.pop_back();
                        prompt.pop_back();
                    }
                    // Character key
                    else if (evnt.text.unicode > 31 && evnt.text.unicode < 127 && name.length() < 15)
                    {
                        name += static_cast<char>(evnt.text.unicode);
                        prompt += static_cast<char>(evnt.text.unicode);
                    }
                    scoreboardText.setString( prompt.c_str() );
                    
                    // Draw window
                    // Draw and display
                    window.clear();
                    //window.setView(view);
                    window.draw(map);
                    map.drawBricks(window);
                    for (auto c : characters)
                    {
                        c->draw(window);
                    }
                    score.draw(window);
                    time.draw(window);
                    window.draw(scoreboardText);
                    window.draw(gameOverText);
                    window.display();
                    clock.restart();
                    pressedKey = true;
                }
                else if (evnt.type == sf::Event::KeyReleased)
                {
                    pressedKey = false;
                }
                // Close window
                else if (evnt.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            score.addToScoreboard(name);
        }
        else if (window.isOpen())  // Pause
        {
            window.draw(gameOverText);
            window.display();
            clock.restart();
            while (clock.getElapsedTime().asSeconds() < 4.0) {}
        }
        
        // Test scoreboard
        cout << score;
        
        // delete characters
        for (int i = 0; i < characters.size(); i++)
        {
            delete characters[i];
            characters[i] = nullptr;
        }
    }
    
    // Save scoreboard to file
    try
    {
        score.saveScoreboard();
    }
    catch(string e)
    {
        cout << "Error. '" << e << "' failed to open." << endl;
    }
    
    return 0;
}


//void ResizedView(const sf::RenderWindow& window, sf::View& view)
//{
//    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
//    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
//
//}
