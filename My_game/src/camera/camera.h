#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include <array>
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
	sf::Texture button_restart;
	sf::Texture button_save;
	sf::Texture button_load;
	sf::Texture button_begin;

	sf::Sprite s_health;
	sf::Sprite s_soul;
	sf::Sprite s_back_ground;
	sf::Sprite s_back_ground_2;
	sf::Sprite s_button_play;
	sf::Sprite s_button_exit;
	sf::Sprite s_button_restart;
	sf::Sprite s_button_save;
	sf::Sprite s_button_load;
	sf::Sprite s_button_begin;
	
	sf::Texture t_died;
	sf::Sprite s_died;

	sf::Font font;
	sf::Text health;
	sf::Text soul;

	bool restart;
	float begin_x, begin_y;
public:
	//Конмтруктор
	Camera();
	//геттер для отримання камери, спрайтів, та текстів
	sf::Sprite getSprite(int a);
	sf::Text getText(int a);
	sf::View getView();
	bool getRestart();
	//Контроль камери за допомогою миші, клавіатури та кнопки вирівнювання за персонажем
	void keyMove(float time);
	void mouseMove(sf::RenderWindow& window, float time);
	void setCenterCHaracter(Player& player);
	

	//Приімітивне меню
	void begin(sf::RenderWindow& window, sf::Clock& clock, sf::Event& event, Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls);
	void menu(sf::RenderWindow& window, sf::Clock& clock, sf::Event & event, Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls);
	void died(Player& player, sf::RenderWindow& window, sf::Clock& clock);
	void save(Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls);
	void load(Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls);
};