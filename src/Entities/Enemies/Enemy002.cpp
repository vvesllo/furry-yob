#include "../../../include/Entities/Enemies/Enemy002.h"
#include "../../../include/Entities/Projectile.h"

#include "../../../include/Core/InputManager.h"
#include "../../../include/Core/EntityManager.h"
#include "../../../include/Core/ColorManager.h"


Enemy002::Enemy002(const sf::Vector2f& position)
    : Entity(
        "enemy_002", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 15, 16 } }
    )
{
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 6;
    entity_data.health_points = entity_data.max_health_points;
    
    entity_data.shot_delay = .08f;

    entity_data.dash_delay = 1.f;
    entity_data.acceleration = 5.f;
    entity_data.speed = 130.f;
    
    m_shooting = false;
}

void Enemy002::AI(const float& dt)
{
    const auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    if (!target) return;
    const sf::Vector2f distance = target->get()->getCenter() - getCenter();
    
    velocity.terminal = distance;

    m_shooting = distance.length() < 80.f;
    
    if (m_shooting)
    {
        shootProjectile(
            "projectile_fire",
            sf::FloatRect{ getCenter(), { 9, 9 } },
            distance.normalized().rotatedBy(sf::degrees(10.f * std::sinf(++m_fire_tick))),
            800.f, .3f, true,
            [dt](Projectile* projectile) {
                projectile->velocity.current *= 0.9f;
            }
        );    
    }

}

const std::optional<Enemy002::LookingDirection> Enemy002::processDirection()
{
    if (!m_shooting)
    {
        if (velocity.current.x > 0) return LookingDirection::Right;
        else if (velocity.current.x < 0) return LookingDirection::Left;
    }

    return std::nullopt;
}