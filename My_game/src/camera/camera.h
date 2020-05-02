#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"

class Camera
{
	sf::View m_view;

public:
	Camera(float x, float y);

	void update(float x, float y);

};