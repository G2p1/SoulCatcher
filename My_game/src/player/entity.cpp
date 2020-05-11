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
	
	Entity::updateEvent(window, event);
	if (m_isMove)
	{
		distance = sqrt((m_tempX - m_x) * (m_tempX - m_x) + (m_tempY - m_y) * (m_tempY - m_y));

			if (distance > 2)
			{
				m_x += 0.3*time  * (m_tempX - m_x) / distance;
				m_y += 0.3 *time * (m_tempY - m_y) / distance;
			}
	}

	m_sprite.setPosition(m_x, m_y);

}

void Entity::updateEvent(sf::RenderWindow& window, sf::Event& event)
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
	}
}

float Entity::getW()
{
	return m_w;
}

float Entity::getH()
{
	return m_h;
}
//class Player
Player::Player(std::string name, float x, float y, std::string image, int w, int h)
	: m_sword(false)
	, m_bow(false)
	, m_souls(0)
	, Entity(name, x, y, "src/player/Image/Player/" + image, w , h)
	
	
{

}

void Player::update(sf::RenderWindow& window, float time, sf::Event& event) 
{
	Entity::update(window, time, event);
	updateEvent(window, event);
}

void Player::updateEvent(sf::RenderWindow& window, sf::Event& event)
{
	
	if (m_life) {
		
			if (event.key.code == sf::Keyboard::Q)
			{
				m_bow = true;
				m_sword = false;
			}

			if (event.key.code == sf::Keyboard::W)
			{
				m_bow = false;
				m_sword = true;
			}

	}
}

void Player::attack()
{
	if (m_bow)
	{

	}
	if (m_sword)
	{

	}
}

void Player::incSouls()
{
	m_souls++;
}

//class Enemy
Enemy::Enemy(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, "src/player/Image/Enemy/" + image, w, h)
	, isDetected (false)

{

}

void Enemy::update(Player& player,float time)
{
	colision(player);
	m_tempX = player.getX();
	m_tempY = player.getY();
	float distance = sqrt((player.getX() - m_x)* (player.getX() - m_x) + (player.getY() - m_y)* (player.getY() - m_y));
	if (distance < 1000)
	{
		isDetected = true;
		m_x += 0.05 * time * (m_tempX - m_x) / distance;
		m_y += 0.05 * time * (m_tempY - m_y) / distance;
	}

	m_sprite.setPosition(m_x, m_y);
}

void Enemy::colision(Player& player)
{
	if (
		player.getX() + (player.getW() / 2) >= m_x - (m_w / 2)
		&&
		(
			(m_y + m_h / 2 < player.getY() + player.getH() && m_y + m_h / 2 > player.getY() - player.getH())
			||
			(m_y - m_h / 2 < player.getY() + player.getH() && m_y - m_h / 2 > player.getY() - player.getH())
			||
			(m_y - m_h< player.getY() - player.getH() && m_y + m_h / 2> player.getY() + player.getH())
			)
		&&
		player.getX() + (player.getW() / 4) <= m_x - (m_w / 2)
		)
		player.setCoordinates(
								 player.getX() - 1
								, player.getY()
								);

	else if (
		player.getX() - (player.getW() / 2)  <= m_x + (m_w / 2)
		&&
		(
			(m_y + m_h / 2  < player.getY() + player.getH()-20 && m_y + m_h / 2 > player.getY() - player.getH()+20)
			||
			(m_y - m_h / 2  < player.getY() + player.getH()-20 && m_y - m_h / 2 > player.getY() - player.getH()+20)
			||
			(m_y - m_h< player.getY() - player.getH() && m_y + m_h / 2> player.getY() + player.getH())
			)
		&&
		player.getX() - (player.getW() / 4) >= m_x + (m_w / 2) 
		)
		player.setCoordinates(
			player.getX() + 1
			, player.getY()
		);

	else if (
		player.getY() + (player.getH() / 2)   >= m_y - (m_h / 2)
		&&
		(
			(m_x + m_w / 2 < player.getX() + player.getW()  && m_x + m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w / 2 < player.getX() + player.getW()  && m_x - m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w< player.getX() - player.getW() && m_x + m_w / 2> player.getX() + player.getW())
			)
		&&
		player.getY() + (player.getH() / 4) <= m_y - (m_h / 2) 
		)
		player.setCoordinates(
			player.getX() 
			, player.getY() - 1
		);
	else if (
		player.getY() - (player.getH() / 2)  <= m_y + (m_h / 2)
		&&
		(
			(m_x + m_w / 2 < player.getX() + player.getW() && m_x + m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w / 2 < player.getX() + player.getW() && m_x - m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w< player.getX() - player.getW() && m_x + m_w / 2> player.getX() + player.getW())
			)
		&&
		player.getY() - (player.getH() / 4) >= m_y + (m_h / 2)
		)
		player.setCoordinates(
			player.getX()
			, player.getY() + 1
		);



}
//class Let
Let::Let(std::string name, float x, float y, std::string image, int w, int h)
	: m_strength(100)
	, Entity(name, x, y, "src/player/Image/Let/" + image, w, h)

