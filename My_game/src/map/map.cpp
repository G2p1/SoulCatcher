#include"map.h"

Map::Map()
{
	t_floor.loadFromFile("src/map/Images/map.png");
	s_floor.setTexture(t_floor);
	s_floor.setTextureRect(sf::IntRect(0, 0, 32, 32));

	s_wall.setTexture(t_floor);
	s_wall.setTextureRect(sf::IntRect(64, 0, 32, 32));

	s_locker.setTexture(t_floor);
	s_locker.setTextureRect(sf::IntRect(32, 0, 32, 32));
}

void Map::update(sf::RenderWindow& window)
{
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {

			if (TileMap[i][j] == ' ')
			{
				s_floor.setPosition(i * 32, j * 32);
				window.draw(s_floor);
			}
			if (TileMap[i][j] == 's')
			{
				s_locker.setPosition(i * 32, j * 32);
				window.draw(s_locker);
			}
			if (TileMap[i][j] == '0' || TileMap[i][j] == '1' || TileMap[i][j] == '2'|| TileMap[i][j] == '3')
			{
				s_wall.setPosition(i * 32, j * 32);
				window.draw(s_wall);
			}
		}
	}
}
void Map::colision(Player& player)
{if(player.getlife())
	for (int i = (player.getX()- player.getW() / 2) / 32; i < (player.getX() + player.getW()/2) / 32; i++) {
		for (int j = (player.getY() - player.getH() / 2) / 32; j < (player.getY() + player.getH()/2) / 32; j++) {
			if (TileMap[i][j] == '3') {
				player.setCoordinates(player.getX(), player.getY()+0.5);
			}
			if (TileMap[i][j] == '0') {
				player.setCoordinates(player.getX()+0.5, player.getY());
			}
			if (TileMap[i][j] == '1') {
				player.setCoordinates(player.getX(), player.getY()-0.5 );
			}
			if (TileMap[i][j] == '2') {
				player.setCoordinates(player.getX()-0.5, player.getY());
			}

		}
	}

}

void Map::colision(Neutral& player)
{
	if (player.getlife())
		for (int i = (player.getX() - player.getW() / 2) / 32; i < (player.getX() + player.getW() / 2) / 32; i++) {
			for (int j = (player.getY() - player.getH() / 2) / 32; j < (player.getY() + player.getH() / 2) / 32; j++) {
				if (TileMap[i][j] == '3') {
					player.setCoordinates(player.getX(), player.getY() + 0.5);
				}
				if (TileMap[i][j] == '0') {
					player.setCoordinates(player.getX() + 0.5, player.getY());
				}
				if (TileMap[i][j] == '1') {
					player.setCoordinates(player.getX(), player.getY() - 0.5);
				}
				if (TileMap[i][j] == '2') {
					player.setCoordinates(player.getX() - 0.5, player.getY());
				}

			}
		}

}