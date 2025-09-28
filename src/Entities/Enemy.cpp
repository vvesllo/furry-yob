#include "../../include/Entities/Enemy.h"
#include "../../include/Entities/Projectile.h"

#include "../../include/Core/InputManager.h"
#include "../../include/Core/MapManager.h"


Enemy::Enemy(const sf::Vector2f& position)
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

Enemy::~Enemy()
{
}

void Enemy::AI(const float& dt)
{
    int target_index = 0;
    bool _player_alive = false;

    std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies = MapManager::getInstance().getEntities();

    for (; target_index < dynamic_bodies.size(); ++target_index)
    {
        if (dynamic_cast<const Entity*>(dynamic_bodies[target_index].get()) != nullptr)
        {
            Entity* entity = (Entity*)dynamic_bodies[target_index].get();
            if (entity->getType() == EntityType::Player) 
            {
                _player_alive = true;
                break;
            }
        }
    }
    
    if (!_player_alive)
        return;

    std::unique_ptr<DynamicBody>& target = dynamic_bodies[target_index]; 
    const sf::Vector2f distance = target->getCenter() - getCenter();
    
    m_staying = false;
    if (distance.length() > 100.f)      velocity.terminal = distance;
    else if (distance.length() < 80.f)  velocity.terminal = -distance;
    else m_staying = true;
    
    if (m_staying && m_shoot_cooldown == 0.f)
    {
        MapManager::getInstance().newProjectile(
            (DynamicBody*)this,
            ProjectileType::Hostile,
            getCenter(),
            distance.normalized(),
            300.f
        );
        
        m_shoot_cooldown = .1f;
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