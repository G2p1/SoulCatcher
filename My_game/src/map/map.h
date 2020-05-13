#pragma once
#include"../player/entity.h"

class Map
{
    const int WIDTH_MAP = 40;
    const int HEIGHT_MAP = 25;
	sf::Texture t_floor;
	sf::Sprite s_floor;
	sf::Sprite s_wall;
	sf::Sprite s_locker;

    sf::String TileMap[25] =
    {
	    "0000000000000000000000000000000000000000",
		"3                                      1",
		"3   s              s                   1",
		"3                           s          1",
		"3                                      1",
		"3      s                               1",
		"3                                      1",
		"3                                      1",
		"3                s                     1",
		"3                                      1",
		"3              s                       1",
		"3                                      1",
		"3                                      1",
		"3                               s      1",
		"3                  s                   1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"3        s                             1",
		"3                                      1",
		"3                                      1",
		"3                                      1",
		"2222222222222222222222222222222222222222",
    };
    public:
		Map();
       void update(sf::RenderWindow& window);
       void colision(Player& player);
 };