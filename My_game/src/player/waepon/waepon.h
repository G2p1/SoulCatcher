#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

class Waepon 
{
public:
	float m_x, m_y;
	int m_damage;
	int m_range;

	Waepon(float x, float y, int range, int damage);
};

class Bow: public Waepon
{
	
public:
	Bow();
	Bow(float x, float y, int range, int damage);

};

class Sword : public Waepon
{
public:
	Sword();
	Sword(float x, float y, int range, int damage);
	
};