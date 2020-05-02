#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

//Interface
class Entity 
{
public:

	std::string m_name;
	float m_x, m_y;
	float m_dx, m_dy;
	float m_speed;
	bool life;
	bool isMove;
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float m_w, m_h;

	Entity(std::string name, float x, float y, std::string image, int w, int h);
	
	void setCoordinates(float x, float y);
	
	float getX();
	float getY();

	void update();
	void eventUpdate();

};

class Player : public Entity
{
	bool sword;
	bool bow;

private:

	Player(std::string name, float x, float y, std::string image, int w, int h);

};

class Enemy : public Entity
{
	bool isDetected;

public: 
	Enemy(std::string name, float x, float y, std::string image, int w, int h);

	void update();

};

class Let : public Entity
{
	float m_strength;

public:

	Let(std::string name, float x, float y, std::string image, int w, int h);
};