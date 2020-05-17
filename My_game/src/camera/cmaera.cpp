#define SFML_NO_DEPRECATED_WARNINGS

#include"camera.h"
const std::string c_base_dir = "src/camera/Imges/";
Camera::Camera()
	:restart(false)
{
	m_view.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_view.zoom(0.5);
	t_health.loadFromFile(c_base_dir+"health.png");
	t_soul.loadFromFile(c_base_dir + "soul.png");
	back_ground.loadFromFile(c_base_dir + "back_ground.png");
	button_play.loadFromFile(c_base_dir + "return_icon.png");
	button_exit.loadFromFile(c_base_dir + "exit_icon.png");
	button_restart.loadFromFile(c_base_dir + "restart_icon.png");
	button_load.loadFromFile(c_base_dir + "load_icon.png");
	button_save.loadFromFile(c_base_dir + "save_icon.png");
	button_begin.loadFromFile(c_base_dir + "begin_icon.png");

	back_ground_2.loadFromFile(c_base_dir + "back_gr.png");

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

	s_button_load.setTexture(button_load);
	s_button_load.setTextureRect(sf::IntRect(0, 0, 142, 55));
	s_button_load.setOrigin(142 / 2, 55 / 2);

	s_button_save.setTexture(button_save);
	s_button_save.setTextureRect(sf::IntRect(0, 0, 142, 55));
	s_button_save.setOrigin(142 / 2, 55 / 2);

	s_button_restart.setTexture(button_restart);
	s_button_restart.setTextureRect(sf::IntRect(0, 0, 142, 55));
	s_button_restart.setOrigin(142 / 2, 55 / 2);

	s_button_begin.setTexture(button_begin);
	s_button_begin.setTextureRect(sf::IntRect(0, 0, 142, 55));
	s_button_begin.setOrigin(142 / 2, 55 / 2);

	font.loadFromFile("src/camera/Text/CyrilicOld.TTF");
	health.setFont(font);
	soul.setFont(font);

	t_died.loadFromFile(c_base_dir + "died_icon.png");

	s_died.setTexture(t_died);
	s_died.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	s_died.setOrigin(1920 / 2, 1080 / 2);
	


}


//Контроь камери клавішами
void Camera::keyMove(float time)
{
	s_health.setPosition(m_view.getCenter().x-450, m_view.getCenter().y-250);
	s_soul.setPosition(m_view.getCenter().x+400, m_view.getCenter().y -250);
	//якщо виконуються мови то камера переміщається
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
//Переміщення камери до гравця
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
//геттер для камери
sf::View Camera::getView()
{
	return m_view;
}
//управління камери мишкою
void Camera::mouseMove(sf::RenderWindow& window, float time)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	//при піднессені до країв камера переміщається в ту ж сторону
	if (localPosition.x < 50) { m_view.move(-0.5 * time, 0); }
	if (localPosition.x > window.getSize().x - 50) { m_view.move(0.5 * time, 0); }
	if (localPosition.y > window.getSize().y - 50) { m_view.move(0, 0.5 * time); }
	if (localPosition.y < 50) { m_view.move(0, -0.5 * time); }
}
//геттер для спрайтів та текстів
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

bool Camera::getRestart()
{
	return restart;
}


