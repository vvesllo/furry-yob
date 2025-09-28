#include "../../include/Core/LevelManager.h"
#include "../../include/Core/ResourceManager.h"

#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Entity.h"
#include "../../include/Entities/Player.h"

#include <fstream>

LevelManager::LevelManager()
{
    m_tile_sprite = std::make_unique<sf::Sprite>(*ResourceManager::getInstance().getTexture("tile"));
    m_tile_sprite->setColor(sf::Color::Blue);
    m_size = { 25, 25 };
    m_level = {};
}

LevelManager& LevelManager::getInstance()
{
    static LevelManager instance;
    return instance;
}

void LevelManager::load(const std::string& name)
{
    std::ifstream file("resources/maps/" + name + ".txt");
    std::string line;

    while (file >> line)
    {
        m_level.emplace_back(line);
    }

    file.close();
}

const std::vector<std::string>& LevelManager::get()
{
    return m_level;
}

const sf::Vector2u& LevelManager::getSize()
{
    return m_size;
}

std::unique_ptr<sf::Sprite>& LevelManager::getTileSprite()
{
    return m_tile_sprite;
}