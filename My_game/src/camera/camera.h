#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"
#include"../player/entity.h"
class Camera
{
	sf::View m_view;

public:
	Camera();

	sf::View getView();
	void keyMove(float time);
	void mouseMove(sf::RenderWindow& window, float time);
	void setCenterCHaracter(Player& player);
	void smth();
};