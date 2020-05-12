#include"camera.h"

Camera::Camera()
{
	m_view.reset(sf::FloatRect(0, 0, 1920, 1080));
	//m_view.zoom(4);
}



void Camera::keyMove(float time)
{
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