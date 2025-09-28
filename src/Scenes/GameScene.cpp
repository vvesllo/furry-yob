#include "../../include/Scenes/GameScene.h"

#include "../../include/Entities/Player.h"
#include "../../include/Entities/Enemy.h"
#include "../../include/Entities/Projectile.h"

#include "../../include/Core/MapManager.h"
#include "../../include/Core/InputManager.h"


GameScene::GameScene(std::unique_ptr<sf::RenderWindow>& window)
	: m_window(window)
{
	MapManager::getInstance().newEntity<Player>(sf::Vector2f{ 0, 0 });

	MapManager::getInstance().loadMap("map1");

	m_calm_time = 0;
	m_max_calm_time = 5.f;

	sf::View view{ 
		sf::FloatRect{
			{ 0, 0 }, 
			(sf::Vector2f)m_window->getSize()
		} 
	};

	view.setCenter({0, 0});
	view.zoom(.6f);
	
	m_window->setView(view);
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
	size_t enemy_amount = 0;
	
	for (const auto& entity : MapManager::getInstance().getEntities())
	{
		enemy_amount += (int)(((Entity*)entity.get())->getType() == EntityType::Enemy);
	}
	
	if (enemy_amount == 0)
	{
		if (m_calm_time < 0)
		{
			m_calm_time = m_max_calm_time;
			spawnEnemies();
		}
		m_calm_time -= dt;
	}
	
	MapManager::getInstance().update(dt);
}

void GameScene::draw()
{
	m_window->clear(sf::Color(0x28'4A'5F'FF));

	const std::vector<std::string>& map = MapManager::getInstance().getMap();
	for (size_t i=0; i < map.size(); ++i)
	{
		for (size_t j=0; j < map[i].size(); ++j)
		{
			if (map[i][j] == '0')
			{
				auto& tile = MapManager::getInstance().getTileSprite();
				tile->setPosition(sf::Vector2f{
					(float)(16 * (-(float)MapManager::getInstance().getSize().x / 2.f + j)),
					(float)(16 * (-(float)MapManager::getInstance().getSize().y / 2.f + i)) 
				});
				m_window->draw(*tile);
			}
		}
	}	
	
	MapManager::getInstance().draw(m_window);
    
	m_window->display();
}

void GameScene::spawnEnemies()
{
	MapManager::getInstance().newEntity<Enemy>(sf::Vector2f{ 100,  100 });
	MapManager::getInstance().newEntity<Enemy>(sf::Vector2f{-100,  100 });
	MapManager::getInstance().newEntity<Enemy>(sf::Vector2f{-100, -100 });
	MapManager::getInstance().newEntity<Enemy>(sf::Vector2f{ 100, -100 });
}
