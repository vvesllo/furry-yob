#include "../../include/Entities/Player.h"
#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Enemies/Enemy000.h"

#include "../../include/Core/InputManager.h"
#include "../../include/Core/EntityManager.h"
#include "../../include/Core/LevelManager.h"
#include "../../include/Core/ColorManager.h"

#include <print>

Player::Player(const sf::Vector2f& position)
    : Entity(
        "player", 
        ColorManager::getInstance().getColors().player,
        { position, { 12, 16 } }
    )
{
    entity_data.acceleration = 10.f;
    entity_data.speed = 160.f;
    entity_data.type = EntityType::Player;
    entity_data.max_health_points = 5;
    entity_data.health_points = entity_data.max_health_points;

    m_shoot_cooldown=0;
    m_dash_cooldown=0;
}

Player::~Player()
{
}

void Player::AI(const float& dt)
{
    sf::Vector2f& mouse_position = InputManager::getInstance().getMouse().position;
    sf::Vector2f mouse_direction = (mouse_position - getCenter()).normalized();
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.terminal.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.terminal.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) velocity.terminal.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) velocity.terminal.y += 1;
    
    if (m_dash_cooldown == 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) 
    {
        dash(velocity.terminal * 5.f);
        m_dash_cooldown = 1.f;
    }

    if (m_shoot_cooldown == 0.f && InputManager::getInstance().getMouse().left_button)
    {
        EntityManager::getInstance().newHitscan(
            (DynamicBody*)this,
            getCenter(),
            mouse_direction,
            false
        );
        m_shoot_cooldown = .2f;
    }

    m_shoot_cooldown = std::max(m_shoot_cooldown - dt, 0.f);
    m_dash_cooldown = std::max(m_dash_cooldown - dt, 0.f);

    if (getCenter().x < mouse_position.x) lookAt(LookingDirection::Right);
    if (getCenter().x > mouse_position.x) lookAt(LookingDirection::Left);

    if (velocity.terminal.length() > 0) 
        velocity.terminal = velocity.terminal.normalized();

    LevelManager::getInstance().setPlayerIcon(entity_data.health_points);
}