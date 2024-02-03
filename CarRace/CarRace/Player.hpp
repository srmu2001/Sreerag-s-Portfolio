#pragma once
#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<vector>
#include<SFML/Audio.hpp>
#include"Map.hpp"

class Map;

class Player
{
private:
    // Member Variables
    float colliderX;            // X-coordinate of the collider
    float colliderY;            // Y-coordinate of the collider
    int posZ;                    // Z-coordinate position
    int posX;                    // X-coordinate position
    bool isAlive;                // Player's alive status
    float speed;                 // Player's movement speed
    int life_collected;          // Number of collected life items
    int framesNum;               // Number of animation frames
    float animDuration;          // Duration of each animation frame (in seconds)
    float delta;                 // Delta time for animation

    sf::RectangleShape collider; // Player's collider shape
    sf::Texture playerFoto;      // Player's texture
    sf::Sprite playerCar;        // Player's sprite
    sf::SoundBuffer lifesound;   // Sound buffer for life collected
    sf::SoundBuffer collisonsound; // Sound buffer for collision
    sf::SoundBuffer lifeimp;     // Sound buffer for life impact
    sf::SoundBuffer turnsound;   // Sound buffer for turn
    sf::Sound playLife;          // Sound for life collected
    sf::Sound collideSounds;     // Sound for collision
    sf::Sound playLifeImp;       // Sound for life impact
    sf::Sound playTurn;          // Sound for turn
    sf::Vector2i playerSize;     // Size of each animation frame
    sf::Clock clockForPlayer;    // Clock for player animations


    
    void initVariables();
    void initPlayerTexture();
   

public:
    // Public member functions for setting values
    void setColliderX(float x);
    void setColliderY(float y);
    void setPosZ(int z);
    void setPosX(int x);
    void setIsAlive(bool alive);
    void setSpeed(float s);
    void setLifeCollected(int collected);
    void setanimDuration(float x);
    void setDelta(float newDelta);
    void setFramesNum(int FrameNo);

    // Public member functions for getting values
    float getColliderX() const;
    float getColliderY() const;
    int getPosZ() const;
    int getPosX() const;
    bool getIsAlive() const;
    float getSpeed() const;
    int getLifeCollected() const;
    float getanimDuration() const;
    float getDelta() const;
    float getFramesNum() const;

    // Gameplay-related functions
    void initPlayer();
    void initPlayerSound();
    void handleEvents();           // Handle player input events
    void collisionTest(Map* map);  // Check for collisions with obstacles and collectibles
    void playerReset();            // Reset player's state
    void update(Map* map);         // Update player's position and animations
    void drawPlayer(sf::RenderWindow& app); // Draw player on the window
};

#endif // PLAYER_HPP
