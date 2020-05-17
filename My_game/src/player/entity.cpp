#include"time.h"
#include<stdio.h>
#include<cstdlib>
#include"entity.h"
const std::string p_base_dir = "src/player/Image/Player/";
const std::string e_base_dir = "src/player/Image/Enemy/";
const std::string l_base_dir = "src/player/Image/Let/";
const std::string n_base_dir = "src/player/Image/Neutral/";
const std::string w_base_dir = "src/player/Image/Waepon/";


////Конструктор
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
	, m_health(100)
	, isAttack(true)
{
	if (h > 0)
		m_h = h;
	else
		m_h = 0;
	if (w > 0)
		m_w = w;
	else
		m_w = 0;
	m_image.loadFromFile(image);
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_w, m_h));
	m_sprite.setPosition(m_x, m_y);
	m_sprite.setOrigin(m_w / 2, m_h / 2);
	
}
//Сеттер для координат
void Entity::setCoordinates(float x, float y) 
{
	m_x = x;
	m_y = y;
}


//Геттери для координат, розмірів об'єкта та спрайту
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
float Entity::getW()
{
	return m_w;
}

float Entity::getH()
{
	return m_h;
}

void Entity::operator>>(std::ofstream& wright)
{
	wright << m_health << " ";
	wright << m_x << " ";
	wright << m_y << " ";

}
void Entity::operator<<(std::ifstream& read)
{
	read >> this->m_health;
	read >> this->m_x;
	read >> this->m_y;
	m_isMove = false;
}
//Реалізація перемщення 
void Entity::update(sf::RenderWindow& window, float time, sf::Event& event)
{
	float distance = 0;
	
	Entity::updateEvent(window, event);
	if (m_isMove)
	{//Розрахунок дистанції та реалізація руху
		distance = sqrt((m_tempX - m_x) * (m_tempX - m_x) + (m_tempY - m_y) * (m_tempY - m_y));

			if (distance > 2)
			{
				m_x += 0.15*time  * (m_tempX - m_x) / distance;
				m_y += 0.15 *time * (m_tempY - m_y) / distance;
			}
	}

	m_sprite.setPosition(m_x, m_y);
	
	
}
//Реалізація обробки подій
void Entity::updateEvent(sf::RenderWindow& window, sf::Event& event)
{
	//запис позиції курсора в контейнери
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
	//обробка подій
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


//перевантаження оператора для віднімання здоров'я
void Entity::operator-(int damage)
{
	m_health -= damage;
}

//class Player
//Конмтруктор
Player::Player(std::string name, float x, float y, std::string image, int w, int h)
	: m_sword(false)
	, m_bow(false)
	, m_souls(0)
	, Entity(name, x, y, p_base_dir + image, w , h)
	
{
	sword.loadFromFile(p_base_dir + "player.png");
	s_sword.setTexture(sword);
	s_sword.setTextureRect(sf::IntRect(0, 0, 100, 100));
	s_sword.setOrigin(50, 50);
	s_sword.setPosition(-2000000, -200000);
	midi_hp.loadFromFile(p_base_dir + "player_2.png");
	low_hp.loadFromFile(p_base_dir+"player_3.png");
	enseyn.loadFromFile(p_base_dir+"player_4.png");
	trash.loadFromFile(p_base_dir+"player_5.png");
}
//функція для переміщення
void Player::update(sf::RenderWindow& window, float time, sf::Event& event) 
{

	//перевірка чи може гравець рухатися
	if(b_trash)
	Entity::update(window, time, event);
	updateEvent(window, event);
	//таймер для рисування тестури леза
	float timer = tik.getElapsedTime().asSeconds();
	if (timer > 0.2) 
	{
		s_sword.setPosition(-2000, -2000);
		tik.restart();
	}
	//відображення спрайта в залежності в який бік йде гравець
	if(m_tempX>m_x)
		m_sprite.setScale(1, 1);
	if(m_tempX < m_x)
		m_sprite.setScale(-1, 1);
	//Зміна текстур в залежності в здоров'я
	if (m_health <= 100)
		m_sprite.setTexture(m_texture);
	if (m_health <= 80)
		m_sprite.setTexture(midi_hp);
	if (m_health <= 60)
		m_sprite.setTexture(low_hp);
	if (m_health <= 40)
		m_sprite.setTexture(enseyn);
	if (m_health <= 20)
	{
		b_trash = false;
		m_sprite.setTexture(trash);
	}
	//Зникнення гравця при смерті
	if (m_health <= 0)
		m_life = false;
	if (!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
}
//функція для обробки подій
void Player::updateEvent(sf::RenderWindow& window, sf::Event& event)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_w / 2, m_h / 2);
	m_sprite.setPosition(m_x, m_y);
	//обробка клавіш а саме вибір зброї
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
//функція для завдання шкоди ворогу
void Player::attack(sf::RenderWindow& window, sf::Event& event, Enemy& enemy, float time)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
	//Реалізація атаки
	if (m_isSelect) {
		if (m_bow)
			m_Bow.update(window, event, *this, enemy, time);
		else
			m_Bow.setCoordinates(-2000000, -200000);
		if (m_sword)
			if(isAttack)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				float enemy_distance = sqrt((enemy.getX() - m_x) * (enemy.getX() - m_x) + (enemy.getY() - m_y) * (enemy.getY() - m_y));


				

				s_sword.setPosition(m_x, m_y);
				if (enemy_distance- enemy.getH()/2 <= 100)
					enemy - 20;
				
			}

		//s_sword.setPosition(-2000000, -200000);
			
	}
	
}
//функція для завдання шкоди перешкоді
void Player::attack(sf::RenderWindow& window, sf::Event& event, Let& let, float time)
{
	
		if (m_sword)
			if (isAttack)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					
					float let_distance = sqrt((let.getX() - m_x) * (let.getX() - m_x) + (let.getY() - m_y) * (let.getY() - m_y));
					if (let_distance - let.getH() / 2 <= 100)
						let - 20;
				}
	
	
}
//функція для збільшення душ
void Player::incSouls()
{
	m_souls++;
}
//Геттери для лука, життя, спрайту леза, кількості луш та здоров'я
sf::Sprite Player::getSword()
{
	return s_sword;
}



