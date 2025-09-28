#include "../include/App.h"
#include "../include/App.h"
#include "../include/Core/SceneManager.h"
#include "../include/Scenes/GameScene.h"

#include <print>

App::App(const unsigned short& width, const unsigned short& height, const char* title)
{
    m_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode({width, height}),
        title
    );
	m_window->setFramerateLimit(60);

	SceneManager::getInstance().setScene(
		std::make_unique<GameScene>(m_window)
	);
}

App::~App()
{

}

void App::pollEvent()
{
    while (const std::optional<sf::Event>& event = m_window->pollEvent())
    {
		SceneManager::getInstance().pollEvent(event);
    }
}

void App::update(const float& dt)
{
	SceneManager::getInstance().update(dt);
}

void App::draw()
{
	SceneManager::getInstance().draw();
}

void App::run()
{
	sf::Clock dt_clock, event_clock;
	sf::Time dt;

	while (m_window->isOpen())
	{
		event_clock.restart();
		pollEvent();
		dt = dt_clock.restart() - event_clock.restart();
		update(dt.asSeconds());
		draw();
	}
}