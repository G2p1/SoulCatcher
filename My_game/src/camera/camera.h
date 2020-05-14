#pragma once
#include<iostream>
#include<sstream>
#include"SFML/Graphics.hpp"
#include"../player/entity.h"
class Camera
{
	sf::View m_view;
	
	sf::Texture t_health;
	sf::Texture t_soul;
	sf::Texture back_ground;
	sf::Texture back_ground_2;
	sf::Texture button_play;
	sf::Texture button_exit;

	sf::Sprite s_health;
	sf::Sprite s_soul;
	sf::Sprite s_back_ground;
	sf::Sprite s_back_ground_2;
	sf::Sprite s_button_play;
	sf::Sprite s_button_exit;
	
	sf::Texture t_died;
	sf::Sprite s_died;

	sf::Font font;
	sf::Text health;
	sf::Text soul;



public:
	Camera();

	sf::View getView();
	void keyMove(float time);
	void mouseMove(sf::RenderWindow& window, float time);
	void setCenterCHaracter(Player& player);
	sf::Sprite getSprite(int a);
	sf::Text getText(int a);
	void menu(sf::RenderWindow& window, sf::Clock& clock, sf::Event & event);
	void died(Player& player, sf::RenderWindow& window, sf::Clock& clock);
};