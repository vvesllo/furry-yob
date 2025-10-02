#include "../../../include/Entities/Enemies/Enemy001.h"
#include "../../../include/Entities/Projectile.h"

#include "../../../include/Core/InputManager.h"
#include "../../../include/Core/EntityManager.h"
#include "../../../include/Core/ColorManager.h"


Enemy001::Enemy001(const sf::Vector2f& position)
    : Entity(
        "enemy_001", 
        ColorManager::getInstance().getColors().enemy,
        { position, { 14, 16 } }
    )
{
    entity_data.acceleration = 50.f;
    entity_data.speed = 80.f;
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 10;
    entity_data.health_points = entity_data.max_health_points;

    m_staying = false;
    m_shoot_cooldown = 1.f;
}

Enemy001::~Enemy001()
{
}

void Enemy001::AI(const float& dt)
{
    // std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>>
    auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    
    if (!target.has_value()) return;

    const sf::Vector2f distance = target->get()->getCenter() - getCenter();
    
    m_staying = false;
    if (distance.length() > 100.f) velocity.terminal = distance;
    else m_staying = true;
    
    if (m_staying && m_shoot_cooldown == 0.f)
    {
        for (short i=-2; i < 3; ++i)
        {
            EntityManager::getInstance().newProjectile(
                (DynamicBody*)this,
                "projectile_bullet",
                sf::FloatRect{ getCenter(), { 5, 5 } },
                distance.normalized().rotatedBy(sf::degrees(5 * i)),
                400.f,
                5.f,
                false,
                [](Projectile* projectile) {}
            );
        }
        
        m_shoot_cooldown = 2.f;
    }

    m_shoot_cooldown = std::max(m_shoot_cooldown - dt, 0.f);

    if (!m_staying)
    {
        if (velocity.current.x > 0) lookAt(LookingDirection::Right);
        if (velocity.current.x < 0) lookAt(LookingDirection::Left);
    }
    else
    {
        if (distance.x > 0) lookAt(LookingDirection::Right);
        if (distance.x < 0) lookAt(LookingDirection::Left);
    }
    
    if (velocity.terminal.length() > 0) 
        velocity.terminal = velocity.terminal.normalized();
}