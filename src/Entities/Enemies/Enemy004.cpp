#include "../../../include/Entities/Enemies/Enemy004.h"
#include "../../../include/Entities/Projectile.h"

#include "../../../include/Core/InputManager.h"
#include "../../../include/Core/EntityManager.h"
#include "../../../include/Core/ColorManager.h"


Enemy004::Enemy004(const sf::Vector2f& position)
    : Entity(
        "enemy_004", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 19, 19 } }
    )
{
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 8;
    entity_data.health_points = entity_data.max_health_points;
    
    entity_data.shot_delay = .1f;

    entity_data.dash_delay = 1.f;
    entity_data.acceleration = 30.f;
    entity_data.speed = 70.f;
}

void Enemy004::AI(const float& dt)
{
    const auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    if (!target.has_value()) return;
    m_direction = target->get()->getCenter() - getCenter();

    if (m_direction.length() > 100.f) 
        velocity.terminal = m_direction;

    if (entity_data.standing)
    {
        m_fire_tick++;
        shootHitscan(
            getCenter(),
            m_direction.normalized().rotatedBy(sf::degrees(10.f * std::sinf(++m_fire_tick))),
            false
        );
    }
}

const std::optional<Enemy004::LookingDirection> Enemy004::processDirection()
{
    if (!entity_data.standing)
    {
        if (velocity.current.x > 0) return LookingDirection::Right;
        if (velocity.current.x < 0) return LookingDirection::Left;
    }
    else
    {
        if (m_direction.x > 0) return LookingDirection::Right;
        if (m_direction.x < 0) return LookingDirection::Left;
    }
    
    return std::nullopt;
}