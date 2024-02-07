
//SREERAG MURALEEDHARAN

#include "../incl/Map.hpp"
#include"../incl/Line.hpp"
#include"../incl/Generator.hpp"
#include"../incl/Scoreboard.hpp"

extern std::vector<Line> lines;

void Map::initMap()
{
    this->initVariables();
    this->initBackgroundTexture();
    this->initFont();
}

void Map::initBackgroundTexture()
{
    for (int i = 0; i < 3; ++i)
    {
        this->backgroundTexture[i].loadFromFile("res\\images\\background\\background" + std::to_string(i) + ".png");
        this->backgroundTexture[i].setRepeated(true);

        if (!this->backgroundTexture[i].loadFromFile("res\\images\\background\\background" + std::to_string(i) + ".png")) 
        {
            std::cerr << "Error loading background texture " << i << std::endl;
        }
        this->background[i].setTexture(backgroundTexture[i]);

    }
}

void Map::initVariables()
{
    this->score = 0;
    this->currentAlpha = 255.0f;
    this->maxAlpha = 255.0f;
}

void Map::initFont()
{

    this->font.loadFromFile("res\\font\\Crang.ttf");
    this->score_text.setPosition(width - 250, 25);
    this->score_text.setFont(font);

    this->font2.loadFromFile("res\\font\\font.ttf");
    this->start.setPosition(width / 2 - 315, height / 2 - 27);
    this->start.setFont(font2);
    this->start.setFillColor(sf::Color::White);
    this->start.setString("PRESS ENTER TO START THE GAME");
    this->start.setCharacterSize(50);
}


void Map::initObstacles()
{
    for (int i = 1; i < 20; i++)
    {
        this->t[i].loadFromFile("res\\images\\obstacles\\" + to_string(i) + ".png");
        this->t[i].setSmooth(true);
        this->obstacle[i].setTexture(t[i]);
    }

    this->lifes.loadFromFile("res\\images\\obstacles\\heart.png");
    this->lifes.setSmooth(true);
    this->life.setTexture(this->lifes);

    generateLines();
    generateObstacles(obstacle);
    generateLife(life);
	
}


void Map::updateScore(sf::Clock clockForScore, Player* player)
{
    if (player->getIsAlive())
    {
        this->setScore(clockForScore.getElapsedTime().asMilliseconds() / 20);
        this->score_text.setString("Score: " + to_string(score) + "\nLives: " + to_string(player->getLifeCollected()));
    }
}
void Map::updateBackground()
{
    this->deltaTime = this->clock.restart();
    this->setCurrentIndex(this->getScore() / 1000 % 3);


    if (this->getCurrentIndex() != this->getBackgroundIndex())
    {
        this->setBackgroundIndex(this->getCurrentIndex());
        this->setCurrentAlpha(75.0f);
        this->setMaxAlpha(255.0f);
    }

}

void Map::Fade()
{
    this->setCurrentAlpha(this->getCurrentAlpha() + 100.0f * deltaTime.asSeconds());

    if (this->getCurrentAlpha() >= this->getMaxAlpha())
    {
        this->setCurrentAlpha(this->getMaxAlpha());
    }
}

