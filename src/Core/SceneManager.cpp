#include "../../include/Core/SceneManager.h"

SceneManager::SceneManager()
{
    m_scene = nullptr;
}

SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::setScene(std::unique_ptr<Scene>&& scene)
{
    m_scene.release();
    m_scene = std::move(scene);
}

void SceneManager::update(const float& dt)
{
    if (m_scene)
        m_scene->update(dt);
}

void SceneManager::pollEvent(const std::optional<sf::Event> event)
{
    if (m_scene)
        m_scene->pollEvent(event);
}

void SceneManager::draw()
{
    if (m_scene)
        m_scene->draw();
}