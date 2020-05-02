#include"entity.h"

//class Entity 
Entity::Entity(std::string name, float x, float y, std::string image, int w, int h)
	: m_name(name)
	, m_x(x)
	, m_y(y)
	, m_dx (0)
	, m_dy (0)
	, m_speed (0)
	, life (true)
	, isMove (false)
	, m_h (h)
	, m_w (w)

{
	m_image.loadFromFile("Image/" + image);
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
}

void Entity::setCoordinates(float x, float y) 
{
	m_x = x;
	m_y = y;
}

float Entity::getX()
{
	return m_x;
}

float Entity::getY()
{
	return m_y;
}

void Entity::update()
{

}

void Entity::eventUpdate()
{

}

//class Player
Player::Player(std::string name, float x, float y, std::string image, int w, int h)
	: sword(false)
	, bow(false)
	, Entity(name, x, y, image, w , h)
	
{

}

//class Enemy
Enemy::Enemy(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, image, w, h)
	, isDetected (false)

{

}

void Enemy::update() 
{

}

//class Let
Let::Let(std::string name, float x, float y, std::string image, int w, int h)
	: m_strength(100)
	, Entity(name, x, y, image, w, h)

{

}