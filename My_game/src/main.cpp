#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include"player/entity.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Clock clock;
    float time;
   
    Player player ("player", 100, 100, "player_1.png", 115, 154);

    Enemy enemy("enemy", 250, 250, "enemy_1.png", 233, 165);

    while (window.isOpen())
    {

        time = clock.getElapsedTime().asMicroseconds();
        time /= 800;
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(window, time, event);
        

        window.clear(sf::Color(24, 145, 75));
        window.draw(player.getSprite());
        window.draw(enemy.getSprite());
        window.display();
    }

}