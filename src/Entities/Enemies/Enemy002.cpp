#include "include/Entities/Enemies/Enemy002.h"
#include "include/Entities/Projectile.h"

#include "include/Core/Managers/InputManager.h"
#include "include/Core/Managers/EntityManager.h"
#include "include/Core/Managers/ThemeManager.h"



Enemy002::Enemy002(const sf::Vector2f& position)
    : Entity(
        "enemy_002", 
        ThemeManager::getInstance().getTheme().enemy,
        { position, { 15, 16 } }
    )
{
    EntityData data;
    
    data.type = EntityType::Enemy;
    
    data.max_health_points = 6;
    data.health_points = data.max_health_points;
    
    data.shot_delay = .08f;
    
    data.dash_delay = 1.f;
    data.acceleration = 15.f;
    data.speed = 120.f;

    regist(data);
    
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