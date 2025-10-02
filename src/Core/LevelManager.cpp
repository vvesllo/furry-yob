#include "../../include/Core/LevelManager.h"
#include "../../include/Core/ResourceManager.h"
#include "../../include/Core/ColorManager.h"

#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Entity.h"
#include "../../include/Entities/Player.h"

#include <fstream>

LevelManager::LevelManager()
{
    m_tile_sprite = std::make_unique<sf::Sprite>(*ResourceManager::getInstance().getTexture("tile"));
    m_tile_sprite->setColor(ColorManager::getInstance().getColors().ground);

    m_colliders.clear();
    m_spawn_points.clear();

    m_size = { 33, 33 };
    
    m_player_icon = std::make_unique<sf::Sprite>(*ResourceManager::getInstance().getTexture("life_5"));
    m_player_icon->setOrigin(m_player_icon->getGlobalBounds().size / 2.f); 
    m_player_icon->setScale({4, 4});
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
    
    sf::FloatRect rect{ {0, 0}, { 16, 16 } };
    ColliderType type;

    size_t columns, rows=0;

    while (file >> line)
    {
        size_t x = 0;
        for (; x < line.length(); ++x)
        {
            rect.position.x = rect.size.x * (-(float)m_size.x / 2.f + x);
            rect.position.y = rect.size.y * (-(float)m_size.y / 2.f + rows);

            switch (line[x])
            {
            case '0':
                type = ColliderType::Empty;
                break;
            case '2':
                m_spawn_points.push_back(rect.position);
            case '1':
                type = ColliderType::Ground;
                break;
            }

            m_colliders.emplace_back(
                std::make_unique<Collider>(rect, type)
            );
        }
        ++rows;
        columns = std::max(columns, x);
    }
    
    file.close();
    
    m_size.x = rows;
    m_size.y = columns;

    
    m_blood = std::make_unique<sf::RenderTexture>(sf::Vector2u{ m_size.x * 16, m_size.y * 16 });
    m_blood->clear(sf::Color(0, 0, 0, 0));

    m_blood_sprite = std::make_unique<sf::Sprite>(m_blood->getTexture());
    m_blood_sprite->setOrigin(m_blood_sprite->getGlobalBounds().size / 2.f);
    m_blood_sprite->setColor(sf::Color(255, 255, 255, 150));
}

const std::vector<sf::Vector2f>& LevelManager::getSpawnPoints()
{
    return m_spawn_points;
}

const std::vector<std::unique_ptr<Collider>>& LevelManager::get()
{
    return m_colliders;
}

const sf::Vector2u& LevelManager::getSize()
{
    return m_size;
}

std::unique_ptr<sf::Sprite>& LevelManager::getTileSprite()
{
    return m_tile_sprite;
}

void LevelManager::addBlood(const sf::Vector2f& position, const sf::Color& color)
{
    unsigned short size = 5;
    
    sf::CircleShape circle;
    circle.setFillColor(color);

    sf::Vector2f final_position = position + (sf::Vector2f)m_blood->getSize() / 2.f;

    for (unsigned short i=size; i > 1; --i)
    {
        circle.setRadius(i);
        
        circle.setPosition(final_position + 2.f * sf::Vector2f(size - i, 0).rotatedBy(sf::degrees(rand() % 360)));
        
        m_blood->draw(circle);
    }
}

void LevelManager::draw(std::unique_ptr<sf::RenderWindow>& target)
{	
	for (size_t i=0; i < m_colliders.size(); ++i)
	{
		if (m_colliders[i]->getType() == ColliderType::Ground)
		{
			m_tile_sprite->setPosition(m_colliders[i]->getRect().position);
			target->draw(*m_tile_sprite);
        }
    }

    m_blood->display();
    target->draw(*m_blood_sprite);
}

void LevelManager::setPlayerIcon(const int hp)
{
    switch (hp)
    {
    case 5:  m_player_icon->setTexture(*ResourceManager::getInstance().getTexture("life_5")); break;
    case 4:  m_player_icon->setTexture(*ResourceManager::getInstance().getTexture("life_4")); break;
    case 3:  m_player_icon->setTexture(*ResourceManager::getInstance().getTexture("life_3")); break;
    case 2:  m_player_icon->setTexture(*ResourceManager::getInstance().getTexture("life_2")); break;
    default: m_player_icon->setTexture(*ResourceManager::getInstance().getTexture("life_1")); break;
    }
}

std::unique_ptr<sf::Sprite>& LevelManager::getPlayerIcon()
{
    return m_player_icon;
}