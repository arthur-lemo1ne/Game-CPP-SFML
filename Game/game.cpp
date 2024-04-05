#include "Dependencies.h"
#include "Ball.h"
#include "Anim.h"


int main()
{
    srand(time(0));

    // Window Initialisation
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Click Them All!", sf::Style::Fullscreen);
    window.setKeyRepeatEnabled(false);


    sf::Music music;
    if (!music.openFromFile("Paradigm Rush.mp3"))
    {
        // error
    }
    music.setVolume(50.f);
    music.setLoop(true);
    music.play();


    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Pop - Sound Effect.mp3")){}
    sf::Sound pop, pop2;
    pop.setBuffer(buffer);
    pop2.setBuffer(buffer);

    // UI Initialisation --------------------------------------------------------------------------------------------------------------
    sf::Text UI;
    UI.setCharacterSize(24);
    UI.setFillColor(sf::Color::White);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }
    UI.setFont(font);


    sf::Text button;
    button.setCharacterSize(40);
    button.setFont(font);
    button.setFillColor(sf::Color::White);
    button.setString("RESTART");
    button.setOrigin(button.getGlobalBounds().getSize().x / 2, button.getGlobalBounds().getSize().y / 2);
    button.setPosition(window.getSize().x/2, window.getSize().y / 2 + 100);


    sf::Text Timeur;
    Timeur.setCharacterSize(50);
    Timeur.setFillColor(sf::Color::White);
    Timeur.setFont(font);
    Timeur.setOrigin(Timeur.getGlobalBounds().getSize().x / 2, Timeur.getGlobalBounds().getSize().y / 2);
    Timeur.setPosition(window.getSize().x/2, 25);



    //Game Initialisation -------------------------------------------------------------------------------------------------------------
    Game game = Game(window.getSize().x, window.getSize().y);
    bool Clicked = false;
    std::deque<anim> anims;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        if(game.GetLife())
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && Clicked == false)
            {
                bool sound = game.Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if(sound)
                {
                    anims.push_back(anim(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y,1));
                    pop.stop();
                    pop.play();
                }
                Clicked = true;  
            }
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Clicked = false;
            }
            UI.setString("Score: " + std::to_string(game.GetScore()) + '\n' + "Level: " + std::to_string(game.GetLevel()) + '\n' + "Combo: " + std::to_string(game.GetCombo()));
            

            Timeur.setOrigin(Timeur.getGlobalBounds().getSize().x / 2, Timeur.getGlobalBounds().getSize().y / 2);
            Timeur.setPosition(window.getSize().x / 2, 25);

            if((int)game.GetTimer() > 5)
            {
                Timeur.setFillColor(sf::Color::White);
                Timeur.setString(std::to_string((int)game.GetTimer()));
            }
            else
            {
                Timeur.setFillColor(sf::Color::Red);
                Timeur.setString(std::to_string(game.GetTimer()));
            }
            
            
            game.NextFrame(window.getSize().x, window.getSize().y);
        }
        else
        {
            window.clear();
            
            UI.setString("GAME OVER\nYour Score: " + std::to_string(game.GetScore()));
            UI.setOrigin(UI.getGlobalBounds().getSize().x / 2, UI.getGlobalBounds().getSize().y / 2);
            UI.setPosition(window.getSize().x/2,window.getSize().y/2);
            Timeur.setOrigin(Timeur.getGlobalBounds().getSize().x / 2, Timeur.getGlobalBounds().getSize().y / 2);
            Timeur.setPosition(window.getSize().x/2, 25);
            Timeur.setString("0");
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
                game = Game(window.getSize().x, window.getSize().y);
                UI.setOrigin(0,0);
                UI.setPosition(0,0);
            }
        }
        window.clear();
        
        

        for (int i = 0; i < anims.size(); i++)
        {
            anims[i].NextFrame();
            window.draw(anims[i]);
            if (anims[0].NeedClear())
            {
                anims.pop_front();
            }
        }
        

        window.draw(game);
        if(!game.GetLife())
            window.draw(button);
        window.draw(UI);
        window.draw(Timeur);


        window.display();
    }

    return 0;
}

