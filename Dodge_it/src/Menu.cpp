
//SREERAG MURALEEDHARAN

#include "../incl/Menu.hpp"
#include"../incl/Line.hpp"
#include"../incl/Map.hpp"
#include"../incl/Game.hpp"
#include<vector>


sf::Font Menu::font;
sf::Music introMusic;
sf::SoundBuffer click;
sf::Sound click_sound;


bool showInstructions;
bool showHighScores;
bool flowMenu;
bool start;



void Menu::LoadAssests()
{
    // Load sound files and fonts
    click.loadFromFile("res\\sound\\click.ogg");
    click_sound.setBuffer(click);

    font.loadFromFile("res\\font\\font.ttf");

    introMusic.openFromFile("res\\sound\\intro sound.ogg");
    introMusic.setLoop(true);
}

Menu::Menu(int width, int height)
{
    // Initialize menu items and visual elements
    showInstructions = false;
    showHighScores = false;
    this->intro_img2.loadFromFile("res\\images\\background\\intro2.png");
    this->intro2.setTexture(intro_img2);

    this->box.setSize(sf::Vector2f(620, 630));
    this->box.setPosition(width / 2 - 315, height / 2 - 315);
    this->box.setFillColor(sf::Color(0, 0, 0, 230));
    this->box.setOutlineColor(sf::Color::White);
    this->box.setOutlineThickness(3);

    for (int i = 0; i < No_of_Items; i++)
    {
        this->text[i].setFont(font);
        this->text[i].setFillColor(sf::Color(255, 255, 255));
        this->text[i].setPosition(width / 2 - 100, 200 + 100 * i);
        this->text[i].setCharacterSize(50);
    }

    this->text[0].setString("Play");
    this->text[0].setFillColor(sf::Color(6, 248, 245));
    this->text[1].setString("Instructions");
    this->text[2].setString("High Score");
    this->text[3].setString("Exit");

    this->selectedItemIndex = 0;
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window)
{
    // Draw menu and additional screens
    window.draw(intro2);
    window.draw(box);

    if (!showInstructions && !showHighScores)
    {
        for (int i = 0; i < No_of_Items; i++)
        {
            window.draw(text[i]);
        }
    }

    if (showInstructions)
    {
        DrawInfo(window);
    }

    if (showHighScores)
    {
        DrawHighScores(window);
    }
}

void Menu::MoveUp()
{
    // Move selection upwards
    if (this->selectedItemIndex > 0)
    {
        this->text[this->selectedItemIndex].setFillColor(sf::Color::White);
        this->selectedItemIndex--;
        this->text[this->selectedItemIndex].setFillColor(sf::Color(6, 245, 248));
    }
}

void Menu::MoveDown()
{
    // Move selection downwards
    if (this->selectedItemIndex < No_of_Items - 1)
    {
        this->text[this->selectedItemIndex].setFillColor(sf::Color::White);
        this->selectedItemIndex++;
        this->text[this->selectedItemIndex].setFillColor(sf::Color(6, 245, 248));
    }
}

int Menu::GetPressedItem()
{
    // Get the index of the selected menu item
    return this->selectedItemIndex;
}

bool LoadMenu(sf::RenderWindow& app, bool flowIntro)
{
    // Load menu assets and create menu object
    Menu::LoadAssests();
    Menu Menu_items(app.getSize().x, app.getSize().y);

    sf::Texture intro_img;
    intro_img.loadFromFile("res\\images\\background\\intro.png");
    sf::Sprite intro(intro_img);

    if (!flowIntro)
    flowMenu = true;

    app.setKeyRepeatEnabled(false);
    introMusic.play();

    while (app.isOpen())
    {
        app.clear();

        if (flowIntro)
        {
            // Handle introduction screen
            sf::Event ev;
            while (app.pollEvent(ev))
            {
                if (ev.type == sf::Event::Closed)
                    exit(0);
            }
            app.draw(intro);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                sf::sleep(sf::milliseconds(500));
                flowMenu = true;
                flowIntro = false;
            }
        }

        sf::Event event;
        if (flowMenu)
        {
            // Handle menu interactions
            app.clear();
            Menu_items.draw(app);
            introMusic.stop();

            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    exit(0);
                };
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        click_sound.play();
                        Menu_items.MoveDown();
                    }
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        click_sound.play();
                        Menu_items.MoveUp();
                    }
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Return)
                    {
                        click_sound.play();
                        sf::sleep(sf::milliseconds(500));
                        switch (Menu_items.GetPressedItem())
                        {
                        case 0:
                            return true;
                        case 1:
                            showInstructions = !showInstructions;
                            break;
                        case 2:
                            showHighScores = !showHighScores;
                            break;
                        case 3:
                            exit(0);
                        }
                    }
                }
            }
        }

        app.display();
    }
}

void Menu::DrawHighScores(sf::RenderWindow& app)
{
    // Draw high scores on the screen
    std::ifstream ifile("res\\data\\score.dat", std::ios::in | std::ios::binary);
    std::vector<int> highScores;

    if (ifile)
    {
        int score;
        while (ifile.read(reinterpret_cast<char*>(&score), sizeof(score)))
        {
            highScores.push_back(score);
        }
        ifile.close();
    }

    // Sort the high scores in descending order
    std::sort(highScores.rbegin(), highScores.rend());

    // Display the scores in a box
    sf::Font font;
    font.loadFromFile("res\\font\\Crang.ttf"); // Replace with the path to your font file

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(255, 215, 0));

    text.setPosition(410, 170);
    text.setString("High Scores ");

    app.draw(text);

    for (size_t i = 0; i < std::min(highScores.size(), static_cast<size_t>(5)); ++i)
    {
        text.setPosition(width / 2 - 105, 270 + 70 * i);
        text.setString("RANK  " + std::to_string(i + 1) + ".   " + std::to_string(highScores[i]));
        app.draw(text);
    }
}

void Menu::DrawInfo(sf::RenderWindow& app)
{
    // Draw instructions on the screen
    sf::Font font;
    font.loadFromFile("res\\font\\Crang.ttf"); // Replace with the path to your font file

    for (int i = 0; i < 5; i++)
    {
        this->InfoText[i].setFont(font);
        this->InfoText[i].setFillColor(sf::Color(255, 255, 255));
        this->InfoText[i].setPosition(width / 2 - 295, 170 + 100 * i);
    }

    this->InfoText[0].setString("Drive as far as you can !");
    this->InfoText[1].setString("Use arrow keys to move the car");
    this->InfoText[2].setString("Right Arrow: Move Right");
    this->InfoText[3].setString("Left Arrow: Move Left");
    this->InfoText[4].setString("Pick up Life points for immunity");

    for (int i = 0; i < 5; i++)
    {
        app.draw(this->InfoText[i]);
    }
}



