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

    sf::Clock clock;
    float time;
   
    Camera cam;
    Map map;

    Player player ("player", 200, 200, "player_1.png", 51, 68);

    std::array<Enemy, 4> enemys;
    
    for (int i = 0; i < enemys.size(); i++)
    {
        float x = rand() % (30 * 31) + 2;
        float y = rand() % (40 * 31) + 2;
        enemys[i].setCoordinates(x, y);
    }
    
    Enemy enemy("enemy", 800, 350, "enemy_1.png", 107, 74);

    std::array<Let, 4> shaphs;

    for (int i = 0; i < shaphs.size(); i++)
    {
        float x = rand() % (30 * 31) + 2;
        float y = rand() % (40 * 31) + 2;
        shaphs[i].setCoordinates(x, y);
    }
    Let tree("tree", 500, 500, "shkaph.png", 44, 69);

    std::array<Neutral, 10> souls;

    for (int i = 0; i < souls.size(); i++)
    {
        float x = rand() % (30 * 31) + 2;
        float y = rand() % (40 * 31) + 2;
        souls[i].setCoordinates(x, y);
    }
   

    while (window.isOpen())
    {

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

        for (int i = 0; i < enemys.size(); i++)
            for(int j = 0; j < shaphs.size();j++)
        {
            shaphs[j].colision(enemys[i]);

            player.attack(window, event, enemys[i], shaphs[j], time);
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
        window.draw(player.getBow().getSprite());

        window.display();
    }

}