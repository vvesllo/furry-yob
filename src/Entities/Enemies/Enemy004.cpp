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
    entity_data.acceleration = 50.f;
    entity_data.speed = 50.f;
    entity_data.type = EntityType::Enemy;

    entity_data.max_health_points = 13;
    entity_data.health_points = entity_data.max_health_points;

    m_staying = false;
    m_shoot_cooldown = 1.f;
}

Enemy004::~Enemy004()
{
}

void Enemy004::AI(const float& dt)
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
        m_fire_tick++;
        EntityManager::getInstance().newHitscan(
            (DynamicBody*)this,
            getCenter(),
            distance.normalized().rotatedBy(sf::degrees(10.f * std::sinf(m_fire_tick))),
            false
        );    
        m_shoot_cooldown = .08f;
    }

    m_shoot_cooldown = std::max(m_shoot_cooldown - dt, 0.f);

    
    if (!m_staying)
    {
        m_fire_tick = 0;
        if (velocity.current.x > 0) lookAt(LookingDirection::Right);
        if (velocity.current.x < 0) lookAt(LookingDirection::Left);
    }
    else
    {
        if (distance.x > 0) lookAt(LookingDirection::Right);
        if (distance.x < 0) lookAt(LookingDirection::Left);
    }
    
    // if (getCenter().x < target->get()->getCenter().x) lookAt(LookingDirection::Right);
    // if (getCenter().x > target->get()->getCenter().x) lookAt(LookingDirection::Left);
    
    if (velocity.terminal.length() > 0) 
        velocity.terminal = velocity.terminal.normalized();
}