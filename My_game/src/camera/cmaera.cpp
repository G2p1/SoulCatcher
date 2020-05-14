#define SFML_NO_DEPRECATED_WARNINGS

#include"camera.h"

Camera::Camera()
{
	m_view.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_view.zoom(0.5);
	t_health.loadFromFile("src/camera/Imges/health.png");
	t_soul.loadFromFile("src/camera/Imges/soul.png");
	back_ground.loadFromFile("src/camera/Imges/back_ground.png");
	button_play.loadFromFile("src/camera/Imges/return_icon.png");
	button_exit.loadFromFile("src/camera/Imges/exit_icon.png");

	back_ground_2.loadFromFile("src/camera/Imges/back_gr.png");

	s_health.setTexture(t_health);
	s_health.setTextureRect(sf::IntRect(0,0,25,25));
	s_health.setOrigin(12, 12);

	s_soul.setTexture(t_soul);
	s_soul.setTextureRect(sf::IntRect(0, 0, 25, 25));
	s_soul.setOrigin(12, 12);

	s_back_ground.setTexture(back_ground);
	s_back_ground.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	s_back_ground.setOrigin(1920/2, 1080/2);

	s_back_ground_2.setTexture(back_ground_2);
	s_back_ground_2.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	s_back_ground_2.setOrigin(1920 / 2, 1080 / 2);

	s_button_play.setTexture(button_play);
	s_button_play.setTextureRect(sf::IntRect(0, 0, 144, 55));
	s_button_play.setOrigin(144/2, 55/2);

	s_button_exit.setTexture(button_exit);
	s_button_exit.setTextureRect(sf::IntRect(0, 0, 142, 55));
	s_button_exit.setOrigin(142/2, 55/2);

	font.loadFromFile("src/camera/Text/CyrilicOld.TTF");
	health.setFont(font);
	soul.setFont(font);

	t_died.loadFromFile("src/camera/Imges/died_icon.png");

	s_died.setTexture(t_died);
	s_died.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	s_died.setOrigin(1920 / 2, 1080 / 2);
	


}



void Camera::keyMove(float time)
{
	s_health.setPosition(m_view.getCenter().x-450, m_view.getCenter().y-250);
	s_soul.setPosition(m_view.getCenter().x+400, m_view.getCenter().y -250);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_view.move(-0.1* time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		m_view.move(0.1 * time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

		m_view.move( 0, -0.1 * time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

		m_view.move(0, 0.1 * time);
	}
}
void Camera::setCenterCHaracter(Player& player)
{
	std::ostringstream h;
	h << player.getHealth();
	health.setString(h.str());
	health.setPosition(m_view.getCenter().x - 430, m_view.getCenter().y - 270);
	
	std::ostringstream s;
	s << player.getSoul();
	soul.setString(s.str());
	soul.setPosition(m_view.getCenter().x +428, m_view.getCenter().y - 270);

	if(player.getlife())
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		m_view.setCenter(player.getX(), player.getY());
}

sf::View Camera::getView()
{
	return m_view;
}

void Camera::mouseMove(sf::RenderWindow& window, float time)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);

	if (localPosition.x < 50) { m_view.move(-0.5 * time, 0); }
	if (localPosition.x > window.getSize().x - 50) { m_view.move(0.5 * time, 0); }
	if (localPosition.y > window.getSize().y - 50) { m_view.move(0, 0.5 * time); }
	if (localPosition.y < 50) { m_view.move(0, -0.5 * time); }
}

sf::Sprite Camera::getSprite(int a)
{
	if (a == 1)
		return s_health;
	if (a == 0)
		return s_soul;
}
sf::Text Camera::getText(int a)
{
	if (a == 1)
		return health;
	if (a == 0)
		return soul;
}

void Camera::menu(sf::RenderWindow& window, sf::Clock & clock, sf::Event& event)
{
	
	bool arg = true;
	while (arg)
	{
		clock.restart();
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
				{
					if (s_button_play.getGlobalBounds().contains(pos.x, pos.y)) {
						arg = false;
						break;

					}
					if (s_button_exit.getGlobalBounds().contains(pos.x, pos.y)) {
						window.close();
						arg = false;

					}
				}
		}
		s_back_ground.setPosition(m_view.getCenter().x, m_view.getCenter().y);
		s_back_ground_2.setPosition(m_view.getCenter().x, m_view.getCenter().y);
		s_button_exit.setPosition(m_view.getCenter().x, m_view.getCenter().y + 40);
		s_button_play.setPosition(m_view.getCenter().x, m_view.getCenter().y - 40);
		
		window.draw(s_back_ground_2);
		window.draw(s_back_ground);
		window.draw(s_button_play);
		window.draw(s_button_exit);
		window.display();
	}
}

void Camera::died(Player& player, sf::RenderWindow& window, sf::Clock& clock)
{

	if (!player.getlife())
	{
		bool arg = true;
		while (arg)
		{
			clock.restart();
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
					{

						if (s_button_exit.getGlobalBounds().contains(pos.x, pos.y))
						{
							window.close();
							arg = false;
						}
						
					}
			}

			s_died.setPosition(m_view.getCenter().x, m_view.getCenter().y);
			s_back_ground_2.setPosition(m_view.getCenter().x, m_view.getCenter().y);
			s_button_exit.setPosition(m_view.getCenter().x, m_view.getCenter().y + 150);
			window.clear();
			window.draw(s_back_ground_2);
			window.draw(s_died);
			window.draw(s_button_exit);
			window.display();
		}

	}
}