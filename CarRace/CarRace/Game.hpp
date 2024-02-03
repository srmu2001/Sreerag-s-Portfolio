#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include<map>
#include<string>
#include<sstream>
#include"Player.hpp"
#include"generator.hpp"
#include"line.hpp"
#include"Scoreboard.hpp"
#include"menu.hpp"
#include"Map.hpp"
#include<SFML/Audio.hpp>
#include <vector>


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Forward declarations of Player and Map classes (assuming they are defined elsewhere)
class Player;
class Map;

class Game
{
private:
    // Window for the game
    sf::RenderWindow app;

    // Font for text rendering
    sf::Font font;

    // Music for the game
    sf::Music gameMusic;

    // Clocks for tracking game time
    sf::Clock gameClock;
    sf::Clock clockForScore;

    // Player and Map objects
    Player playerr;  // Assuming Player and Map classes are defined elsewhere
    Map gameMap;

    // Pointers to Player and Map for dynamic memory allocation
    Player* player;
    Map* map;

    // Private functions for initializing various components of the game
    void initApp();
    void initGame();
    void initMap();
    void initPlayer();
    void initSound();

public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    // Public functions for game functionality

    // Handle user input events
    void handleEvents();

    // Update the game state
    void updateGame();

    // Draw game elements on the window
    void drawGameElements();

    // Run the game loop
    void run();
};

#endif // GAME_HPP