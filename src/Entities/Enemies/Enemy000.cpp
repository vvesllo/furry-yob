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
    entity_data.acceleration = 15.f;
    entity_data.speed = 100.f;
    entity_data.type = EntityType::Enemy;
    entity_data.max_health_points = 3;
    entity_data.health_points = entity_data.max_health_points;

    m_staying = false;
    m_shoot_cooldown = 1.f;
}

Enemy000::~Enemy000()
{
}

void Enemy000::AI(const float& dt)
{
    // std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>>
    auto target = EntityManager::getInstance().findEntityByType(EntityType::Player);
    
    if (!target.has_value()) return;

    const sf::Vector2f distance = target->get()->getCenter() - getCenter();
    
    m_staying = false;
    if (distance.length() > 120.f)      velocity.terminal = distance;
    else if (distance.length() < 60.f)  velocity.terminal = -distance;
    else m_staying = true;
    
    if (m_staying && m_shoot_cooldown == 0.f)
    {
        EntityManager::getInstance().newProjectile(
            (DynamicBody*)this,
            "projectile_bullet",
            {getCenter(), {5, 5}},
            distance.normalized().rotatedBy(sf::degrees(10 - rand() % 21)),
            400.f,
            3.f,
            true,
            [](Projectile* projectile) {}
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