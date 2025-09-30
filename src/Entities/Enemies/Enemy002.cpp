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
    entity_data.acceleration = 5.f;
    entity_data.speed = 150.f;
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 7;
    entity_data.health_points = entity_data.max_health_points;

    m_shooting = false;
    m_shoot_cooldown = 1.f;
}

Enemy002::~Enemy002()
{
}

void Enemy002::AI(const float& dt)
{
    // std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>>
    auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    
    if (!target.has_value()) return;

    const sf::Vector2f distance = target->get()->getCenter() - getCenter();
    
    velocity.terminal = distance;

    m_shooting = distance.length() < 80.f;
    
    if (m_shooting && m_shoot_cooldown == 0.f)
    {
        m_fire_tick++;
        EntityManager::getInstance().newProjectile(
            (DynamicBody*)this,
            "projectile_fire",
            sf::FloatRect{ getCenter(), { 9, 9 } },
            distance.normalized().rotatedBy(sf::degrees(10.f * std::sinf(m_fire_tick))),
            400.f,
            .3f,
            true
        );    
        m_shoot_cooldown = .08f;
    }

    m_shoot_cooldown = std::max(m_shoot_cooldown - dt, 0.f);

    if (!m_shooting)
    {
        m_fire_tick = 0;
        if (velocity.current.x > 0) lookAt(LookingDirection::Right);
        if (velocity.current.x < 0) lookAt(LookingDirection::Left);
    }
    
    if (velocity.terminal.length() > 0) 
        velocity.terminal = velocity.terminal.normalized();
}