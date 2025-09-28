#include "../../../include/Entities/Enemies/Enemy000.h"
#include "../../../include/Entities/Projectile.h"

#include "../../../include/Core/InputManager.h"
#include "../../../include/Core/EntityManager.h"


Enemy000::Enemy000(const sf::Vector2f& position)
    : Entity("enemy_000", sf::Color::Green , {
        position, 
        { 14, 16 }
    })
{
    entity_data.acceleration = 15.f;
    entity_data.speed = 120.f;
    entity_data.type = EntityType::Enemy;
    entity_data.health_points = 5;

    m_staying = false;
    m_shoot_cooldown = 0;
}

Enemy000::~Enemy000()
{
}

void Enemy000::AI(const float& dt)
{
    std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>> target = EntityManager::getInstance()
        .findEntityByType(EntityType::Player);
    
    if (!target.has_value()) return;

    const sf::Vector2f distance = target->get()->getCenter() - getCenter();
    
    m_staying = false;
    if (distance.length() > 100.f)      velocity.terminal = distance;
    else if (distance.length() < 80.f)  velocity.terminal = -distance;
    else m_staying = true;
    
    if (m_staying && m_shoot_cooldown == 0.f)
    {
        EntityManager::getInstance().newProjectile(
            (DynamicBody*)this,
            ProjectileType::Hostile,
            getCenter(),
            distance.normalized(),
            300.f
        );
        
        m_shoot_cooldown = .3f;
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