void Map::drawMap(sf::RenderWindow& app, Player* player)
{
    this->setPosZ(player->getPosZ());
    this->setPosX(player->getPosX());
    this->setMaxy(height);
    this->setStartPos(this->getPosZ() / segL);
    this->setCamH(lines[this->getStartPos()].gety() + 1450);
    this->setX(0), this->setDx(0);

    for (int n = this->getStartPos(); n < this->getStartPos() + 300; n++)
    {

        Line& l = lines[n % lines.size()];

        l.projectToScreen(this->getPosX() * roadW - this->getX(), this->getCamH(), this->getStartPos() * segL - (n >= lines.size() ? lines.size() * segL : 0));

        this->setX(this->getX() + this->getDx());
        this->setDx(this->getDx() + l.getCurve()) ;

        l.setClip(this->getMaxy());

        if (l.getY() >= this->getMaxy()) continue;
        this->setMaxy(l.getY());


       // ----------DEFINE COLORS---------------//
        if (this->getCurrentIndex() == 0)
        {
            this->environment = (n / 5) % 2 ? sf::Color(161, 164, 162) : sf::Color(161, 164, 162);
            this->roadside = (n / 3) % 2 ? sf::Color::White : sf::Color(33, 33, 33);
            this->marking = (n / 3) % 3 ? sf::Color::White : sf::Color(105, 105, 105);
            this->road = (n / 12) % 2 ? sf::Color(33, 33, 33) : sf::Color(33, 33, 33);
        }
        if (this->getCurrentIndex() == 1)
        {
            this->environment = (n / 5) % 2 ? sf::Color(131, 101, 57) : sf::Color(131, 101, 57);
            this->roadside = (n / 3) % 2 ? sf::Color::White : sf::Color(206, 181, 144);
            this->marking = (n / 3) % 3 ? sf::Color::White : sf::Color(206, 181, 144);
            this->road = (n / 12) % 2 ? sf::Color(206, 181, 144) : sf::Color(206, 181, 144);
        }
        if (this->getCurrentIndex() == 2)
        {
            this->environment = (n / 5) % 2 ? sf::Color(211, 212, 211) : sf::Color(211, 212, 211);
            this->roadside = (n / 3) % 2 ? sf::Color::White : sf::Color(60, 137, 208);
            this->marking = (n / 3) % 3 ? sf::Color::White : sf::Color(60, 137, 208);
            this->road = (n / 12) % 2 ? sf::Color(33, 33, 33) : sf::Color(33, 33, 33);
        }

        Line p = lines[(n - 1) % lines.size()];
        // ----------DRAWING ROADS AND ENVIRONMENT-------------------//
        DrawQuad env(app, this->environment, 0, p.getY(), width, 0, l.getY(), width);
        DrawQuad side(app, this->roadside, p.getX(), p.getY(), p.getW() * 1.2, l.getX(), l.getY(), l.getW() * 1.2);
        DrawQuad road_lane(app, this->road, p.getX(), p.getY(), p.getW(), l.getX(), l.getY(), l.getW());
        DrawQuad markings(app, this->marking, p.getX(), p.getY(), p.getW() * 0.02, l.getX(), l.getY(), l.getW() * 0.02);
    }
}


void Map::drawObstacles(sf::RenderWindow& app)
{
    for (int n = this->getStartPos() + 300; n > this->getStartPos(); n--)
    {
        lines[n % lines.size()].drawSprite(app);
        lines[n % lines.size()].drawLife(app);
    }
}

void Map::drawBackground(sf::RenderWindow& app)
{
    this->background[this->getBackgroundIndex()].setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(std::min(this->getMaxAlpha(), this->getCurrentAlpha()))));
    app.draw(this->background[this->getBackgroundIndex()]);
    app.draw(this->background[this->getCurrentIndex()]);
}

void Map::drawStart(sf::RenderWindow& app)
{
    app.draw(start);
}

void Map::drawScore(sf::RenderWindow& app)
{
    app.draw(score_text);
}


//Getters
int Map::getScore()
{
    return  this->score;
}
const sf::Font& Map::getFont() const
{
    return this->font;
}
const sf::Text& Map::getScoreText() const
{
    return this->score_text;
}
int Map::getMaxy() const
{
    return this->maxy;
}
int Map::getStartPos() const
{
    return this->startPos;
}
int Map::getCamH() const
{
    return this->camH;
}
int Map::getPosX() const
{
    return this->posX;
}
int Map::getPosZ() const
{
    return this->posZ;
}
float Map::getX() const
{
    return this->x;
}
float Map::getDx() const
{
    return this->dx;
}
int Map::getCurrentIndex() const
{
    return this->currentIndex;
}
int Map::getBackgroundIndex() const
{
    return this->backgroundIndex;
}
float Map::getCurrentAlpha() const
{
    return this->currentAlpha;
}
float Map::getMaxAlpha() const
{
    return this->maxAlpha;
}


//Setters
void Map::setScore(int scores)
{
    this->score = scores;
}
void Map::setFont(const sf::Font& newFont) 
{
    this->font = newFont;
}
void Map::setScoreText(const sf::Text& newScoreText)
{
    this->score_text = newScoreText;
}
void Map::setMaxy(int newMaxy) 
{
    this->maxy = newMaxy;
}
void Map::setStartPos(int newStartPos) 
{
    this->startPos = newStartPos;
}
void Map::setCamH(int newCamH) 
{
    this->camH = newCamH;
}
void Map::setPosX(int newPosX) 
{
    this->posX = newPosX;
}
void Map::setPosZ(int newPosZ) 
{
    this->posZ = newPosZ;
}
void Map::setX(float newX) 
{
    this->x = newX;
}
void Map::setDx(float newDx) 
{
    this->dx = newDx;
}
void Map::setCurrentIndex(int index)
{
    this->currentIndex = index;
}
void Map::setBackgroundIndex(int index)
{
    this->backgroundIndex = index;
}
void Map::setCurrentAlpha(float value) 
{
    this->currentAlpha = value;
}
void Map::setMaxAlpha(float value)
{
    this->maxAlpha = value;
}