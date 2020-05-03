#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "waepon/waepon.h"

//Interface
class Entity 
{
public:

	std::string m_name;
	float m_x, m_y;
	float m_tempX, m_tempY;
	float m_speed;
	bool m_life;
	bool m_isMove;
	bool m_isSelect;
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Event m_event;
	float m_w, m_h;

	Entity(std::string name, float x, float y, std::string image, int w, int h);
	
	void setCoordinates(float x, float y);
	
	float getX();
	float getY();
	sf::Sprite getSprite();

	void update(sf::RenderWindow& window, float time, sf::Event& event);
	void updateEvent(sf::RenderWindow& window, sf::Event& event);

};

class Player : public Entity
{
	bool m_sword;
	bool m_bow;

	Bow m_Bow;
	Sword m_Sword;

public:

	Player(std::string name, float x, float y, std::string image, int w, int h);

	void update(sf::RenderWindow& window, float time, sf::Event& event);
	void updateEvent(sf::RenderWindow& window, sf::Event& event);
	void attack();
};

class Enemy : public Entity
{
	bool isDetected;

public: 
	Enemy(std::string name, float x, float y, std::string image, int w, int h);

	void update(Player& player, float time);

};

class Let : public Entity
{
	float m_strength;

public:

	Let(std::string name, float x, float y, std::string image, int w, int h);
};