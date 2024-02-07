
//SREERAG MURALEEDHARAN


#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP
#include <SFML/Graphics.hpp>
#include<sstream>
#include<iostream>
#include<fstream>
#include"game.hpp"
#include<vector>

using namespace std;

class ScoreBoard {
private:
    sf::RectangleShape box;  // Visual representation of the score display box
    sf::Text text[3];        // Array to store various text elements for display
    sf::Text space;          // Text element for the instruction to return to Menu
    sf::Font font;           // Font used for the text elements

public:
    
    static const int NUM_HIGH_SCORES = 5;  // Maximum number of high scores to store

    struct ScoreData
    {
        int score;
    };
    
    
    ///  <summary>
    ///  Constructor for the ScoreBoard class
    ///  Displays the score, high score, and related information on the screen
    ///  </summary>
    ScoreBoard(sf::RenderWindow& app, sf::Font font, int score);

    
    ///  <summary>
    ///  Checks if the current score is a new high score and updates the high score list
    ///  Returns true if the current score is a new high score, false otherwise
    ///  </summary>
    bool checkHighScore(int score);

    
    ///  <summary>
    ///  Handles events related to the score display, such as returning to the Menu
    ///  </summary>
    void handleEvents(sf::RenderWindow& app, Player* player, Map* map);
};

#endif // SCOREBOARD_HPP
