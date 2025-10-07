#include "../../../include/Entities/Enemies/Enemy003.h"
#include "../../../include/Entities/Projectile.h"

#include "../../../include/Core/InputManager.h"
#include "../../../include/Core/EntityManager.h"
#include "../../../include/Core/ColorManager.h"


Enemy003::Enemy003(const sf::Vector2f& position)
    : Entity(
        "enemy_003", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 16, 16 } }
    )
{
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 5;
    entity_data.health_points = entity_data.max_health_points;
    
    entity_data.shot_delay = 2.5f;

    entity_data.dash_delay = 1.f;
    entity_data.acceleration = 50.f;
    entity_data.speed = 80.f;
}

void Enemy003::AI(const float& dt)
{
    // std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>>
    const auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    if (!target) return;
    m_distance = target->get()->getCenter() - getCenter();
    
    if (m_distance.length() > 300.f)
        velocity.terminal = m_distance;
    else if (m_distance.length() < 200.f)
        velocity.terminal = -m_distance;
    
    if (entity_data.standing)
    {
        shootHitscan(
            getCenter(),
            m_distance.normalized(),
            true
        );
    }
}

const std::optional<Enemy003::LookingDirection> Enemy003::processDirection()
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