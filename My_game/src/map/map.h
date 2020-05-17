#pragma once
#include"../player/entity.h"

class Map
{
    const int WIDTH_MAP = 40;
    const int HEIGHT_MAP = 46;
	sf::Texture t_floor;
	sf::Sprite s_floor;
	sf::Sprite s_wall;
	sf::Sprite s_locker;

    sf::String TileMap[46] =
    {
	    "0000000000000000000000000000000000000000",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"2222222222222222222222222222222222222222",
    };
    public:
		//Конструктор
		Map();
		//функція для рисування карти
       void update(sf::RenderWindow& window);
       //Функції для иявлення колізій і непрохідности гравця та душ
	   void colision(Player& player);
	   void colision(Neutral& player);
 };