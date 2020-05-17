#include<stdlib.h>
#include"time.h"
#include<array>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include"player/entity.h"
#include"camera/camera.h"
#include"map/map.h"

Camera cam;
bool game();
void startGames();
int main()
{
    startGames();
}
void startGames()
{
    if (game()) 
        startGames();
}

bool game()
{
    //Запуск генерації випадкових чисел
    srand(time(0));

    //створення вікна з допомогою бібліотеки СФМЛ
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window", sf::Style::Fullscreen);

    //Створення годинника, та змінної яка буде контролювати однаковість перемщення на різних машинах
    sf::Clock clock, timer;
    float time;
    float locale_timer;
    //змінна яка контролює інтервал між атаками гравця
    bool attack_time = true;
    //Створення камери
    
    //Створення карти
    Map map;
    //Створення гравця
    Player player("player", 200, 200, "player_1.png", 51, 68);
    //створеня за допомогою контейнерів стл 4 ворогів
    std::array<Enemy, 4> enemys;
    //Задання їм випадкових координат карти
    for (int i = 0; i < enemys.size(); i++)
    {
        float x = rand() % (45 * 31) + 1;
        float y = rand() % (39 * 31) + 1;
        enemys[i].setCoordinates(x, y);
    }

    //Створення перешкод та задання їм випадкових координат на карті
    std::array<Let, 15> shaphs;

    for (int i = 0; i < shaphs.size(); i++)
    {
        float x = rand() % (45 * 31) + 1;
        float y = rand() % (39 * 31) + 1;
        shaphs[i].setCoordinates(x, y);
    }

    //Створення душ та задання їм випадкових координат на карті
    std::array<Neutral, 10> souls;

    for (int i = 0; i < souls.size(); i++)
    {
        float x = rand() % (45 * 31) + 1;
        float y = rand() % (39 * 31) + 1;
        souls[i].setCoordinates(x, y);
    }
    sf::Event event;
    cam.begin(window, clock, event, player, shaphs, enemys, souls);
    //Головний цикл який працює поки вікно відкрите
    while (window.isOpen())
    {
        //Інтервал атаки гравця
        locale_timer = timer.getElapsedTime().asSeconds();
        if (locale_timer > 2)
        {
            attack_time = true;
            timer.restart();

        }
        //змінна яка контролює рух
        time = clock.getElapsedTime().asMicroseconds();
        time /= 800;
        clock.restart();
        //Створення змінної яка приймає події

        //цикл який відстежує та оброблює ці події
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        // Функція новлення стану гравця
        player.update(window, time, event);
        //Функція оновлення стану ворогів
        for (int i = 0; i < enemys.size(); i++)
        {
            enemys[i].update(player, time);
        }
        //Розгалудження яке відповідає за інтервал атак
        if (attack_time)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                attack_time = false;
            }
            for (int i = 0; i < enemys.size(); i++)
                player.attack(window, event, enemys[i], time);

            for (int i = 0; i < shaphs.size(); i++)
                player.attack(window, event, shaphs[i], time);

            player.getSword().setPosition(player.getX(), player.getY());

        }
        //цикл який відповідає за оброблення перетинів перешкод з ворогами
        for (int i = 0; i < enemys.size(); i++)
            for (int j = 0; j < shaphs.size(); j++)
            {
                shaphs[j].colision(enemys[i]);
            }
        //Цикл який відповідає за перетин перешкод з гравцем
        for (int i = 0; i < shaphs.size(); i++)
        {
            shaphs[i].colision(player);

        }
        //цикл який відповідає оновленню стан душі та її перетину з картою та гравцем
        for (int i = 0; i < souls.size(); i++)
        {
            souls[i].colision(player);
            souls[i].update(time);

            map.colision(souls[i]);
        }
        //Відповідає за перетин гравця з картою
        map.colision(player);

        ///Функції які відпвідають за переміщення камери
        cam.setCenterCHaracter(player);
        cam.keyMove(time);
        cam.mouseMove(window, time);

        //Функцї які звязують камеру з вікном та починають рисування об'єктів
        window.setView(cam.getView());
        //Очищення вікна
        window.clear(sf::Color(128, 106, 89));
        //рисування карти
        map.update(window);
        //рисування перешкод
        for (int i = 0; i < shaphs.size(); i++)
        {
            window.draw(shaphs[i].getSprite());
        }
        //Рисування ворогів
        window.draw(player.getSprite());
        for (int i = 0; i < enemys.size(); i++)
        {
            window.draw(enemys[i].getSprite());
        }
        //рисування душ
        for (int i = 0; i < souls.size(); i++)
        {
            window.draw(souls[i].getSprite());
        }
        //рисування гравця та його зброї
        window.draw(player.getSword());
        window.draw(player.getBow().getSprite());
        //Рисування примітивного інтерфейсу(серце та луша які позначають кількість здоров'я та кількість зібраних душ)
        window.draw(cam.getSprite(0));
        window.draw(cam.getSprite(1));
        //Рисування чисельних данних про кількість здоров'я та душ
        window.draw(cam.getText(0));
        window.draw(cam.getText(1));
        //реалізація меню
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {

            cam.menu(window, clock, event, player, shaphs, enemys, souls);
            if (cam.getRestart())
                return true;
        }
        //відображення всего що нарисували
        window.display();
        //Меню при смерти гравця
        cam.died(player, window, clock);
    }
    return false;
}