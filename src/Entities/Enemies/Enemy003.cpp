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
    entity_data.acceleration = 50.f;
    entity_data.speed = 80.f;
    entity_data.type = EntityType::Enemy;
    entity_data.max_health_points = 7;
    entity_data.health_points = entity_data.max_health_points;

    m_staying = false;
    m_shoot_cooldown = 1.f;
}

Enemy003::~Enemy003()
{
}

void Enemy003::AI(const float& dt)
{
    // std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>>
    auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    
    if (!target.has_value()) return;

    const sf::Vector2f distance = target->get()->getCenter() - getCenter();
    
    m_staying = false;
    if (distance.length() > 300.f)       velocity.terminal = distance;
    else if (distance.length() < 200.f)  velocity.terminal = -distance;
    else m_staying = true;
    
    if (m_staying && m_shoot_cooldown == 0.f)
    {
        EntityManager::getInstance().newHitscan(
            (DynamicBody*)this,
            getCenter(),
            distance.normalized(),
            true
        );
        
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