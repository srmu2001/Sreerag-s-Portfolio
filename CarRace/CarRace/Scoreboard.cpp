#include"Scoreboard.hpp"





// Implementation for ScoreBoard class
ScoreBoard::ScoreBoard(sf::RenderWindow& app, sf::Font font, int score)
{
    font.loadFromFile("font\\Crang.ttf");

    this->box.setSize(sf::Vector2f(500, 220));
    this->box.setPosition(width / 2 - 250, height / 2 - 120);
    this->box.setFillColor(sf::Color(0, 0, 0, 240));
    this->box.setOutlineColor(sf::Color::White);
    this->box.setOutlineThickness(3);

    this->text[0].setPosition(box.getPosition().x + 127, box.getPosition().y + 10);
    this->text[0].setFillColor(sf::Color::White);
    this->text[0].setFont(font);
    this->text[0].setCharacterSize(28);
    this->text[0].setString("You are dead !");

    this->text[1].setPosition(box.getPosition().x + 180, box.getPosition().y + 80);
    this->text[1].setFillColor(sf::Color(255, 215, 0));
    this->text[1].setFont(font);
    this->text[1].setCharacterSize(20);

    this->text[2].setPosition(box.getPosition().x + 145, box.getPosition().y + 130);
    this->text[2].setFillColor(sf::Color(255, 0, 0));
    this->text[2].setFont(font);
    this->text[2].setCharacterSize(20);

    this->space.setPosition(box.getPosition().x + 50, box.getPosition().y + 180);
    this->space.setFillColor(sf::Color::White);
    this->space.setFont(font);
    this->space.setCharacterSize(20);
    this->space.setString("Press Space to return to Menu");

    if (checkHighScore(score))
    {
        this->text[1].setString("Score: " + to_string(score));
        this->text[2].setString("NEW HIGHSCORE!!!");
    }
    else
    {
        text[1].setString("Score: " + to_string(score));
    }

    app.draw(box);
    app.draw(text[0]);
    app.draw(text[1]);
    app.draw(text[2]);
    app.draw(space);
}

bool ScoreBoard::checkHighScore(int score)
{
    std::vector<int> highScores;

    // Read existing high scores
    std::ifstream ifile("data\\score.dat", std::ios::in | std::ios::binary);
    if (ifile)
    {
        int existingScore;
        while (ifile.read(reinterpret_cast<char*>(&existingScore), sizeof(existingScore)))
        {
            highScores.push_back(existingScore);
        }
        ifile.close();
    }

    // Add the current score to the high scores if it doesn't already exist
    if (std::find(highScores.begin(), highScores.end(), score) == highScores.end())
    {
        highScores.push_back(score);

        // Sort the high scores in descending order
        std::sort(highScores.begin(), highScores.end(), std::greater<int>());

        // Truncate the list to keep only the top 5 scores
        highScores.resize(std::min(static_cast<size_t>(NUM_HIGH_SCORES), highScores.size()));

        // Write the updated high scores back to the file
        std::ofstream ofile("data\\score.dat", std::ios::out | std::ios::binary);
        for (const int& updatedScore : highScores)
        {
            ofile.write(reinterpret_cast<const char*>(&updatedScore), sizeof(updatedScore));
        }
        ofile.close();
    }

    return score == highScores[0];
}

void ScoreBoard::handleEvents(sf::RenderWindow& app, Player* player, Map* map)
{
    if (Keyboard::isKeyPressed(Keyboard::Space))
    {
        sf::sleep(sf::milliseconds(500));
        if (LoadMenu(app, false))
        {
            player->playerReset();
            map->setScore(0);
        }
    }
}




