#include "../../include/Scenes/GameScene.h"

#include "../../include/Entities/Player.h"
#include "../../include/Entities/Projectile.h"

#include "../../include/Entities/Enemies/Enemy000.h"
#include "../../include/Entities/Enemies/Enemy001.h"
#include "../../include/Entities/Enemies/Enemy002.h"
#include "../../include/Entities/Enemies/Enemy003.h"

#include "../../include/Core/EntityManager.h"
#include "../../include/Core/LevelManager.h"
#include "../../include/Core/InputManager.h"
#include "../../include/Core/ResourceManager.h"

#include "../../include/Utils/Vector.h"


GameScene::GameScene(std::unique_ptr<sf::RenderWindow>& window)
	: m_window(window)
{
	srand(time(NULL));

	EntityManager::getInstance().newEntity<Player>(sf::Vector2f{ 0, 0 });
	LevelManager::getInstance().load("map1");
	
	m_wave_label = std::make_unique<sf::Text>(
		*ResourceManager::getInstance().getFont("basis33"),
		"", 
		32
	);
	m_wave_label->setPosition(sf::Vector2f(150, 30));
	m_wave_label->setFillColor(sf::Color::Red);


	m_max_calm_time = 5.f;
	m_calm_time = m_max_calm_time;

	m_view = sf::View(sf::FloatRect{
		{ 0, 0 }, 
		(sf::Vector2f)m_window->getSize()
	});
	m_view.setCenter({0, 0});
	m_view.zoom(.6f);
	
	m_wave = 1;
}

GameScene::~GameScene()
{

}

void GameScene::pollEvent(const std::optional<sf::Event>& event)
{
	if (event->is<sf::Event::Closed>())
	{
		m_window->close();
	}
	else if (event->is<sf::Event::MouseMoved>())
	{
		InputManager::getInstance().getMouse().position = m_window->mapPixelToCoords(event->getIf<sf::Event::MouseMoved>()->position);
	}
	else if (event->is<sf::Event::MouseButtonPressed>())
	{
		switch (event->getIf<sf::Event::MouseButtonPressed>()->button)
		{
		case sf::Mouse::Button::Left:	
			InputManager::getInstance().getMouse().left_button = true;
			break;
		case sf::Mouse::Button::Right:
			InputManager::getInstance().getMouse().right_button = true;
			break;
		}
	}
	else if (event->is<sf::Event::MouseButtonReleased>())
	{
		switch (event->getIf<sf::Event::MouseButtonReleased>()->button)
		{
		case sf::Mouse::Button::Left:	
			InputManager::getInstance().getMouse().left_button = false;
			break;
		case sf::Mouse::Button::Right:
			InputManager::getInstance().getMouse().right_button = false;
			break;
		}
	}
}

void GameScene::update(const float& dt)
{
	m_view.setCenter(
		VectorUtils::lerp(
			m_view.getCenter(),
			InputManager::getInstance().getMouse().position / 20.f,
			5.f * dt
		)
	);
	m_window->setView(m_view);
	
	

	size_t enemy_amount = 0;
	
	for (const auto& entity : EntityManager::getInstance().getEntities())
	{
		enemy_amount += (int)(((Entity*)entity.get())->getType() == EntityType::Enemy);
	}
	
	if (enemy_amount == 0)
	{
		if (m_calm_time < 0)
		{
			m_calm_time = m_max_calm_time;
			m_wave_label->setString("wave " + std::to_string(++m_wave));
			m_wave_label->setOrigin(
				m_wave_label->getGlobalBounds().size / 2.f + m_wave_label->getLocalBounds().position
			);
			spawnEnemies();
		}
		m_calm_time -= dt;
	}
	
	EntityManager::getInstance().update(dt);
}

void GameScene::draw()
{
	m_window->clear(sf::Color(0x28'4A'5F'FF));

	LevelManager::getInstance().draw(m_window);
	EntityManager::getInstance().draw(m_window);
    
	m_window->setView(m_window->getDefaultView());
	
	std::unique_ptr<sf::Sprite>& player_icon = LevelManager::getInstance().getPlayerIcon();
	
	// todo: fix this piece of fucking garbage
	player_icon->setColor(sf::Color::Red);
	player_icon->setPosition(sf::Vector2f(150, 100));
	
	m_window->draw(*m_wave_label);
	m_window->draw(*player_icon);
	
	m_window->setView(m_view);

	m_window->display();
}

void GameScene::spawnEnemies()
{
	int points = std::pow(m_wave, 2);

	sf::Vector2f position;

	while (points > 0)
	{
		position = sf::Vector2f{ 
			16 * (12.5f - rand() % 26),
			16 * (12.5f - rand() % 26) 
		};
		if (rand() % 13 == 0)
		{
			EntityManager::getInstance().newEntity<Enemy003>(position);
			points -= 13;
		} 
		else if (rand() % 11 == 0)
		{
			EntityManager::getInstance().newEntity<Enemy002>(position);
			points -= 11;
		} 
		else if (rand() % 5 == 0)
		{
			EntityManager::getInstance().newEntity<Enemy001>(position);
			points -= 5;
		} 
		else
		{
			EntityManager::getInstance().newEntity<Enemy000>(position);
			points -= 1;
		}
	}

	// EntityManager::getInstance().newEntity<Enemy001>(sf::Vector2f{-100,  100 });
	// EntityManager::getInstance().newEntity<Enemy000>(sf::Vector2f{-100, -100 });
	// EntityManager::getInstance().newEntity<Enemy002>(sf::Vector2f{ 100, -100 });
}