void Camera::begin(sf::RenderWindow& window, sf::Clock& clock, sf::Event& event, Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls)
{
	s_back_ground.setPosition(m_view.getCenter().x, m_view.getCenter().y);
	s_button_exit.setPosition(m_view.getCenter().x, m_view.getCenter().y + 160);
	s_button_load.setPosition(m_view.getCenter().x, m_view.getCenter().y + 40);

	s_button_begin.setPosition(m_view.getCenter().x, m_view.getCenter().y - 40);

	window.draw(s_back_ground);
	window.draw(s_button_exit);
	window.draw(s_button_begin);
	window.display();

	begin_x = m_view.getCenter().x;
	begin_y = m_view.getCenter().y;
	//нескінчений цикл який зупиняє гру і чекає на виконнання вказанх дій
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
					if (s_button_begin.getGlobalBounds().contains(pos.x, pos.y)) {
						arg = false;

						break;

					}
					if (s_button_exit.getGlobalBounds().contains(pos.x, pos.y)) {
						window.close();
						arg = false;

					}
					
				}
		}

	}
}
//меню
void Camera::menu(sf::RenderWindow& window, sf::Clock & clock, sf::Event& event, Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls)
{//Відрисовка та встановдення потрибних значень кнопок
	s_back_ground.setPosition(m_view.getCenter().x, m_view.getCenter().y);
	s_back_ground_2.setPosition(m_view.getCenter().x, m_view.getCenter().y);
	s_button_exit.setPosition(m_view.getCenter().x, m_view.getCenter().y + 160);
	s_button_play.setPosition(m_view.getCenter().x, m_view.getCenter().y - 80);
	s_button_load.setPosition(m_view.getCenter().x, m_view.getCenter().y + 40);
	s_button_save.setPosition(m_view.getCenter().x, m_view.getCenter().y - 20);
	s_button_restart.setPosition(m_view.getCenter().x, m_view.getCenter().y + 100);

	window.draw(s_back_ground);
	window.draw(s_button_play);
	window.draw(s_button_load);
	window.draw(s_button_save);
	window.draw(s_button_restart);
	window.draw(s_button_exit);
	window.display();
	//нескінчений цикл який зупиняє гру і чекає на виконнання вказанх дій
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

					if (s_button_load.getGlobalBounds().contains(pos.x, pos.y)) {
						load(player, shaphs, enemys, souls);
						arg = false;

					}
					if (s_button_save.getGlobalBounds().contains(pos.x, pos.y)) {
						save(player, shaphs, enemys, souls);
						
					}
					if (s_button_restart.getGlobalBounds().contains(pos.x, pos.y)) {
						m_view.setCenter(begin_x, begin_y);
						restart = true;
						arg = false;

					}
				}
		}
		
	}
		
}
//Меню смерті
void Camera::died(Player& player, sf::RenderWindow& window, sf::Clock& clock)
{
	//Схоже з звичайним але виникає лише при смерті
	if (!player.getlife())
	{
		s_died.setPosition(m_view.getCenter().x, m_view.getCenter().y);
		s_back_ground.setPosition(m_view.getCenter().x, m_view.getCenter().y);
		s_button_exit.setPosition(m_view.getCenter().x, m_view.getCenter().y + 150);
		
		window.draw(s_back_ground);
		window.draw(s_died);
		window.draw(s_button_exit);
		window.display();
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
						if (s_button_restart.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							arg = false;

						}
						if (s_button_load.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							arg = false;

						}
						
					}
			}

			
		}

	}
}

void Camera::save(Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls)
{
	std::ofstream save_data("save.txt");
	
	if(!save_data.is_open())
		std::cout<<"File can not be able to open!!!";

	player >> save_data;

	for (int i = 0; i < shaphs.size(); i++)
		shaphs[i] >> save_data;
	for (int i = 0; i < enemys.size(); i++)
		enemys[i] >> save_data;
	for (int i = 0; i < souls.size(); i++)
		souls[i] >> save_data;
	

	save_data.close();
}
void Camera::load(Player& player, std::array<Let, 15>& shaphs, std::array<Enemy, 4>& enemys, std::array<Neutral, 10>& souls)
{
	std::ifstream load_data("save.txt");

	if (!load_data.is_open())
		std::cout << "File can not be able to open!!!";

	player << load_data;

	for (int i = 0; i < shaphs.size(); i++)
		shaphs[i] << load_data;
	for (int i = 0; i < enemys.size(); i++)
		enemys[i] << load_data;
	for (int i = 0; i < souls.size(); i++)
		souls[i] << load_data;
	m_view.setCenter(player.getX(), player.getY());

	load_data.close();
}
