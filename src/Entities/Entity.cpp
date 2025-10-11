#include "include/Entities/Entity.h"
#include "include/Utils/Vector.h"
#include "include/Core/Managers/ResourceManager.h"
#include "include/Core/Managers/EntityManager.h"
#include "include/Core/Managers/LevelManager.h"


Entity::Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect)
    : DynamicBody(texture_name, color, rect)
{
    m_invincibility_time = 0.f;
    
    m_dash_cooldown = 0.f;
    m_shoot_cooldown = .1f;
}

void Entity::regist(const EntityData& data)
{
    m_static_entity_data = data;
    entity_data = m_static_entity_data;
}

void Entity::update(const float& dt)
{
    // check is entity dead
    if (entity_data.health_points <= 0)
    {
        destroy();
        return;
    }
    
    
    updateItems();
    
    // reset velocity
    velocity.terminal = sf::Vector2f{};

    // individual update function for entity childrens
    AI(dt);
    movement(dt);

    lookAt(processDirection());
    
    m_dash_cooldown = std::max(0.f, m_dash_cooldown - dt);
    m_shoot_cooldown = std::max(0.f, m_shoot_cooldown - dt);

    // entity can't take damage while m_invincibility_time > 0.f
    m_invincibility_time = std::max(0.f, m_invincibility_time - dt);

    if (m_shoot) 
    {
        m_shoot_cooldown = entity_data.shot_delay;
        m_shoot = false;
    }
}
    
void Entity::updateItems() 
{
    for (const auto& item : EntityManager::getInstance().getEntityItems())
    {
        ItemManager::getInstance().update(this, item.first, item.second);
    }
}

void Entity::checkColliding(const ColliderCheckAxis& axis)
{
    const Types::uptr_vec<Collider>& colliders = LevelManager::getInstance().get();
    for (size_t i=0; i < colliders.size(); ++i)
    {
        if (colliders[i]->getRect().findIntersection(rect) && colliders[i]->getType() == ColliderType::Empty)
        {
            switch (axis)
            {
                case ColliderCheckAxis::X: checkCollidingX(colliders[i]); break;
                case ColliderCheckAxis::Y: checkCollidingY(colliders[i]); break;
            }
        }
    }
}

void Entity::checkCollidingX(const std::unique_ptr<Collider>& collider)
{
    if (velocity.current.x > 0)
    {
        velocity.current.x = 0;
        rect.position.x = collider->getRect().position.x - rect.size.x;
    }
    
    else if (velocity.current.x < 0)
    {
        velocity.current.x = 0;
        rect.position.x = collider->getRect().position.x + collider->getRect().size.x;
    }
}

void Entity::checkCollidingY(const std::unique_ptr<Collider>& collider)
{
    if (velocity.current.y > 0)
    {
        velocity.current.y = 0;
        rect.position.y = collider->getRect().position.y - rect.size.y;
    }
    
    else if (velocity.current.y < 0)
    {
        velocity.current.y = 0;
        rect.position.y = collider->getRect().position.y + collider->getRect().size.y;
    }
}

void Entity::movement(const float& dt)
{
    // noramlize velocity after AI(float) (smth like {1, 1} -> {v/2, v/2})
    if (velocity.terminal.length() > 0) velocity.terminal = velocity.terminal.normalized();

    // update velocity
    velocity.current = VectorUtils::lerp(
        velocity.current, 
        velocity.terminal, 
        entity_data.acceleration > 0 ? entity_data.acceleration * dt : 1.f
    );

    // bouncy animation (jump + rotation)
    const float current_speed = velocity.current.length();
    const double additional_transformation_value = std::sin(m_moving_frames / 5.f);

    // check if entity moves and count frames when entity move
    entity_data.standing = current_speed < 0.05f;

    if (entity_data.standing) m_moving_frames = 0;
    else ++m_moving_frames;


    const sf::Angle rotation = sf::degrees(current_speed * additional_transformation_value * 10.f);
    const sf::Vector2f jumping_offset = sf::Vector2f(0, 5.f * std::abs(additional_transformation_value));

    // move entity
    rect.position.x += entity_data.speed * velocity.current.x * dt;
    checkColliding(ColliderCheckAxis::X);

    rect.position.y += entity_data.speed * velocity.current.y * dt;
    checkColliding(ColliderCheckAxis::Y);
    
    // update sprite
    sprite->setRotation(rotation);
    sprite->setPosition(rect.getCenter() - jumping_offset);
}

void Entity::dash(const sf::Vector2f& direction)
{
    if (m_dash_cooldown <= 0.f)
    {
        m_invincibility_time = .5f;
        velocity.current = direction;

        m_dash_cooldown = entity_data.dash_delay;
    }
}

void Entity::lookAt(const std::optional<LookingDirection>& direction)
{   
    // stop if current direction equals to terminal
    if (!direction || direction == m_looking_direction) return;

    switch (direction.value())
    {
    case LookingDirection::Right:
        sprite->setScale({ 1, 1 });
        break;
    case LookingDirection::Left:
        sprite->setScale({ -1, 1 });
        break;
    }

    m_looking_direction = direction.value();
}

void Entity::shootHitscan(const sf::Vector2f& position, const sf::Vector2f& direction, const bool piercing)
{
    if (m_shoot_cooldown <= 0.f)
    {
        EntityManager::getInstance().newHitscan(
            (DynamicBody*)this,
            position,
            direction,
            piercing
        );

        m_shoot = true;
    }
}

void Entity::shootProjectile(
        const std::string& name, 
        const sf::FloatRect& rect, 
        const sf::Vector2f& direction, 
        const float& speed,
        const float& lifetime,
        const bool piercing,
        const std::function<void(Projectile*)> ai)
{
    
    if (m_shoot_cooldown <= 0.f)
    {
        EntityManager::getInstance().newProjectile(
            (DynamicBody*)this, name, rect, direction, speed, lifetime, piercing, ai
        );    
        
        m_shoot = true;
    }
}

const bool Entity::preHit(Entity* sender)
{
    return true;
}

void Entity::hit(Entity* sender, const float& damage_amount)
{
    if (!preHit(sender)) return;
    
    m_invincibility_time = .2f;
    entity_data.health_points -= damage_amount;

    LevelManager::getInstance().addBlood(getCenter(), m_color);

    if (entity_data.health_points <= 0)
        destroy();
}

void Entity::heal(const float& heal_amount)
{
    entity_data.health_points = std::min(entity_data.health_points + heal_amount, entity_data.max_health_points);
}

const bool Entity::isInvincible()
{
    return m_invincibility_time > 0.f;
}

const sf::Vector2f Entity::getVelocity()
{
    return velocity.current;
}

const EntityType Entity::getType()
{
    return entity_data.type;
}
