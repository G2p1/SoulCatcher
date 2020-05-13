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
	, m_isSelect(true)
	, m_h(h)
	, m_w(w)
	, m_health(100)
	, isAttack(true)
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
	
	if (m_health <= 0)
		m_life = false;
	if(!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
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

void Entity::operator-(int damage)
{
	m_health -= damage;
}
//class Player
Player::Player(std::string name, float x, float y, std::string image, int w, int h)
	: m_sword(false)
	, m_bow(false)
	, m_souls(0)
	//,m_Bow(-20000000, -2000000, 400, 25)
	//,m_Sword(x, y , 60, 15)
	, Entity(name, x, y, "src/player/Image/Player/" + image, w , h)
	
{

}

void Player::update(sf::RenderWindow& window, float time, sf::Event& event) 
{
	Entity::update(window, time, event);
	updateEvent(window, event);

	//m_Sword.setCoord(m_x, m_y);
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
				std::cout << "Sword\n";
				m_bow = false;
				m_sword = true;
			}
			
	}


}

void Player::attack(sf::RenderWindow& window, sf::Event& event, Enemy& enemy, Let& let, float time)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

	if (m_isSelect) {
		if (m_bow)
			m_Bow.update(window, event, *this, enemy, time);
		else
			m_Bow.setCoordinates(-2000000, -200000);
		if (m_sword)
			if(isAttack)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				float enemy_distance = sqrt((enemy.getX() - m_x) * (enemy.getX() - m_x) + (enemy.getY() - m_y) * (enemy.getY() - m_y));
				float let_distance = sqrt((let.getX() - m_x) * (let.getX() - m_x) + (let.getY() - m_y) * (let.getY() - m_y));

				if (enemy_distance <= 400)
					enemy - 20;
				if (let_distance <= 400)
					let - 20;
				isAttack = false;
			}
	}
	float timer = clock.getElapsedTime().asSeconds();
	if (timer > 2.5)
	{
		timer = 0;
		clock.restart();
		isAttack = true;
	}
}

void Player::incSouls()
{
	m_souls++;
}

Bow Player::getBow()
{
	return m_Bow;
}

//class Enemy
Enemy::Enemy(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, "src/player/Image/Enemy/" + image, w, h)
	, isDetected (false)

{

}

void Enemy::update(Player& player, float time)
{
	colision(player, isAttack);

	float timer = clock.getElapsedTime().asSeconds();
	if (timer > 5)
	{
		timer = 0;
		clock.restart();
		isAttack = true;
	}
	
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

	if (m_health <= 0)
		m_life = false;
	if (!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
}

void Enemy::colision(Player& player, bool& attack)
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
	{
		player.setCoordinates(player.getX() - 1, player.getY());
		if (attack)
		{
			player - 20;
			attack = false;
		}
	}
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
	{
		player.setCoordinates(player.getX() + 1, player.getY());
		if (attack)
		{
			player - 20;
			attack = false;
		}
	}
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
	{
		player.setCoordinates(player.getX(), player.getY() - 1);
		if (attack)
		{
			player - 20;
			attack = false;
		};
	}
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
	{
		player.setCoordinates(player.getX(), player.getY() + 1);
		if (attack)
		{
			player - 20;
			attack = false;
		}
	}


}
//class Let
Let::Let(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, "src/player/Image/Let/" + image, w, h)

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

	m_sprite.setPosition(m_x, m_y);

	if (m_health < 0)
		m_life = false;
	if (!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
}

//Neutral
Neutral::Neutral(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, "src/player/Image/Neutral/" + image, w, h)
{

}

