
//SREERAG MURALEEDHARAN

#include "../incl/Line.hpp"


using namespace sf;

DrawQuad::DrawQuad(sf::RenderWindow& app, sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2)
{
    this->shape.setPointCount(4);
    this->shape.setFillColor(c);
    this->shape.setPoint(0, sf::Vector2f(x1 - w1, y1));
    this->shape.setPoint(1, sf::Vector2f(x2 - w2, y2));
    this->shape.setPoint(2, sf::Vector2f(x2 + w2, y2));
    this->shape.setPoint(3, sf::Vector2f(x1 + w1, y1));
    app.draw(this->shape);
}

DrawQuad::~DrawQuad() 
{}

Line::Line() 
{
    this->lifeX = this->spriteX = this->curve = this->x = this->y = this->z = 0;
}

Line::~Line() {}

// Project the 3D coordinates of the line to the 2D screen coordinates based on the camera's position
void Line::projectToScreen(int camX, int camY, int camZ)
{
    // Calculate the scaling factor for the line based on its distance from the camera
    this->scale = camD / (z - camZ);
    this->X = (1 + scale * (x - camX)) * width / 2;
    this->Y = (1 - scale * (y - camY)) * height / 2;
    this->W = this->scale * roadW * width / 2;
}


void Line::drawSprite(sf::RenderWindow& app)
{

    sf::Sprite s = sprite;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = this->X + this->scale * this->spriteX * width / 2;
    float destY = this->Y;
    float destW = w * this->W / 266;
    float destH = h * this->W / 266;

    destX += destW * this->spriteX;
    destY += destH * (-1);

    float clipH = destY + destH - this->clip;
    if (clipH < 0) clipH = 0;

    if (clipH >= destH) return;
    s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
    s.setScale(destW / w, destH / h);
    s.setPosition(destX, destY);

    texture_rect = s.getGlobalBounds();

    app.draw(s);

}

void Line::drawLife(sf::RenderWindow& app)
{

    sf::Sprite s = life;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = this->X + this->scale * this->lifeX * width / 2;
    float destY = this->Y - 2;
    float destW = w * this->W / 266;
    float destH = h * this->W / 266;

    destX += destW * this->lifeX;
    destY += destH * (-1);

    float clipH = destY + destH - this->clip;
    if (clipH < 0) clipH = 0;

    if (clipH >= destH) return;
    s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
    s.setScale(destW / w, destH / h);
    s.setPosition(destX, destY);

    life_texture = s.getGlobalBounds();

    app.draw(s);
}

FloatRect Line::getObstacleBounds() 
{
    return  this->texture_rect;
}

FloatRect Line::getLifeBounds()
{
    return  this->life_texture;
}

float Line::gety()
{
    return  this->y;
}

float Line::getX()
{
    return  this->X;
}

float Line::getY() 
{
    return  this->Y;
}

float Line::getW() 
{
    return  this->W;
}

float Line::getCurve() 
{
    return  this->curve;
}

float Line::getClip()
{
    return  this->clip;
}

void Line::setClip(float num)
{
    this->clip = num;
}

void Line::setY(float n)
{
    this->Y = n;
}
