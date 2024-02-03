#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<iostream>
#include<fstream>
#include<vector>
#define No_of_Items 4


class Menu
{
private:
    static sf::Font font;            // Static font for all menu items
    int selectedItemIndex;           // Index of the currently selected menu item

    sf::Text text[No_of_Items];      // Array of menu item texts
    sf::Texture intro_img2;          // Texture for the second introduction screen
    sf::Sprite intro2;               // Sprite for the second introduction screen
    sf::RectangleShape box;          // Rectangle shape for background box
    sf::Text InfoText[5];            // Array of informational texts

public:
    // Constructor and Destructor
    Menu(int width, int height);     // Constructor to initialize menu elements
    ~Menu();                         // Destructor

    // Static function to load menu assets
    static void LoadAssests();

    // Menu navigation functions
    void MoveUp();                   // Move selection upwards
    void MoveDown();                 // Move selection downwards
    int GetPressedItem();            // Get the index of the pressed menu item

    // Draw functions
    void draw(sf::RenderWindow& window);        // Draw menu on the window
    void DrawHighScores(sf::RenderWindow& app); // Draw high scores screen
    void DrawInfo(sf::RenderWindow& app);       // Draw instructions screen
};

// Function to load the menu and handle its flow
bool LoadMenu(sf::RenderWindow&, bool);


#endif // MENU_HPP
