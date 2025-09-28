#include "../../include/Entities/Player.h"
#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Enemy.h"

#include "../../include/Core/InputManager.h"
#include "../../include/Core/MapManager.h"

Player::Player(const sf::Vector2f& position)
    : Entity("player", sf::Color::Red, {
        position, 
        { 12, 16 }
    })
{
    entity_data.acceleration = 10.f;
    entity_data.speed = 160.f;
    entity_data.type = EntityType::Player;
    entity_data.health_points = 5;

    m_shoot_cooldown=0;
}

Player::~Player()
{
}

void Player::AI(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.terminal.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.terminal.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) velocity.terminal.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) velocity.terminal.y += 1;
    
    if (m_shoot_cooldown == 0.f && InputManager::getInstance().getMouse().left_button)
    {
        MapManager::getInstance().newProjectile(
            (DynamicBody*)this,
            ProjectileType::Friendly,
            getCenter(),
            (InputManager::getInstance().getMouse().position - getCenter()).normalized(),
            300.f
        );
        m_shoot_cooldown = .2f;
    }

    m_shoot_cooldown = std::max(m_shoot_cooldown - dt, 0.f);

    if (velocity.current.x > 0) lookAt(LookingDirection::Right);
    if (velocity.current.x < 0) lookAt(LookingDirection::Left);

    if (velocity.terminal.length() > 0) 
        velocity.terminal = velocity.terminal.normalized();
}