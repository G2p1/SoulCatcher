#include"entity.h"

//class Entity 
Entity::Entity(std::string name, float x, float y, std::string image, int w, int h)
	: m_name(name)
	, m_x(x)
	, m_y(y)
	, m_tempX(0)
	, m_tempY(0)
	, m_speed(0)
	, m_life(true)
	, m_isMove(false)
	, m_isSelect(false)
	, m_h(h)
	, m_w(w)

{
	m_image.loadFromFile(image);
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_w, m_h));
	m_sprite.setPosition(m_x, m_y);
	m_sprite.setOrigin(m_w / 2, m_h / 2);
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

sf::Sprite Entity::getSprite() 
{
	return m_sprite;
}

void Entity::update(sf::RenderWindow& window, float time, sf::Event& event)
{
	float distance = 0;
	
	Entity::eventUpdate(window, event);
	if (m_isMove)
	{
		distance = sqrt((m_tempX - m_x) * (m_tempX - m_x) + (m_tempY - m_y) * (m_tempY - m_y));

			if (distance > 2)
			{
				m_x += 0.1*time  * (m_tempX - m_x) / distance;
				m_y += 0.1 *time * (m_tempY - m_y) / distance;
			}
	}

	m_sprite.setPosition(m_x, m_y);

}

void Entity::eventUpdate(sf::RenderWindow& window, sf::Event& event)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
	
	if (m_life) 
	{	
		
		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::F1)
			{
				m_isSelect = true;
			}
		
			
		}
		if(event.type == sf::Event::MouseButtonPressed)
			if(event.key.code == sf::Mouse::Left)
				if (m_sprite.getGlobalBounds().contains(pos.x, pos.y))
				{
					m_isSelect = true;
				}
				else
				{
					m_isSelect = false;
				}

		

		if(m_isSelect)
			if(event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Right)
				{
					m_isMove = true;
					m_tempX = pos.x;
					m_tempY = pos.y;
				}

		if (event.key.code == sf::Keyboard::S)
		{
			m_isMove = false;
		}
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Q)
			{
				std::cout << "bow\n";
				m_bow = true;
				m_sword = false;
			}

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::W)
			{
				std::cout << "sword\n";
				m_bow = false;
				m_sword = true;
			}

	}
}

//class Player
Player::Player(std::string name, float x, float y, std::string image, int w, int h)
	: m_sword(false)
	, m_bow(false)
	, Entity(name, x, y, "src/player/Image/Player/" + image, w , h)
	
{

}

void Player::update(sf::RenderWindow& window, float time, sf::Event& event) 
{
	Entity::update(window, time, event);
	updateEvent(event);
}

void Player::updateEvent(sf::Event & event) {
	if (m_life) {
		
		
	}
}

//class Enemy
Enemy::Enemy(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, "src/player/Image/Enemy/" + image, w, h)
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