Bow Player::getBow()
{
	return m_Bow;
}

bool Player::getlife()
{
	return m_life;
}

int Player::getSoul()
{
	return m_souls;
}
int Player::getHealth()
{
	return m_health;
}


void Player::operator>>(std::ofstream& wright)
{
	wright << m_health << " ";
	wright << m_x << " ";
	wright << m_y << " ";
	wright << m_souls << " ";
}
void Player::operator<<(std::ifstream& read)
{
	read >> m_health ;
	read >> m_x;
	read >> m_y ;
	int tmp;
	read >> tmp;
	if (tmp >= 0)
		m_souls = tmp;
	else
		m_souls = 0;
	m_isMove = false;
}
//class Enemy
//Конмтруктори
Enemy::Enemy()
	: Entity("enemy", 800, 350, e_base_dir + "enemy_1.png", 107, 74)
	, b_trash(true)
{
	midi_hp.loadFromFile(e_base_dir+"enemy_2.png");
	low_hp.loadFromFile(e_base_dir+"enemy_3.png");
	enseyn.loadFromFile(e_base_dir+"enemy_4.png");
	trash.loadFromFile(e_base_dir+"enemy_5.png");
}

Enemy::Enemy(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, e_base_dir + image, w, h)
	, isDetected (false)

{

}
//Функція переміщення та детектінга ворогв
void Enemy::update(Player& player, float time)
{
	
	colision(player, isAttack);
	//інтервал атаки ворога
	float timer = clock.getElapsedTime().asSeconds();
	if (timer > 3)
	{
		timer = 0;
		clock.restart();
		isAttack = true;
	}
	
	m_tempX = player.getX();
	m_tempY = player.getY();
	//Змна тестури в залежності від здоров'я
	if (m_health <= 100)
		m_sprite.setTexture(m_texture);
	if (m_health <= 80)
		m_sprite.setTexture(midi_hp);
	if (m_health <= 60)
		m_sprite.setTexture(low_hp);
	if (m_health <= 40)
		m_sprite.setTexture(enseyn);
	if (m_health <= 20)
	{
		b_trash = false;
		m_sprite.setTexture(trash);
	}
	else
	b_trash = true;
	//реалізація руху
	if (b_trash)
	{
		float distance = sqrt((player.getX() - m_x) * (player.getX() - m_x) + (player.getY() - m_y) * (player.getY() - m_y));
		if (distance < 300)
		{
			isDetected = true;
			m_x += 0.05 * time * (m_tempX - m_x) / distance;
			m_y += 0.05 * time * (m_tempY - m_y) / distance;
		}
		if (m_tempX > m_x)
			m_sprite.setScale(-1, 1);
		if (m_tempX < m_x)
			m_sprite.setScale(1, 1);
	}

	m_sprite.setPosition(m_x, m_y);
	//зникнення з карти при смерті
	if (m_health <= 0)
		m_life = false;
	else
		m_life = true;
	if (!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
}
//Функція виявлення перетину з гравцем та завдання пошкоджень
void Enemy::colision(Player& player, bool& attack)
{//Умови для знаходження колізій
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
//Конструктори
Let::Let() 
	:Entity("tree", 500, 500, l_base_dir+"shkaph.png", 44, 69)
{
	midi_hp.loadFromFile(l_base_dir + "shkaph_2.png");
	low_hp.loadFromFile(l_base_dir + "shkaph_3.png");
	enseyn.loadFromFile(l_base_dir + "shkaph_4.png");
	trash.loadFromFile(l_base_dir + "shkaph_5.png");
}

Let::Let(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, l_base_dir  + image, w, h)

{

}
//геттер для спрайта
sf::Sprite Let::getSprite()
{
	return m_sprite;
}
//Визначенняперетину для гравця та ворога, щоб вони не могли пройти
void Let::colision(Player& player)
{//змана текстури в залежності від здоров'я
	if (m_health <= 100)
		m_sprite.setTexture(m_texture);
	if (m_health <= 80)
		m_sprite.setTexture(midi_hp);
	if (m_health <= 60)
		m_sprite.setTexture(low_hp);
	if (m_health <= 40)
		m_sprite.setTexture(enseyn);
	if (m_health <= 20)
		m_sprite.setTexture(trash);
	//реалізація колізій як в клвсі ворога
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
	//зникнення при руйнуванні
	if (m_health <= 0)
		m_life = false;
	else
		m_life = true;
	if (!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
}

//Визначенняперетину для гравця та ворога, щоб вони не могли пройти
void Let::colision(Enemy& player)
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
	else
		m_life = true;
	if (!m_life)
	{
		m_x = -2000000;
		m_y = -2000000;
	}
}
//Neutral
//Конструктори
Neutral::Neutral()
	:Entity("soul", 500, 500, n_base_dir+"soul.png", 30, 29)
{

}
Neutral::Neutral(std::string name, float x, float y, std::string image, int w, int h)
	: Entity(name, x, y, n_base_dir + image, w, h)
	, rander(true)
{

	srand(time(0));
}
//Функція для реалізації руху
void Neutral::update(float times)
{	
	float timer = clock.getElapsedTime().asSeconds();
	//генераія випадкового напрямку руху
	if (rander)
	{
		m_tempX = rand()%(40*31);
		m_tempY = rand() % (46*31);
		//std::cout << m_tempX << " " << m_tempY << "\n";
			rander = false;
			m_isMove = true;
	}
	if (timer > 2)
	{
		timer = 0;
		clock.restart();
		rander = true;
		
	}
		float distance = 0;
	if (m_isMove)
	{//реалізація руху
		distance = sqrt((m_tempX - m_x) * (m_tempX - m_x) + (m_tempY - m_y) * (m_tempY - m_y));

		if (distance > 2)
		{
			m_x += 0.1 * times * (m_tempX - m_x) / distance;
			m_y += 0.1 * times * (m_tempY - m_y) / distance;
		}
		else
			m_isMove = false;
	}
}
//функція яка виявляє перетин з гравцем тадодає йому душі
bool takeIt(Player& player, Neutral* soul)
{//Реалізація підбору
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
			(soul->getX() + soul->getW() / 2 < player.getX() + player.getW()/2 && soul->getX() + soul->getW() / 2 > player.getX() - player.getW()/2)
			||
			(soul->getX() - soul->getW() / 2 < player.getX() + player.getW()/2 && soul->getX() - soul->getW() / 2 > player.getX() - player.getW()/2)
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
//Функція яка використовує функцію takeIt()
void Neutral::colision(Player& player)
{	
	m_sprite.setPosition(m_x, m_y);
	//зникнення після того як підібрали
		bool colis = false;
		colis =takeIt(player, this);
		if (colis)
		{
			m_x = -2000000;
			m_y = -2000000;
			m_life = false;
		}
}
//геттер для життя
bool Neutral::getlife()
{
	return m_life;
}

//Bow
//Конструктор
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
	m_image.loadFromFile(w_base_dir+ "bow.png");
	m_imageArrow.loadFromFile(w_base_dir + "arrow_1.png");
	m_texture.loadFromImage(m_image);
	m_textureArrow.loadFromImage(m_imageArrow);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 31, 30));
	m_sprite.setPosition(m_x, m_y);
	m_sprite.setOrigin(31 / 2, 30 / 2);
}
//Фкнуція яка заьезпечує рух
void Bow::update(sf::RenderWindow& window, sf::Event event, Player& player, Enemy& enemy, float time)
{//повернення спрайту до гравця після того як влучив чи пролетів значену дальність
	if (!m_doing)
	{
		m_x = player.getX()+30;
		m_y = player.getY();
		m_sprite.setTexture(m_texture);
	}


	m_sprite.setPosition(m_x, m_y);
	//реалізація стрільби
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
	if(m_acsses)
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Left)
		{
			m_sprite.setTexture(m_textureArrow);
			m_sprite.setTextureRect(sf::IntRect(0, 0, 31, 30));
			m_sprite.setPosition(m_x, m_y);
			m_sprite.setOrigin(31 / 2, 30 / 2);
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
			m_x += 0.1 * time * (m_rangeX - m_x) / distance;
			m_y += 0.1 * time * (m_rangeY - m_y) / distance;
		}
		else
		{
			m_doing = false;
			m_acsses = true;
		}
	}
	colision(enemy);
}
//геттер для спрайта
sf::Sprite Bow::getSprite()
{
	return m_sprite;
}
//Сеттер для координат
void Bow::setCoordinates(float x, float y)
{
	m_x = x;
	m_y = y;
	m_sprite.setPosition(m_x, m_y);
}
//функція яка знаходить перетин між Луком та ворогом
void Bow::colision(Enemy& enemy)
{//колізії з ворогом
	if (m_x < enemy.getX()+enemy.getW()/2 && m_x > enemy.getX() - enemy.getW() / 2 && m_y < enemy.getY() + enemy.getH() / 2 && m_y > enemy.getY() - enemy.getH() / 2)
	{
		enemy - m_damage;
		m_doing = false;
		m_acsses = true;
	}
}