#include "Game.hpp"



Game::Game()
{
    this->initApp();
}

Game::~Game() {}

void Game::initApp()
{
    this->app.create(VideoMode(width, height), "Dodge it", Style::Close);
    this->app.setVerticalSyncEnabled(true);
    this->app.setFramerateLimit(60);

    if (LoadMenu(this->app, true) == true)
        this->initGame();
}

void Game::initGame()
{
    this->initMap();
    this->initPlayer();
    this->initSound();
    this->run();
}

void Game::initMap()
{
    this->map = &gameMap;
    this->map->initObstacles();
    this->map->initMap();
}

void Game::initPlayer()
{
    this->player = &playerr;
    this->player->initPlayer();
    this->player->setIsAlive(false);
}

void Game::initSound()
{
    this->player->initPlayerSound();
    this->gameMusic.openFromFile("sound\\game sound.ogg");
    this->gameMusic.setLoop(true);
}

void Game::updateGame()
{
    this->player->update(this->map);
    this->map->updateBackground();
    this->map->updateScore(this->clockForScore, this->player);
    this->player->collisionTest(this->map);
}

void Game::drawGameElements()
{
    this->app.clear();
    this->map->drawBackground(this->app);
    this->map->drawMap(this->app, this->player);
    this->map->drawObstacles(this->app);

    if (this->player->getIsAlive())
    {
        this->player->drawPlayer(this->app);
        this->map->drawScore(this->app);
    }
    else if (!this->player->getIsAlive() && this->map->getScore() == 0)
    {
        this->map->drawStart(this->app);
    }
    if (!this->player->getIsAlive() && this->map->getScore() > 0)
    {
        this->gameMusic.stop();
        ScoreBoard scoreboard(this->app, this->map->getFont(), this->map->getScore());
        scoreboard.handleEvents(this->app, this->player, this->map);
    }

    this->app.display();
}

void Game::handleEvents()
{
    sf::Event event;

    while (this->app.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !this->player->getIsAlive() && this->map->getScore() == 0)
        {
            sf::sleep(sf::milliseconds(500));
            this->gameMusic.play();
            this->player->setIsAlive(true);
            this->app.setKeyRepeatEnabled(false);
            this->clockForScore.restart().asSeconds();
            break;
        }
        else if (event.type == sf::Event::Closed)
        {
            this->app.close();
            return;
        }
    }

    this->player->handleEvents();
}

void Game::run()
{
    this->app.setKeyRepeatEnabled(false);

    while (this->app.isOpen())
    {
        this->handleEvents();
        this->updateGame();
        this->drawGameElements();
        this->map->Fade();
    }
}
