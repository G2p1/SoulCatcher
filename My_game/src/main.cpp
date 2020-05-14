#include<stdlib.h>
#include"time.h"
#include<array>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include"player/entity.h"
#include"camera/camera.h"
#include"map/map.h"


int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window", sf::Style::Fullscreen);

   

    sf::Clock clock, timer;
    float time;
    float locale_timer;
   
    bool attack_time = true;

    Camera cam;
    Map map;

    Player player ("player", 200, 200, "player_1.png", 51, 68);

    std::array<Enemy, 4> enemys;
    
    for (int i = 0; i < enemys.size(); i++)
    {
        float x = rand() % (45 * 31) + 1;
        float y = rand() % (39 * 31) + 1;
        enemys[i].setCoordinates(x, y);
    }
    
    Enemy enemy("enemy", 800, 350, "enemy_1.png", 107, 74);

    std::array<Let, 15> shaphs;

    for (int i = 0; i < shaphs.size(); i++)
    {
        float x = rand() % (45 * 31) + 1;
        float y = rand() % (39 * 31) + 1;
        shaphs[i].setCoordinates(x, y);
    }
    Let tree("tree", 500, 500, "shkaph.png", 44, 69);

    std::array<Neutral, 10> souls;

    for (int i = 0; i < souls.size(); i++)
    {
        float x = rand() % (45 * 31) + 1;
        float y = rand() % (39 * 31) + 1;
        souls[i].setCoordinates(x, y);
    }
   

    while (window.isOpen())
    {
        
        locale_timer = timer.getElapsedTime().asSeconds();
        if (locale_timer > 2)
        {
            attack_time = true;
            timer.restart();

        }

        time = clock.getElapsedTime().asMicroseconds();
        time /= 800;
        clock.restart();
        
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
           
        }

        player.update(window, time, event);
        for (int i = 0; i < enemys.size(); i++)
        {
            enemys[i].update(player, time);
        }
        if (attack_time)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                attack_time = false;
            }
            for(int i = 0; i < enemys.size();i++)
                player.attack(window, event, enemys[i], time);

            for(int i = 0; i < shaphs.size();i++)
                player.attack(window, event, shaphs[i], time);

            player.getSword().setPosition(player.getX(), player.getY());
            
        }

        for (int i = 0; i < enemys.size(); i++)
            for(int j = 0; j < shaphs.size();j++)
        {
            shaphs[j].colision(enemys[i]);
          }
        
        for (int i = 0; i < shaphs.size(); i++)
        {
            shaphs[i].colision(player);

        }
        
        for (int i = 0; i < souls.size(); i++)
        {
            souls[i].colision(player);
            souls[i].update(time);
           
            map.colision(souls[i]);
        }
        map.colision(player);
        

        cam.setCenterCHaracter(player);
        cam.keyMove(time);
        cam.mouseMove(window, time);

        window.setView(cam.getView());
        window.clear(sf::Color(128, 106, 89));

        map.update(window);
        
        for (int i = 0; i < shaphs.size(); i++)
        {
            window.draw(shaphs[i].getSprite());
        }
        window.draw(player.getSprite());
        for (int i = 0; i < enemys.size(); i++)
        {
            window.draw(enemys[i].getSprite());
        }
        for (int i = 0; i < souls.size(); i++)
        {
            window.draw(souls[i].getSprite());
        }
        window.draw(player.getSword());
        window.draw(player.getBow().getSprite());

        window.draw(cam.getSprite(0));
        window.draw(cam.getSprite(1));

        window.draw(cam.getText(0));
        window.draw(cam.getText(1));
           
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {

                cam.menu(window, clock, event);

            }

        window.display();

        cam.died(player, window,clock);
    }

}