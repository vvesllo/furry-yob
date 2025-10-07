#include "../../../include/Entities/Enemies/Enemy000.h"
#include "../../../include/Entities/Projectile.h"

#include "../../../include/Core/InputManager.h"
#include "../../../include/Core/EntityManager.h"
#include "../../../include/Core/ColorManager.h"


Enemy000::Enemy000(const sf::Vector2f& position)
    : Entity(
        "enemy_000", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 14, 16 } }
    )
{
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 3;
    entity_data.health_points = entity_data.max_health_points;
    
    entity_data.shot_delay = .5f;

    entity_data.dash_delay = 1.f;
    entity_data.acceleration = 10.f;
    entity_data.speed = 160.f;
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