bool takeIt(Player& player, Neutral* soul)
{
	if (
		player.getX() + (player.getW() / 2) >= soul->getX() - (soul->getW() / 2)
		&&
		(
			(soul->getY() + soul->getH() / 2 < player.getY() + player.getH() && soul->getY() + soul->getH() / 2 > player.getY() - player.getH())
			||
			(soul->getY() - soul->getH() / 2 < player.getY() + player.getH() && soul->getY() - soul->getH() / 2 > player.getY() - player.getH())
			||
			(soul->getY() - soul->getH() < player.getY() - player.getH() && soul->getY() + soul->getH() / 2> player.getY() + player.getH())
			)
		&&
		player.getX() + (player.getW() / 4) <= soul->getX() - (soul->getW() / 2)
		)
	{
		player.incSouls();
		return true;
	}

	else if (
		player.getX() - (player.getW() / 2) <= soul->getX() + (soul->getW() / 2)
		&&
		(
			(soul->getY() + soul->getH() / 2 < player.getY() + player.getH() - 20 && soul->getY() + soul->getH() / 2 > player.getY() - player.getH() + 20)
			||
			(soul->getY() - soul->getH() / 2 < player.getY() + player.getH() - 20 && soul->getY() - soul->getH() / 2 > player.getY() - player.getH() + 20)
			||
			(soul->getY() - soul->getH() < player.getY() - player.getH() && soul->getY() + soul->getH() / 2> player.getY() + player.getH())
			)
		&&
		player.getX() - (player.getW() / 4) >= soul->getX() + (soul->getW() / 2)
		)
	{
		player.incSouls();
		return true;
	}

	else if (
		player.getY() + (player.getH() / 2) >= soul->getY() - (soul->getH() / 2)
		&&
		(
			(soul->getX() + soul->getW() / 2 < player.getX() + player.getW() && soul->getX() + soul->getW() / 2 > player.getX() - player.getW())
			||
			(soul->getX() - soul->getW() / 2 < player.getX() + player.getW() && soul->getX() - soul->getW() / 2 > player.getX() - player.getW())
			||
			(soul->getX() - soul->getW() < player.getX() - player.getW() && soul->getX() + soul->getW() / 2> player.getX() + player.getW())
			)
		&&
		player.getY() + (player.getH() / 4) <= soul->getY() - (soul->getH() / 2)
		)
	{
		player.incSouls();
		return true;
	}
	else if (
		player.getY() - (player.getH() / 2) <= soul->getY() + (soul->getH() / 2)
		&&
		(
			(soul->getX() + soul->getW() / 2 < player.getX() + player.getW() && soul->getX() + soul->getW() / 2 > player.getX() - player.getW())
			||
			(soul->getX() - soul->getW() / 2 < player.getX() + player.getW() && soul->getX() - soul->getW() / 2 > player.getX() - player.getW())
			||
			(soul->getX() - soul->getW() < player.getX() - player.getW() && soul->getX() + soul->getW() / 2> player.getX() + player.getW())
			)
		&&
		player.getY() - (player.getH() / 4) >= soul->getY() + (soul->getH() / 2)
		)
	{
		player.incSouls();
		return true;
	}
	return false;
}
void Neutral::colision(Player& player)
{	
	m_sprite.setPosition(m_x, m_y);

		bool colis = false;
		colis =takeIt(player, this);
		if (colis)
		{
			m_x = -2000000;
			m_y = -2000000;
		}
}


//Bow
Bow::Bow()
	: m_x(-2000000000)
	, m_y(-2000000000)
	, m_damage(30)
	, m_range(500)
	, m_doing(false)
	, m_tempY(0)
	, m_tempX(0)
	, m_acsses(true)
{
	m_image.loadFromFile("src/player/Image/Waepon/bow.png");
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
	m_sprite.setPosition(m_x, m_y);
	m_sprite.setOrigin(20 / 2, 20 / 2);
}

void Bow::update(sf::RenderWindow& window, sf::Event event, Player& player, Enemy& enemy, float time)
{
	if (!m_doing)
	{
		m_x = player.getX();
		m_y = player.getY();
	}


	m_sprite.setPosition(m_x, m_y);

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
	if(m_acsses)
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Left)
		{
			m_doing = true;
			m_tempX = pos.x;
			m_tempY = pos.y;

			float distance = sqrt((m_tempX - m_x) * (m_tempX - m_x) + (m_tempY - m_y) * (m_tempY - m_y));
			m_rangeY = m_y - ((m_y - m_tempY) * m_range / distance);
			m_rangeX = m_x - ((m_x - m_tempX) * m_range / distance);

			m_acsses = false;
		}

	if (m_doing)
	{

		float distance = sqrt((m_rangeX - m_x) * (m_rangeX - m_x) + (m_rangeY - m_y) * (m_rangeY - m_y));

		if (distance > 2)
		{
			m_x += 0.3 * time * (m_rangeX - m_x) / distance;
			m_y += 0.3 * time * (m_rangeY - m_y) / distance;
		}
		else
		{
			m_doing = false;
			m_acsses = true;
		}
	}
	colision(enemy);
}
sf::Sprite Bow::getSprite()
{
	return m_sprite;
}

void Bow::setCoordinates(float x, float y)
{
	m_x = x;
	m_y = y;
	m_sprite.setPosition(m_x, m_y);
}

void Bow::colision(Enemy& enemy)
{
	if (m_x < enemy.getX()+enemy.getW()/2 && m_x > enemy.getX() - enemy.getW() / 2 && m_y < enemy.getY() + enemy.getH() / 2 && m_y > enemy.getY() - enemy.getH() / 2)
	{
		enemy - m_damage;
		m_doing = false;
		m_acsses = true;
	}
}