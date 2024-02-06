
//SREERAG MURALEEDHARAN

#pragma once
#ifndef MAP_HPP
#define MAP_HPP
#include"Player.hpp"
#include<SFML/Graphics.hpp>
#include<vector>
#include"Player.hpp"

class Player;

class Map
{
private:
	
	// Textures for various elements
	sf::Texture lifes;
	sf::Texture backgroundTexture[3];
	sf::Texture t[20];

	// Sprites for visual elements
	sf::Sprite life;
	sf::Sprite background[3];
	sf::Sprite obstacle[20];

	// Fonts for text elements
	sf::Font font;
	sf::Font font2;

	// Text elements for displaying score and start message
	sf::Text score_text;
	sf::Text start;

	// Colors used in the game environment
	sf::Color environment;
	sf::Color roadside;
	sf::Color marking;
	sf::Color road;

	// Clock and time for handling time-based events
	sf::Clock clock;
	sf::Time deltaTime;

	// Variables for handling fading in effect
	bool fadeIn;

	// Variables for controlling transparency and movement
	float currentAlpha;
	float maxAlpha;
	
	// Index for tracking the current state in some scenarios
	int currentIndex;

	// Player-related variables
	int score;
	int maxy;
	int startPos;
	int camH;
	int posX;
	int posZ;
	float x;
	float dx;

	// background 
	int backgroundIndex;
	
public:
	
	void initMap();

	void initBackgroundTexture();

	void initVariables();

	void initFont();

	void initObstacles();

	void updateBackground();

	void updateScore(sf::Clock clockForScore, Player* player);

	void Fade();

	void drawStart(sf::RenderWindow& app);

	void drawBackground(sf::RenderWindow& app);

	void drawMap(sf::RenderWindow& app, Player* player);

	void drawObstacles(sf::RenderWindow& app);

	void drawScore(sf::RenderWindow& app);

	//Getters
	int getScore();
	const sf::Font& getFont() const;
	const sf::Text& getScoreText() const;
	int getMaxy() const;
	int getStartPos() const;
	int getCamH() const;
	int getPosX() const;
	int getPosZ() const;
	float getX() const;
	float getDx() const;
	int getCurrentIndex() const;
	int getBackgroundIndex() const;
	float getCurrentAlpha() const;
	float getMaxAlpha() const;

	//Setters
	void setScore(int score);
	void setFont(const sf::Font& newFont);
	void setScoreText(const sf::Text& newScoreText);
	void setMaxy(int newMaxy);
	void setCamH(int newCamH);
	void setStartPos(int newStartPos);
	void setPosX(int newPosX);
	void setPosZ(int newPosZ);
	void setX(float newX);
	void setDx(float newDx);
	void setCurrentIndex(int index);
	void setBackgroundIndex(int index);
	void setCurrentAlpha(float value);
	void setMaxAlpha(float value);

	
};

#endif //!MAP_HPP