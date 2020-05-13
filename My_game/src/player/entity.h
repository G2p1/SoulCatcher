#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>

class Enemy;
class Let;
class Player;
class Bow
{
	float m_x, m_y;
	float m_tempX, m_tempY;
	float m_rangeX, m_rangeY;
	int m_damage, m_range;
	bool m_doing;
	bool m_acsses;
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	Bow();

	void update(sf::RenderWindow& window, sf::Event event, Player& player, Enemy& enemy, float time);
	sf::Sprite getSprite();
	void setCoordinates(float x, float y);
	void colision(Enemy& enemy);
};


//Interface
class Entity 
{
public:

	std::string m_name;
	int m_health;
	float m_x, m_y;
	float m_w, m_h;
	float m_tempX, m_tempY;
	float m_speed;
	bool m_life;
	bool m_isMove;
	bool m_isSelect;
	bool isAttack;
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Event m_event;
	sf::Clock clock;
	

	Entity(std::string name, float x, float y, std::string image, int w, int h);
	
	void setCoordinates(float x, float y);
	
	float getX();
	float getY();
	float getH();
	float getW();
	sf::Sprite getSprite();

	void update(sf::RenderWindow& window, float time, sf::Event& event);
	void updateEvent(sf::RenderWindow& window, sf::Event& event);
	void operator-(int damage);

};

class Player : public Entity
{
	int m_souls;
	bool m_sword;
	bool m_bow;

	Bow m_Bow;

public:
	

	Player(std::string name, float x, float y, std::string image, int w, int h);

	void update(sf::RenderWindow& window, float time, sf::Event& event);
	void updateEvent(sf::RenderWindow& window, sf::Event& event);
	
	void attack(sf::RenderWindow& window, sf::Event& event, Enemy& enemy, Let& let, float time);
	void incSouls();
	Bow getBow();
};

class Enemy : public Entity
{
	bool isDetected;
	
public: 
	Enemy(std::string name, float x, float y, std::string image, int w, int h);

	void update(Player& player, float time);
	void colision(Player& pleyer, bool& attack);
};

class Let : public Entity
{

public:

	Let(std::string name, float x, float y, std::string image, int w, int h);

	sf::Sprite getSprite();
	void colision(Player& player);
};

class Neutral : public Entity
{
public: 
	Neutral(std::string name, float x, float y, std::string image, int w, int h);
	void colision(Player& player);
	friend bool takeIt(Player& player, Neutral* soul);

};