{

}

sf::Sprite Let::getSprite()
{
	return m_sprite;
}
void Let::colision(Player& player)
{
	if (
		player.getX() + (player.getW() / 2) >= m_x - (m_w / 2)
		&&
		(
			(m_y + m_h / 2 < player.getY() + player.getH() && m_y + m_h / 2 > player.getY() - player.getH())
			||
			(m_y - m_h / 2 < player.getY() + player.getH() && m_y - m_h / 2 > player.getY() - player.getH())
			||
			(m_y - m_h< player.getY() - player.getH() && m_y + m_h / 2> player.getY() + player.getH())
			)
		&&
		player.getX() + (player.getW() / 4) <= m_x - (m_w / 2)
		)
		player.setCoordinates(
			player.getX() - 1
			, player.getY()
		);

	else if (
		player.getX() - (player.getW() / 2) <= m_x + (m_w / 2)
		&&
		(
			(m_y + m_h / 2 < player.getY() + player.getH() - 20 && m_y + m_h / 2 > player.getY() - player.getH() + 20)
			||
			(m_y - m_h / 2 < player.getY() + player.getH() - 20 && m_y - m_h / 2 > player.getY() - player.getH() + 20)
			||
			(m_y - m_h< player.getY() - player.getH() && m_y + m_h / 2> player.getY() + player.getH())
			)
		&&
		player.getX() - (player.getW() / 4) >= m_x + (m_w / 2)
		)
		player.setCoordinates(
			player.getX() + 1
			, player.getY()
		);

	else if (
		player.getY() + (player.getH() / 2) >= m_y - (m_h / 2)
		&&
		(
			(m_x + m_w / 2 < player.getX() + player.getW() && m_x + m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w / 2 < player.getX() + player.getW() && m_x - m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w< player.getX() - player.getW() && m_x + m_w / 2> player.getX() + player.getW())
			)
		&&
		player.getY() + (player.getH() / 4) <= m_y - (m_h / 2)
		)
		player.setCoordinates(
			player.getX()
			, player.getY() - 1
		);
	else if (
		player.getY() - (player.getH() / 2) <= m_y + (m_h / 2)
		&&
		(
			(m_x + m_w / 2 < player.getX() + player.getW() && m_x + m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w / 2 < player.getX() + player.getW() && m_x - m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w< player.getX() - player.getW() && m_x + m_w / 2> player.getX() + player.getW())
			)
		&&
		player.getY() - (player.getH() / 4) >= m_y + (m_h / 2)
		)
		player.setCoordinates(
			player.getX()
			, player.getY() + 1
		);

}

Neutral::Neutral(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, "src/player/Image/Neutral/" + image, w, h)
{

}

void Neutral::takeIt(Player& player)
{
	if (
		player.getX() + (player.getW() / 2) >= m_x - (m_w / 2)
		&&
		(
			(m_y + m_h / 2 < player.getY() + player.getH() && m_y + m_h / 2 > player.getY() - player.getH())
			||
			(m_y - m_h / 2 < player.getY() + player.getH() && m_y - m_h / 2 > player.getY() - player.getH())
			||
			(m_y - m_h< player.getY() - player.getH() && m_y + m_h / 2> player.getY() + player.getH())
			)
		&&
		player.getX() + (player.getW() / 4) <= m_x - (m_w / 2)
		)
		player.incSouls();

	else if (
		player.getX() - (player.getW() / 2) <= m_x + (m_w / 2)
		&&
		(
			(m_y + m_h / 2 < player.getY() + player.getH() - 20 && m_y + m_h / 2 > player.getY() - player.getH() + 20)
			||
			(m_y - m_h / 2 < player.getY() + player.getH() - 20 && m_y - m_h / 2 > player.getY() - player.getH() + 20)
			||
			(m_y - m_h< player.getY() - player.getH() && m_y + m_h / 2> player.getY() + player.getH())
			)
		&&
		player.getX() - (player.getW() / 4) >= m_x + (m_w / 2)
		)
		player.incSouls();

	else if (
		player.getY() + (player.getH() / 2) >= m_y - (m_h / 2)
		&&
		(
			(m_x + m_w / 2 < player.getX() + player.getW() && m_x + m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w / 2 < player.getX() + player.getW() && m_x - m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w< player.getX() - player.getW() && m_x + m_w / 2> player.getX() + player.getW())
			)
		&&
		player.getY() + (player.getH() / 4) <= m_y - (m_h / 2)
		)
		player.incSouls();
	else if (
		player.getY() - (player.getH() / 2) <= m_y + (m_h / 2)
		&&
		(
			(m_x + m_w / 2 < player.getX() + player.getW() && m_x + m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w / 2 < player.getX() + player.getW() && m_x - m_w / 2 > player.getX() - player.getW())
			||
			(m_x - m_w< player.getX() - player.getW() && m_x + m_w / 2> player.getX() + player.getW())
			)
		&&
		player.getY() - (player.getH() / 4) >= m_y + (m_h / 2)
		)
		player.incSouls();
}