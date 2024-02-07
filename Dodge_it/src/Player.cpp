
//SREERAG MURALEEDHARAN

#include "../incl/Player.hpp"
#include"../incl/Line.hpp"
#include"../incl/Scoreboard.hpp"

void Player::initPlayer()
{

    this->initVariables();
    this->initPlayerTexture();

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
    this->collider.setPosition(this->colliderX, this->colliderY);
    this->playerSize.x = 264;
    this->playerSize.y = 200; //size of each frame
    this->framesNum = 2;
    this->animDuration = 0.45; //seconds
    this->clockForPlayer;
    this->delta = 0;
}

void Player::initPlayerTexture()
{
    this->playerFoto.loadFromFile("res\\images\\player\\car_idle.png");
    this->playerCar.setTexture(this->playerFoto);
    this->playerCar.setPosition(width / 2 - 100, height / 2 + 160);
}


void Player::initPlayerSound()
{
    this->lifesound.loadFromFile("res\\sound\\life sound.ogg");
    this->playLife.setBuffer(this->lifesound);

    this->collisonsound.loadFromFile("res\\sound\\crash.ogg");
    this->collideSounds.setBuffer(this->collisonsound);

    this->lifeimp.loadFromFile("res\\sound\\life impact.ogg");
    this->playLifeImp.setBuffer(this->lifeimp);

    this->turnsound.loadFromFile("res\\sound\\turn sound.ogg");
    this->playTurn.setBuffer(this->turnsound);
}

void Player::update(Map* map) {


    if (map->getScore() == 1000)
    {
        this->setSpeed(250.0f);
        this->setanimDuration(0.40);

    }
    if (map->getScore() == 2000)
    {
        this->setSpeed(300.0f);
        this->setanimDuration(0.35);

    }
    if (map->getScore() == 3000)
    {
        this->setSpeed(350.0f);
        this->setanimDuration(0.30);
    }

    if (this->getIsAlive())
        this->setPosZ(getPosZ() + this->speed);

    if (this->getIsAlive())
        this->setDelta(this->getDelta() + this->clockForPlayer.restart().asSeconds());

    if (this->getPosZ() >= lines.size() * segL)
        this->setPosZ(this->getPosZ() - lines.size() * segL);

    if (this->getPosZ() < 0)
        this->setPosZ(this->getPosZ() + lines.size() * segL);

    //----PLAYER-ANIMATION----//

    //---Get Current Frame----//
    int animFrame = static_cast<int>((this->getDelta() / this->getanimDuration()) * this->getFramesNum()) % this->framesNum;

    //---Set Sprite Rectangle Based on Frame---//
    this->playerCar.setTextureRect(IntRect(animFrame * playerSize.x, 0, playerSize.x, playerSize.y));

}

void Player::collisionTest(Map* map)
{
    if (this->getIsAlive() == true)
        if (lines[map->getStartPos() + 5].getObstacleBounds().intersects(collider.getGlobalBounds()))
        {

            if (getLifeCollected() == 0)
            {
                this->setIsAlive(false);
                this->collideSounds.play();
            }

            else if (getLifeCollected() > 0)
            {
                this->playLifeImp.play();
                this->setLifeCollected((this->getLifeCollected() - 1));
            }

        }
    if (lines[map->getStartPos() + 5].getLifeBounds().intersects(collider.getGlobalBounds()))
    {
        this->setLifeCollected(this->getLifeCollected() + 1);
        this->playLife.play();
    }
}


void Player::playerReset()
{
    this->setPosZ(0);
    this->setPosX(0);
    this->setIsAlive(false);
    this->setLifeCollected(0);
    this->setSpeed(200.0f);
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
    this->colliderX = x;
}
void Player::setColliderY(float y)
{
    this->colliderY = y;
}
void Player::setPosZ(int z)
{
    this->posZ = z;
}
void Player::setPosX(int x)
{ 
    this->posX = x;
}
void Player::setIsAlive(bool alive) 
{ 
    this->isAlive = alive;
}
void Player::setSpeed(float s) 
{
    this->speed = s;
}
void Player::setLifeCollected(int collected)
{ 
    this->life_collected = collected; 
}
void Player::setanimDuration(float x)
{ 
    this->animDuration = x; 
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
    return this->colliderX; 
}
float Player::getColliderY() const 
{
    return this->colliderY;
}
int Player::getPosZ() const
{
    return this->posZ;
}
int Player::getPosX() const
{
    return this->posX;
}
bool Player::getIsAlive() const
{ 
    return this->isAlive;
}
float Player::getSpeed() const 
{ 
    return this->speed;
}
int Player::getLifeCollected() const 
{ 
    return this->life_collected;
}
float Player::getanimDuration() const 
{ 
    return this->animDuration;
}
float Player::getDelta() const
{
    return this->delta;
}
float Player::getFramesNum() const
{
    return this->framesNum;
}