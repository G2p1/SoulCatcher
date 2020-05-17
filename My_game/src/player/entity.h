#pragma once
#include<fstream>
#include<iostream>
#include <SFML/Graphics.hpp>

class Enemy;
class Let;
class Player;
//Клас Лука
class Bow
{
	float m_x, m_y;
	float m_tempX, m_tempY;
	float m_rangeX, m_rangeY;
	int m_damage, m_range;
	bool m_doing;
	bool m_acsses;
	sf::Image m_image;
	sf::Image m_imageArrow;
	sf::Texture m_texture;
	sf::Texture m_textureArrow;
	sf::Sprite m_sprite;
public:
	//Конструктор
	Bow();
	//Фкнуція яка заьезпечує рух
	void update(sf::RenderWindow& window, sf::Event event, Player& player, Enemy& enemy, float time);
	//геттер для спрайта
	sf::Sprite getSprite();
	//Сеттер для координат
	void setCoordinates(float x, float y);
	//функція яка знаходить перетин між Луком та ворогом
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
	
	//Конструктор
	Entity(std::string name, float x, float y, std::string image, int w, int h);
	//Сеттер для координат
	void setCoordinates(float x, float y);
	//Геттери для координат, розмірів об'єкта та спрайту
	float getX();
	float getY();
	float getH();
	float getW();
	sf::Sprite getSprite();
	//Реалізація перемщення 
	void update(sf::RenderWindow& window, float time, sf::Event& event);
	//Реалізація обробки подій
	void updateEvent(sf::RenderWindow& window, sf::Event& event);
	//перевантаження оператора для віднімання здоров'я
	void operator-(int damage);
	void operator>>(std::ofstream& wright);
	void operator<<(std::ifstream& read);

};

class Player : public Entity
{
	
	int m_souls;
	bool m_sword;
	bool m_bow;
	bool b_trash;
	sf::Clock tik;
	sf::Texture sword;
	sf::Sprite s_sword;
	Bow m_Bow;
	sf::Texture midi_hp;
	sf::Texture low_hp;
	sf::Texture enseyn;
	sf::Texture trash;

public:
	
	//Конмтруктор
	Player(std::string name, float x, float y, std::string image, int w, int h);
	//функція для переміщення
	void update(sf::RenderWindow& window, float time, sf::Event& event);
	//функція для обробки подій
	void updateEvent(sf::RenderWindow& window, sf::Event& event);
	//функція для завдання шкоди ворогу
	void attack(sf::RenderWindow& window, sf::Event& event, Enemy& enemy, float time);
	//функція для завдання шкоди перешкоді
	void attack(sf::RenderWindow& window, sf::Event& event, Let& let, float time);
	//функція для збільшення душ
	void incSouls();
	//Геттери для лука, життя, спрайту леза, кількості луш та здоров'я
	Bow getBow();
	bool getlife();
	sf::Sprite getSword();
	int getSoul();
	int getHealth();
	//Сеттер для вствновлення душ
	void operator>>(std::ofstream& wright);
	void operator<<(std::ifstream& read);

};

class Enemy : public Entity
{
	bool b_trash;
	bool isDetected;
	sf::Texture midi_hp;
	sf::Texture low_hp;
	sf::Texture enseyn;
	sf::Texture trash;

	
public: 
	//Конмтруктори
	Enemy();
	Enemy(std::string name, float x, float y, std::string image, int w, int h);
	//Функція переміщення та детектінга ворогв
	void update(Player& player, float time);
	//Функція виявлення перетину з гравцем та завдання пошкоджень
	void colision(Player& pleyer, bool& attack);
	
};

class Let : public Entity
{

	sf::Texture midi_hp;
	sf::Texture low_hp;
	sf::Texture enseyn;
	sf::Texture trash;
public:
	//Конструктори
	Let();
	Let(std::string name, float x, float y, std::string image, int w, int h);
	//геттер для спрайта
	sf::Sprite getSprite();
	//Визначенняперетину для гравця та ворога, щоб вони не могли пройти
	void colision(Player& player);
	void colision(Enemy& player);
	
	
};

class Neutral : public Entity
{
	bool rander;
public: 
	//Конструктори
	Neutral();
	Neutral(std::string name, float x, float y, std::string image, int w, int h);
	//Функція яка використовує функцію takeIt()
	void colision(Player& player);
	//функція яка виявляє перетин з гравцем тадодає йому душі
	friend bool takeIt(Player& player, Neutral* soul);
	//Функція для реалізації руху
	void update(float times);
	//геттер для життя
	bool getlife();
};