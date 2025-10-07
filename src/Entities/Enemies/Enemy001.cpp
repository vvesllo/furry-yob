#include "include/Entities/Enemies/Enemy001.h"
#include "include/Entities/Projectile.h"

#include "include/Core/Managers/InputManager.h"
#include "include/Core/Managers/EntityManager.h"
#include "include/Core/Managers/ColorManager.h"



Enemy001::Enemy001(const sf::Vector2f& position)
    : Entity(
        "enemy_001", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 14, 16 } }
    )
{
    EntityData data;
    
    data.type = EntityType::Enemy;

    data.max_health_points = 6;
    data.health_points = data.max_health_points;
    
    data.shot_delay = 1.f;

    data.dash_delay = .0f;
    data.acceleration = 50.f;
    data.speed = 80.f;
    
    regist(data);
}

void Enemy001::AI(const float& dt)
{
    const auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    if (!target) return;
    m_distance = target->get()->getCenter() - getCenter();
    
    if (m_distance.length() > 100.f) 
        velocity.terminal = m_distance;
    
    if (entity_data.standing)
    {
        for (short i=-2; i < 3; ++i)
        {
            shootProjectile(
                "projectile_bullet", // name
                sf::FloatRect{ getCenter(), { 5, 5 } }, // rect
                m_distance.normalized().rotatedBy(sf::degrees(5 * i)), // direction
                400.f, // speed
                5.f, // life time
                false, // piercing
                [](Projectile* projectile) {} // ai
            );
        }
    }
}

const std::optional<Enemy001::LookingDirection> Enemy001::processDirection() 
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