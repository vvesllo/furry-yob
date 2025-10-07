#include "include/Entities/Enemies/Enemy000.h"
#include "include/Entities/Projectile.h"

#include "include/Core/Managers/InputManager.h"
#include "include/Core/Managers/EntityManager.h"
#include "include/Core/Managers/ColorManager.h"

#include <print>

Enemy000::Enemy000(const sf::Vector2f& position)
    : Entity(
        "enemy_000", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 14, 16 } }
    )
{
    EntityData data;

    data.type = EntityType::Enemy;

    data.max_health_points = 3;
    data.health_points = data.max_health_points;
    
    data.shot_delay = .5f;

    data.dash_delay = 1.f;
    data.acceleration = 10.f;
    data.speed = 100.f;

    regist(data);
}

void Enemy000::AI(const float& dt)
{
    const auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    if (!target) return;
    m_distance = target->get()->getCenter() - getCenter();
    
    // move to player
    if (m_distance.length() > 120.f)
        velocity.terminal = m_distance;

    // move from player
    else if (m_distance.length() < 60.f)
        velocity.terminal = -m_distance;
    
    if (entity_data.standing)
    {
        shootHitscan(
            getCenter(),
            m_distance.normalized().rotatedBy(sf::degrees(10 - rand() % 21)),
            true
        );
    }
}

const std::optional<Enemy000::LookingDirection> Enemy000::processDirection() 
{
    if (!entity_data.standing)
    {
        if (velocity.current.x > 0) return LookingDirection::Right;
        if (velocity.current.x < 0) return LookingDirection::Left;
    }
    else
    {
        if (m_distance.x > 0) return LookingDirection::Right;
        if (m_distance.x < 0) return LookingDirection::Left;
    }

    return std::nullopt;
}