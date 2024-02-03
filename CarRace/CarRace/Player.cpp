
//SREERAG MURALEEDHARAN

#include "Player.hpp"
#include"line.hpp"
#include"Scoreboard.hpp"

void Player::initPlayer()
{

    initVariables();

    initPlayerTexture();

}

void Player::initVariables()
{
    this->colliderX = width / 2 - 20;
    this->colliderY = height / 2 + 200;
    this->posZ = 0;
    this->posX = 0;
    this->isAlive = true;
    this->speed = 200.0f;
    this->life_collected = 0;
    this->collider.setSize(sf::Vector2f(100, 90));
    this->collider.setPosition(colliderX, colliderY);
    this->playerSize.x = 264;
    this->playerSize.y = 200; //size of each frame
    this->framesNum = 2;
    this->animDuration = 0.45; //seconds
    this->clockForPlayer;
    this->delta = 0;
}

void Player::initPlayerTexture()
{
    this->playerFoto.loadFromFile("images\\player\\car_idle.png");
    this->playerCar.setTexture(this->playerFoto);
    this->playerCar.setPosition(width / 2 - 100, height / 2 + 160);
}


void Player::initPlayerSound()
{
    this->lifesound.loadFromFile("sound\\life sound.ogg");
    this->playLife.setBuffer(this->lifesound);

    this->collisonsound.loadFromFile("sound\\crash.ogg");
    this->collideSounds.setBuffer(this->collisonsound);

    this->lifeimp.loadFromFile("sound\\life impact.ogg");
    this->playLifeImp.setBuffer(this->lifeimp);

    this->turnsound.loadFromFile("sound\\turn sound.ogg");
    this->playTurn.setBuffer(this->turnsound);
}

void Player::update(Map* map) {


    if (map->getScore() == 1000)
    {
        setSpeed(250.0f);
        this->setanimDuration(0.40);

    }
    if (map->getScore() == 2000)
    {
        setSpeed(300.0f);
        this->setanimDuration(0.35);

    }
    if (map->getScore() == 3000)
    {
        setSpeed(350.0f);

        this->setanimDuration(0.30);
    }

    if (this->getIsAlive())
        this->setPosZ(getPosZ() + this->speed);

    if (this->getIsAlive())
        this->setDelta(this->getDelta() + this->clockForPlayer.restart().asSeconds());

    //---Get Current Frame----//
    int animFrame = static_cast<int>((this->getDelta() / this->getanimDuration()) * this->getFramesNum()) % this->framesNum;

    //---Set Sprite Rectangle Based on Frame---//
    this->playerCar.setTextureRect(IntRect(animFrame * playerSize.x, 0, playerSize.x, playerSize.y));


    if (this->getPosZ() >= lines.size() * segL)
        this->setPosZ(this->getPosZ() - lines.size() * segL);

    if (this->getPosZ() < 0)
        this->setPosZ(this->getPosZ() + lines.size() * segL);

}

void Player::collisionTest(Map* map)
{
    if (getIsAlive() == true)
        if (lines[map->getStartPos() + 5].getObstacleBounds().intersects(collider.getGlobalBounds()))
        {

            if (getLifeCollected() == 0)
            {
                setIsAlive(false);
                this->collideSounds.play();
            }

            else if (getLifeCollected() > 0)
            {
                this->playLifeImp.play();
                setLifeCollected((getLifeCollected() - 1));
            }

        }
    if (lines[map->getStartPos() + 5].getLifeBounds().intersects(collider.getGlobalBounds()))
    {
        setLifeCollected(getLifeCollected() + 1);
        this->playLife.play();
    }
}


void Player::playerReset()
{
    this->setPosZ(0);
    this->setPosX(0);
    this->setIsAlive(false);
    this->setLifeCollected(0);
    this->playerCar.setPosition(width / 2 - 100, height / 2 + 160);
    this->collider.setPosition(this->colliderX, this->colliderY);

}

void Player::handleEvents()
{

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        if (this->collider.getPosition().x < this->colliderX + 300)
        {
            this->collider.move(30, 0);     this->playerCar.move(30, 0);
            this->playTurn.play();
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        if (this->collider.getPosition().x > this->colliderY - 300)
        {
            this->collider.move(-30, 0);     this->playerCar.move(-30, 0);
            this->playTurn.play();
        }
    }
}


void Player::drawPlayer(sf::RenderWindow& app)
{
    app.draw(this->playerCar);

}


void Player::setColliderX(float x)
{
    colliderX = x;
}
void Player::setColliderY(float y)
{
    colliderY = y;
}
void Player::setPosZ(int z)
{
    posZ = z;
}
void Player::setPosX(int x)
{ 
    posX = x;
}
void Player::setIsAlive(bool alive) 
{ 
    isAlive = alive;
}
void Player::setSpeed(float s) 
{
    speed = s;
}
void Player::setLifeCollected(int collected)
{ 
    life_collected = collected; 
}
void Player::setanimDuration(float x)
{ 
    animDuration = x; 
}
void Player::setDelta(float newDelta)
{
    this->delta = newDelta;
}
void Player::setFramesNum(int FrameNo)
{
    this->framesNum = FrameNo;
}



float Player::getColliderX() const 
{ 
    return colliderX; 
}
float Player::getColliderY() const 
{
    return colliderY;
}
int Player::getPosZ() const
{
    return posZ;
}
int Player::getPosX() const
{
    return posX;
}
bool Player::getIsAlive() const
{ 
    return isAlive;
}
float Player::getSpeed() const 
{ 
    return speed;
}
int Player::getLifeCollected() const 
{ 
    return life_collected;
}
float Player::getanimDuration() const 
{ 
    return animDuration;
}
float Player::getDelta() const
{
    return this->delta;
}
float Player::getFramesNum() const
{
    return this->framesNum;
}
