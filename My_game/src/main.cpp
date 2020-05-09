#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include"player/entity.h"
#include"camera/camera.h"
#include"map/map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1980, 1080), "SFML window");

    sf::Clock clock;
    float time;
   
    Camera cam;
    Map map;

    Player player ("player", 100, 100, "player_1.png", 115, 154);

    Enemy enemy("enemy", 250, 250, "enemy_1.png", 233, 165);

    Let tree("tree", 500, 500, "let_1.png", 815, 870);
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
        enemy.update(player, time);
        tree.colision(player);

      

        cam.setCenterCHaracter(player);
        cam.keyMove(time);
        cam.mouseMove(window, time);

        window.setView(cam.getView());
        window.clear(sf::Color(24, 145, 75));
        window.draw(tree.getSprite());
        window.draw(player.getSprite());
        window.draw(enemy.getSprite());
        window.display();
    }

}