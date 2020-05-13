#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include"player/entity.h"
#include"camera/camera.h"
#include"map/map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window", sf::Style::Fullscreen);

    sf::Clock clock;
    float time;
   
    Camera cam;
    Map map;

    Player player ("player", 200, 200, "player_1.png", 115, 154);

    Enemy enemy("enemy", 800, 350, "enemy_1.png", 233, 165);

    Let tree("tree", 500, 500, "let_1.png", 300, 300);

    Neutral* soul;
    soul = new Neutral("soul", 500, 500, "let_1.png", 50, 50);

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
        player.attack(window, event, enemy, tree, time);
        enemy.update(player, time);
        tree.colision(player);
        soul->colision(player);
        map.colision(player);

        cam.setCenterCHaracter(player);
        cam.keyMove(time);
        cam.mouseMove(window, time);
        

        window.setView(cam.getView());
        window.clear(sf::Color(24, 145, 75));

        map.update(window);

        window.draw(tree.getSprite());
        window.draw(player.getSprite());
        window.draw(enemy.getSprite());
        window.draw(soul->getSprite());
        window.draw(player.getBow().getSprite());

        window.display();
    }

}