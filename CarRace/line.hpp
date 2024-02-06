
//SREERAG MURALEEDHARAN

#pragma once
#ifndef LINE_HPP
#define LINE_HPP





#include<cmath>
#include<SFML/Graphics.hpp>
#include<vector>
//-----CLASS TO MANIPULATE LINES------//

const int height = 768;
const int width = 1024;

const float camD = 0.84; //camera depth
const int roadW = 2000; //width of road in 3D
const int segL = 200; //width of each segment of road

using namespace sf;

class DrawQuad 
{
private:
    sf::ConvexShape shape;

public:
    DrawQuad(sf::RenderWindow& app, sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
    ~DrawQuad();

};

class Line
{
private:

    float x,y,z; //real world coordinate in 3d
    float X,Y,W; //screen coordinates
    float curve; // for curve in road
    float scale;
    float spriteX;
    float clip;
    float lifeX;// X distance of obstacle from road
    Sprite sprite; //sprite to render obstacle
    FloatRect texture_rect;
    Sprite life;
    FloatRect life_texture;


public:

    
     Line();
    ~Line();

    void projectToScreen(int camX, int camY, int camZ);
    void drawSprite(RenderWindow& app);
    void drawLife(sf::RenderWindow& app);


    FloatRect getObstacleBounds();
    FloatRect getLifeBounds();
   
    float gety();
    float getX();
    float getY();
    float getW();
    float getCurve();
    float getClip();
    void setClip(float num);
    void setY(float n);

    friend void generateLines();
    friend void generateObstacles(Sprite[]);
    friend void generateLife(Sprite lifee);
};


#endif // LINE_HPP
